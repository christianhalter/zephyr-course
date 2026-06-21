#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <led_switch/led_switch.h>

#define SLEEP_TIME_MS CONFIG_APP_HEARTBEAT_PERIOD_MS

/* The devicetree node identifier for the "led_switch" alias. */
#define LED_SWITCH_NODE DT_ALIAS(led_switch)

static const struct device *const led_switch = DEVICE_DT_GET(LED_SWITCH_NODE);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;
    struct sensor_value value;

    if (!device_is_ready(led_switch))
    {
        LOG_ERR("LED Switch is not ready");
        return 0;
    }

    while (1) {

        if (led_state)
        {
            if (sensor_sample_fetch(led_switch, SENSOR_CHAN_ALL)<0)
            {
                LOG_ERR("Sample fetch - LED OFF - failed");
                return 0;
            }
            else
            {
                led_state = false;
            }
        }
        else
        {
            if (sensor_channel_get(led_switch, SENSOR_CHAN_ALL, &value))
            {
                LOG_ERR("Channel get - LED ON - failed");
                return 0;
            }
            else
            {
                led_state = true;
            }
        }

        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}
