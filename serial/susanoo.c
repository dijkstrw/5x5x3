#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <libudev.h>
#include <linux/serial.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <termios.h>
#include <unistd.h>

#define DIR_NAME      "/run/user/%d/5x5x3"
#define SOCKET_NAME   "%s/socket"
#define FIFO_NAME     "%s/fifo"
#define SERIAL_NAME   "/dev/ttyACM%d"
#define MAX_TERMINALS 10
#define BUFFER_SIZE   1024

typedef struct {
    int serial_fd;
    int fifo_fd;
    int socket_fd;
    int terminals[MAX_TERMINALS];
    int num_terminals;
} Mux;

int find_5x5x3()
{
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;
    const char *path, *model;

    udev = udev_new();
    if (!udev) {
        fprintf(stderr, "Can't create udev\n");
        exit(1);
    }

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices)
    {
        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        model = udev_device_get_property_value(dev, "ID_MODEL");
        if (model != NULL && strcmp(model, "5x5x3") == 0) {
            const char *devname = udev_device_get_property_value(dev, "DEVNAME");
            if (devname != NULL) {
                int fd = open(devname, O_RDWR | O_NOCTTY | O_NONBLOCK);
                if (fd != -1) {
                    udev_device_unref(dev);
                    udev_enumerate_unref(enumerate);
                    udev_unref(udev);
                    return fd;
                }
            }
        }

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);
    return -1;
}

void mux_init(Mux *mux, int serial_fd, int fifo_fd, int socket_fd)
{
    mux->serial_fd = serial_fd;
    mux->fifo_fd = fifo_fd;
    mux->socket_fd = socket_fd;
    mux->num_terminals = 0;
}

void mux_add_terminal(Mux *mux, int fd)
{
    if (mux->num_terminals < MAX_TERMINALS) {
        mux->terminals[mux->num_terminals] = fd;
        mux->num_terminals++;
        printf("%d clients active\n", mux->num_terminals);
    }
}

void mux_remove_terminal(Mux *mux, int fd)
{
    for (int i = 0; i < mux->num_terminals; i++) {
        if (mux->terminals[i] == fd) {
            mux->terminals[i] = mux->terminals[--mux->num_terminals];
            printf("%d clients active\n", mux->num_terminals);
            break;
        }
    }
}

void mux_broadcast(Mux *mux, const char *data, int len)
{
    for (int i = 0; i < mux->num_terminals; i++) {
        write(mux->terminals[i], data, len);
    }
}

void mux_handle_serial_input(Mux *mux)
{
    char buffer[BUFFER_SIZE];
    int len = read(mux->serial_fd, buffer, sizeof(buffer));
    if (len > 0) {
        mux_broadcast(mux, buffer, len);
    }
}

void mux_handle_fifo_input(Mux *mux)
{
    char buffer[BUFFER_SIZE];
    int len = read(mux->fifo_fd, buffer, sizeof(buffer));
    if (len > 0) {
        write(mux->serial_fd, buffer, len);
    }
}

void mux_handle_terminal_input(Mux *mux, int fd)
{
    char buffer[BUFFER_SIZE];
    int len = read(fd, buffer, sizeof(buffer));
    if (len > 0) {
        write(mux->serial_fd, buffer, len);
    } else if (len == 0) {
        mux_remove_terminal(mux, fd);
        close(fd);
    }
}

void mux_handle_socket_connection(Mux *mux)
{
    int client_fd = accept(mux->socket_fd, NULL, NULL);
    if (client_fd >= 0) {
        mux_add_terminal(mux, client_fd);
    }
}

void mux_run(Mux *mux)
{
    fd_set read_fds;
    int max_fd;

    FD_ZERO(&read_fds);
    FD_SET(mux->serial_fd, &read_fds);
    FD_SET(mux->fifo_fd, &read_fds);
    FD_SET(mux->socket_fd, &read_fds);

    max_fd = mux->serial_fd;
    if (mux->fifo_fd > max_fd) {
        max_fd = mux->fifo_fd;
    }
    if (mux->socket_fd > max_fd) {
        max_fd = mux->socket_fd;
    }

    for (int i = 0; i < mux->num_terminals; i++) {
        FD_SET(mux->terminals[i], &read_fds);
        if (mux->terminals[i] > max_fd) {
            max_fd = mux->terminals[i];
        }
    }

    select(max_fd + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(mux->socket_fd, &read_fds)) {
        mux_handle_socket_connection(mux);
    }

    if (FD_ISSET(mux->serial_fd, &read_fds)) {
        mux_handle_serial_input(mux);
    }

    if (FD_ISSET(mux->fifo_fd, &read_fds)) {
        mux_handle_fifo_input(mux);
    }

    for (int i = 0; i < mux->num_terminals; i++) {
        if (FD_ISSET(mux->terminals[i], &read_fds)) {
            mux_handle_terminal_input(mux, mux->terminals[i]);
        }
    }
}

int main()
{
    Mux mux;
    int serial_fd = find_5x5x3();
    int fifo_fd;
    int socket_fd;
    int status;
    char *work_dir_name;
    char *socket_name;
    char *fifo_name;

    if (serial_fd < 0) {
        err(EXIT_FAILURE, "Failed to open serial device");
    }

    if (fcntl(serial_fd, F_SETFL, O_NONBLOCK) < 0) {
        err(EXIT_FAILURE, "Could not set serial to non-blocking");
    }

    if (asprintf(&work_dir_name, DIR_NAME, getuid()) < 0) {
        err(EXIT_FAILURE, "Failed to allocate work dir name");
    }

    if (asprintf(&socket_name, SOCKET_NAME, work_dir_name) < 0) {
        err(EXIT_FAILURE, "Failed to allocate socket name");
    }

    if (asprintf(&fifo_name, FIFO_NAME, work_dir_name) < 0) {
        err(EXIT_FAILURE, "Failed to allocate fifo name");
    }

    status = mkdir(work_dir_name, S_IRWXU);
    if ((status < 0) && (errno != EEXIST)) {
        err(EXIT_FAILURE, "Failed to create work dir");
    }

    unlink(fifo_name);
    if (mkfifo(fifo_name, S_IRUSR | S_IWUSR) < 0) {
        err(EXIT_FAILURE, "Failed to create fifo");
    }

    if ((fifo_fd = open(fifo_name, O_RDONLY | O_NONBLOCK)) < 0) {
        err(EXIT_FAILURE, "Failed to open fifo");
    }

    if (fcntl(fifo_fd, F_SETFL, O_NONBLOCK) < 0) {
        err(EXIT_FAILURE, "Could not set fifo to non-blocking");
    }

    if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_name, sizeof(addr.sun_path) - 1);

    unlink(socket_name);
    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        err(EXIT_FAILURE, "Failed to bind socket");
    }

    if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) < 0) {
        err(EXIT_FAILURE, "Could not set socket to non-blocking");
    }

    if (listen(socket_fd, 5) < 0) {
        err(EXIT_FAILURE, "Failed to listen on socket");
    }

    mux_init(&mux, serial_fd, fifo_fd, socket_fd);

    for (;;) {
        mux_run(&mux);
    }

    /* Not reached: */
    close(serial_fd);
    close(fifo_fd);
    close(socket_fd);
    unlink(socket_name);

    return 0;
}
