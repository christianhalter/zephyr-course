#pragma ONCE

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C"{
#endif

static int led_switch_channel_get(const struct device *dev,
                                 enum sensor_channel chan,
                                 struct sensor_value *val);

static int led_switch_sample_fetch(const struct device *dev,
                                  enum sensor_channel chan);

static int led_switch_init(const struct device *dev);

#ifdef __cplusplus
}
#endif
