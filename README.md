Building
--------

To start run:

 git submodule update --recursive --remote
 west init -l zmk/app
 cd zmk/app/
 west update
 pip install -r ../zephyr/scripts/requirements-base.txt

Inside a zmk/app directory, run

 west build --pristine -b 5x5x3 -- -DZMK_EXTRA_MODULES=`pwd`/../../zmk-config -DCONFIG_COMPILER_SAVE_TEMPS=y

For a debug build that includes the shell, logging, and ability to inspect zephyr kernel, gpio, bt, and cli over rtt:

 west build --pristine -b 5x5x3 -S debug -- -DZMK_EXTRA_MODULES=/home/dijkstra/project/5x5x3/zmk-config -DSNIPPET_ROOT=/home/dijkstra/project/5x5x3/zmk-config

Serial
------

Start talking to keyboard:

 tio /dev/ttyACM1

Enable debug logging for zmk:

 log enable dbg zmk

Look at zephyr kernel threads and the amount of stack use of each:

 kernel thread list
 kernel thread stacks

