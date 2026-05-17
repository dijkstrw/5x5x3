PROJECT_ROOT := $(CURDIR)
ZMK_DIR      := $(PROJECT_ROOT)/zmk
ZMK_CONFIG   := $(PROJECT_ROOT)/zmk-config
APP_DIR      := $(ZMK_DIR)/app
ELF          := $(APP_DIR)/build/zephyr/zmk.elf

BOARD := 5x5x3
PROBE := blackmagic.lan:2022
GDB   := /usr/bin/arm-none-eabi-gdb
PIP   := uv pip
WEST  := west

.PHONY: init build debug flash serial clean

init:
	git submodule update --init --recursive zmk
	-cd $(ZMK_DIR) && $(WEST) init -l app
	cd $(ZMK_DIR) && $(WEST) update
	$(PIP) install -r zephyr/scripts/requirements-base.txt

build:
	cd $(APP_DIR) && $(WEST) build --pristine -b $(BOARD) -- \
		-DZMK_EXTRA_MODULES=$(ZMK_CONFIG)

debug:
	cd $(APP_DIR) && $(WEST) build --pristine -b $(BOARD) -S debug -- \
		-DZMK_EXTRA_MODULES=$(ZMK_CONFIG) \
		-DSNIPPET_ROOT=$(ZMK_CONFIG)

flash:
	$(GDB) -silent \
		-ex 'set confirm off' \
		-ex 'target extended-remote $(PROBE)' \
		-ex 'monitor swdp_scan' \
		-ex 'attach 1' \
		-ex 'load $(ELF)' \
		-ex 'kill' \
		-ex 'quit'

serial:
	@dev=$$(ls /dev/serial/by-id/ 2>/dev/null | grep '$(BOARD)' | head -1); \
	if [ -z "$$dev" ]; then \
		echo "No '$(BOARD)' serial device found under /dev/serial/by-id/"; \
		exit 1; \
	fi; \
	echo "Connecting to /dev/serial/by-id/$$dev"; \
	tio "/dev/serial/by-id/$$dev"

clean:
	-cd $(ZMK_DIR) && git clean -fdx
	-git submodule deinit --all -f
	-rm -rf $(ZMK_CONFIG)/.west
