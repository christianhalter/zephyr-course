#pragma ONCE

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C"{
#endif

struct led_switch_api {
	int (*channel_get)(const struct device *dev, enum sensor_channel chan, struct sensor_value *val);
	int (*sample_fetch)(const struct device *dev, enum sensor_channel chan);
};

int led_switch_channel_get(const struct device *dev,
                                 enum sensor_channel chan,
                                 struct sensor_value *val);

int led_switch_sample_fetch(const struct device *dev,
                                  enum sensor_channel chan);

int led_switch_init(const struct device *dev);

#ifdef __cplusplus
}
#endif
