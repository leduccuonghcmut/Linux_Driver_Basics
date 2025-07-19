#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>
#include <linux/timer.h>

#define IO_LED       23
#define IO_OFFSET    32
#define MAX_COUNT    70
#define TIME_DELAY   1000  // milliseconds

static struct gpio_desc *led_gpio;
static struct timer_list blink_timer;
static int blink_count = 0;
static bool led_state = false;

static void timer_callback(struct timer_list *t)
{
	if (blink_count >= MAX_COUNT) {
		gpiod_set_value(led_gpio, 0);
		pr_info("gpioctrl: Stopped after %d cycles\n", blink_count);
		return;
	}

	led_state = !led_state;
	gpiod_set_value(led_gpio, led_state);

	if (led_state) {
		blink_count++;
		pr_info("gpioctrl: LED ON (Cycle %d/%d)\n", blink_count, MAX_COUNT);
	}

	mod_timer(&blink_timer, jiffies + msecs_to_jiffies(TIME_DELAY));
}

static int __init my_init(void)
{
	int ret;

	led_gpio = gpio_to_desc(IO_LED + IO_OFFSET);
	if (!led_gpio) {
		pr_err("gpioctrl: Failed to get GPIO descriptor for pin %d\n", IO_LED);
		return -ENODEV;
	}

	ret = gpiod_direction_output(led_gpio, 0);
	if (ret) {
		pr_err("gpioctrl: Failed to set GPIO %d as output\n", IO_LED);
		return ret;
	}

	timer_setup(&blink_timer, timer_callback, 0);

	ret = mod_timer(&blink_timer, jiffies + msecs_to_jiffies(TIME_DELAY));
	if (ret) {
		pr_err("gpioctrl: Failed to start timer\n");
		return ret;
	}

	pr_info("gpioctrl: Module initialized successfully\n");
	return 0;
}

static void __exit my_exit(void)
{
	del_timer_sync(&blink_timer);
	gpiod_set_value(led_gpio, 0);
	pr_info("gpioctrl: Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cuong LeDuc");
MODULE_DESCRIPTION("An example of using GPIOs without the Device Tree");
