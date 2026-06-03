
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT led_switch

LOG_MODULE_REGISTER(led_switch, LOG_LEVEL_INF);

struct led_switch_config {
    struct gpio_dt_spec led;
};

struct led_switch_data {
    bool led_state;
};

static DEVICE_API(sensor,led_switch_api) = {
	.sample_fetch = led_switch_sample_fetch,
	.channel_get = led_switch_channel_get,
};
