5x5x3
-----

First-time setup;
- clones zmk
- runs `west init`
- fetches zephyr + modules
- pip installs zephyr python modules

 make init

Lean production build;
- BLE
- USB
- kscan in interrupt mode
- no shell

 make build

Debug build;
- logging
- kernel/gpio/bt/settings shells
- RTT over the SWD probe
- polling kscan

 make debug

Flash the resulting firmware to the board via Black Magic Probe at
`blackmagic.lan:2022`:

 make flash

Open a terminal to the keyboard's USB CDC ACM:

 make serial

Debugging
---------
Enable debug logging for zmk:

 log enable dbg zmk

Look at zephyr kernel threads and the amount of stack use of each:

 kernel thread list
 kernel thread stacks
