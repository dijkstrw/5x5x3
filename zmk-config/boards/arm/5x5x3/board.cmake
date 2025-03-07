board_runner_args(blackmagicprobe "--gdb-serial" "blackmagic.lan:2022")
include_directories(include)
include(${ZEPHYR_BASE}/boards/common/blackmagicprobe.board.cmake)