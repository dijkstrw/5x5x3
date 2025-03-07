target_sources_ifdef(CONFIG_ZMK_BEHAVIOR_LIGHT_GROUP app PRIVATE src/light-group.c src/color-effect.c)

zephyr_include_directories(include)
