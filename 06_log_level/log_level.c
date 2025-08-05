// SPDX-License-Identifier: GPL-2.0
/*
 * log_level.c - Example Linux kernel module to demonstrate printk log levels.
 *
 */

#include <linux/module.h>
#include <linux/init.h>

static int __init log_level_init(void)
{
pr_emerg("RV1106: Emergency message\n");
    pr_alert("RV1106: Alert message\n");
    pr_crit("RV1106: Critical message\n");
    pr_err("RV1106: Error message\n");
    pr_warn("RV1106: Warning message\n");
    pr_notice("RV1106: Notice message\n");
    pr_info("RV1106: Info message\n");
    pr_debug("RV1106: Debug message\n");
    pr_cont("RV1106: Continuation message\n");
    return 0;

	return 0;
}

static void __exit log_level_exit(void)
{
	pr_info("RV1106: Unloading logging module\n");
}

module_init(log_level_init);
module_exit(log_level_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cuong Le Duc <cuong.le@ologn.tech>");
MODULE_DESCRIPTION("A demo Linux kernel module showing printk log levels");

