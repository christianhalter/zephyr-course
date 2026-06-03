
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT led_switch

LOG_MODULE_REGISTER(led_switch, LOG_LEVEL_INF);

static DEVICE_API(sensor,led_switch_api) = {
	.sample_fetch = led_switch_sample_fetch,
	.channel_get = led_switch_channel_get,
};
