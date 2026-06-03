
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

static int led_switch_channel_get(const struct device *dev,
                                 enum sensor_channel chan,
                                 struct sensor_value *val)
{
    const struct led_switch_config *cfg = dev->config;
    struct led_switch_data *data = dev->data;
    gpio_pin_set_dt(&cfg->led, 1);
    data->led_state = true;
	LOG_INF("LED ON");
	return 0;
}

static int nn_driver_sample_fetch(const struct device *dev,
                                  enum sensor_channel chan)
{
    const struct led_switch_config *cfg = dev->config;
    struct led_switch_data *data = dev->data;
    gpio_pin_set_dt(&cfg->led, 0);
    data->led_state = false;
    LOG_INF("LED OFF");
	return 0;
}

static DEVICE_API(sensor,led_switch_api) = {
	.sample_fetch = led_switch_sample_fetch,
	.channel_get = led_switch_channel_get,
};
