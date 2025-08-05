# 06_kernel_logging

This README shows how to use printk with different log levels in a Linux kernel module for the RV1106 SoC (e.g., Luckfox Pico or JetKVM). The module is cross-compiled on an WSL host and tested on an RV1106 device.

You can find the information also in the [Linux Kernel documentation](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html)

## printk Function

Printk is used like this:

~~~
printk(KERN_INFO "Message: %s\n", arg);
~~~

KERN_INFO is the log level used for this line of the kernel logs

## Kernel Log Levels

The following log levels are available:

|     Name     | String |                 Alias function                |
|:------------:|:------:|:---------------------------------------------:|
| KERN_EMERG   | “0”    | pr_emerg()                                    |
| KERN_ALERT   | “1”    | pr_alert()                                    |
| KERN_CRIT    | “2”    | pr_crit()                                     |
| KERN_ERR     | “3”    | pr_err()                                      |
| KERN_WARNING | “4”    | pr_warn()                                     |
| KERN_NOTICE  | “5”    | pr_notice()                                   |
| KERN_INFO    | “6”    | pr_info()                                     |
| KERN_DEBUG   | “7”    | pr_debug() and pr_devel() if DEBUG is defined |
| KERN_DEFAULT | “”     |                                               |
| KERN_CONT    | “c”    | pr_cont()                                     |

## Filtering for log levels

~~~
echo 6 > /proc/sys/kernel/printk
~~~