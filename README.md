Building
--------

To start run:

 git submodule update --recursive --remote
 west init -l zmk/app
 cd zmk/app/
 west update
 pip install -r ../zephyr/scripts/requirements-base.txt 

Inside a zmk/app directory, run

 west build --pristine -b 5x5x3 -- -DZMK_EXTRA_MODULES=`pwd`/../../zmk-config
