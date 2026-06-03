#if(CONFIG_LED_SWITCH)
#    target_sources(app PRIVATE led_switch.c)
#endif()

zephyr_library()
zephyr_library_sources(led_switch.c)