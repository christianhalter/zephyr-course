
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT led_switch

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "LED Switch driver enabled without any devices"
#endif

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

static int led_switch_sample_fetch(const struct device *dev,
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

static int led_switch_init(const struct device *dev)
{
	const struct led_switch_config *cfg = dev->config;
	int ret;
	if (!gpio_is_ready_dt(&cfg->led)) {
		LOG_ERR("GPIO device not ready");
		return -ENODEV;
	}
	ret = gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		LOG_ERR("Failed to configure LED GPIO: %d", ret);
		return ret;
	}
	return 0;
}

#define LED_SWITCH_DEFINE(inst)                                         \
	static struct led_switch_data led_switch_data_##inst;               \
	static const struct led_switch_config led_switch_config_##inst = {  \
		.led = GPIO_DT_SPEC_INST_GET(inst, gpios),                      \
	};                                                                  \
	DEVICE_DT_INST_DEFINE(inst, led_switch_init, NULL,                  \
				     &led_switch_data_##inst,                           \
				     &led_switch_config_##inst, POST_KERNEL,            \
				     CONFIG_SENSOR_INIT_PRIORITY, &led_switch_api);

DT_INST_FOREACH_STATUS_OKAY(LED_SWITCH_DEFINE);
