/*
* 5x5x3
*
* Connect to 5x5x3 keyboard to relay desktop and sound values so that they can be shown visually using rgb leds.
*/

use std::{
    fs,
    io::{self, Read, Write},
    os::unix::{
        fs::PermissionsExt,
        net::UnixListener,
    },
    path::Path,
    sync::{
        atomic::{AtomicBool, Ordering},
        Arc, Mutex,
    },
    thread,
    time::Duration,
};

use serialport;
use tokio::sync::mpsc as tokio_mpsc;
use udev::Enumerator;

const SOCKET_NAME: &str = "/run/user/1000/5x5x3/socket"; // Will need to be adjusted for actual UID
const FIFO_NAME: &str = "/run/user/1000/5x5x3/fifo";

#[derive(Debug)]
struct Mux {
    running: Arc<AtomicBool>,
    serial_out: tokio_mpsc::Sender<Vec<u8>>,
    terminals: Arc<Mutex<Vec<Terminal>>>,
    debug: bool,
}

impl Mux {
    fn new(serial_out: tokio_mpsc::Sender<Vec<u8>>, debug: bool) -> Self {
        Mux {
            running: Arc::new(AtomicBool::new(true)),
            serial_out,
            terminals: Arc::new(Mutex::new(Vec::new())),
            debug,
        }
    }

    fn terminal_add(&self, terminal: Terminal) {
        let mut terminals = self.terminals.lock().unwrap();
        terminals.push(terminal);
        println!("{} clients active", terminals.len());
    }

    async fn terminal_line_received(&self, line: Vec<u8>) {
        if self.debug {
            println!("{}", String::from_utf8_lossy(&line));
        }
        self.serial_out.send(line).await.unwrap_or_default();
    }

    async fn terminal_line_transmit(&self, line: Vec<u8>) {
        if self.debug {
            println!("{}", String::from_utf8_lossy(&line));
        }
        // clone terminals to avoid holding lock across await
        let terminals = {
            let guard = self.terminals.lock().unwrap();
            guard.clone()
        };
        for terminal in terminals {
            terminal.write(line.clone()).await;
        }
    }

    fn terminal_abort(&self, terminal: &Terminal) {
        let mut terminals = self.terminals.lock().unwrap();
        terminals.retain(|t| t.id != terminal.id);
        if self.debug {
            println!("{} clients active", terminals.len());
        }
    }

    fn stop(&self) {
        self.running.store(false, Ordering::SeqCst);
    }
}

#[derive(Debug, Clone)]
struct Terminal {
    id: usize,
    sender: tokio_mpsc::Sender<Vec<u8>>,
}

impl Terminal {
    async fn write(&self, data: Vec<u8>) {
        self.sender.send(data).await.unwrap_or_default();
    }
}

// Stub for PulseListener. Real implementation would require using libpulse-binding's callback API and mainloop.
struct PulseListener {
    mux: Arc<Mux>,
}

impl PulseListener {
    fn new(mux: Arc<Mux>) -> Self {
        PulseListener { mux }
    }

    fn listen(&self) {
        // TODO: Replace this stub with a callback-based approach using libpulse-binding
        // For now, this function does nothing
        println!("PulseListener.listen() stub called.");
    }
}

fn find_5x5x3() -> Option<String> {
    let mut enumerator = Enumerator::new().ok()?;
    enumerator.match_subsystem("tty").ok()?;
    for device in enumerator.scan_devices().ok()? {
        if let Some(model) = device.property_value("ID_MODEL") {
            if model.to_str() == Some("5x5x3") {
                if let Some(devnode) = device.devnode() {
                    return Some(devnode.to_string_lossy().into_owned());
                }
            }
        }
    }
    None
}

#[tokio::main]
async fn main() -> io::Result<()> {
    let serial_device = find_5x5x3().expect("Failed to find 5x5x3 device");
    println!("Attaching to {}, mux at {}", serial_device, SOCKET_NAME);

    // Create required directories
    fs::create_dir_all(Path::new(FIFO_NAME).parent().unwrap())?;
    fs::create_dir_all(Path::new(SOCKET_NAME).parent().unwrap())?;
    let _ = fs::remove_file(FIFO_NAME);

    // Create FIFO
    nix::unistd::mkfifo(Path::new(FIFO_NAME), nix::sys::stat::Mode::from_bits(0o600).unwrap())?;

    // Setup serial port inside Arc<Mutex> for sharing
    let port = Arc::new(Mutex::new(
        serialport::new(&serial_device, 115200)
            .open()
            .expect("Failed to open serial port")
    ));

    let (tx, mut serial_rx) = tokio_mpsc::channel(100);
    let mux = Arc::new(Mux::new(tx, true));

    // Start pulse listener (stub, non-async)
    let pulse_listener = PulseListener::new(mux.clone());
    pulse_listener.listen();

    // Handle serial port reading in blocking thread
    {
        let mux_clone = mux.clone();
        let port_clone = port.clone();
        thread::spawn(move || {
            let mut buf = [0u8; 1024];
            while mux_clone.running.load(Ordering::SeqCst) {
                let n = port_clone.lock().unwrap().read(&mut buf).unwrap_or(0);
                if n > 0 {
                    let data = buf[..n].to_vec();
                    // send to mux via channel
                    let _ = mux_clone.serial_out.try_send(data);
                }
                thread::sleep(Duration::from_millis(10));
            }
        });
    }

    // Handle serial port writing in blocking thread
    {
        let mux_clone = mux.clone();
        let port_clone = port.clone();
        thread::spawn(move || {
            while let Some(data) = serial_rx.blocking_recv() {
                let _ = port_clone.lock().unwrap().write_all(&data);
            }
            mux_clone.stop();
        });
    }

    // Setup Unix domain socket
    let listener = UnixListener::bind(SOCKET_NAME)?;
    fs::set_permissions(SOCKET_NAME, fs::Permissions::from_mode(0o600))?;

    while mux.running.load(Ordering::SeqCst) {
        if let Ok((mut stream, _)) = listener.accept() {
            let (tx, _rx) = tokio_mpsc::channel(100);
            let terminal = Terminal {
                id: rand::random(),
                sender: tx,
            };
            mux.terminal_add(terminal);

            let mux_clone = mux.clone();
            thread::spawn(move || {
                let mut buf = [0u8; 1024];
                while let Ok(n) = stream.read(&mut buf) {
                    if n == 0 { break; }
                    let _ = mux_clone.serial_out.try_send(buf[..n].to_vec());
                }
            });
        }
    }

    Ok(())
}
