# 04_devicefiles

This is an introduction to device files, device numbers, block & character devices.

## Device files

Device files can be used as an interface between the userspace and a Linux driver or kernel module. Typically the device files live in the /dev folder but they can be created anywhere. Most device files are temporary files and when you turn off your board and navigate into the dev folder, it will be almost empty.

Here is how a regular file looks like when displayed with the ls command:

~~~
~ # ls -l 
-rw-rw-rw-    1 root     root       3932160 Jan  1  1970 mypic_ramos.raw
~~~

The leading *-* indicate, it is a regular file, the next part are the file permissions. The 1 is the number of hardlinks pointing to the file. Then we can see the owners and the group of the file. 3932160 is the size of the file in bytes. Finally we have the last modified date and the filename. 

When looking at device files, the ls output looks a little bit different:

~~~
~ # ls -l /dev
total 0
brw-------    1 root     root        7,   3 Jan  1 00:00 loop3
crw-------    1 root     root      254,   0 Jan  1 00:00 gpiochip0
brw-------    1 root     root       31,   1 Jan  1 00:00 mtdblock1
crw-------    1 root     root       81,  10 Jan  1 00:00 video10
crw-------    1 root     root       81,  23 Jan  1 00:00 v4l-subdev2
v.v..
~~~

The output looks similar but there are two differences. First, the leading letter of the devices.

## Character and block devices

Linux classifies devices into two main types:

| Type        | Prefix | Access Mode      |                   Examples                           |
|-------------|--------|------------------|------------------------------------------------------|
| Character   | `c`    | Byte-stream      | `/dev/video10`, `/dev/gpiochip0`, `/dev/v4l-subdev2` |
| Block       | `b`    | Block-oriented   | `/dev/loop3`, `/dev/mtdblock1`                       |

### Character Devices
Character devices allow access one byte at a time in a sequential manner. They are not buffered by the kernel and are typically used for devices like:
- Serial ports
- GPIO
- Cameras 
- Sensors

Operations: `read()`, `write()`, `ioctl()`

### Block Devices
Block devices support random access and are read/written in blocks (typically 512 bytes or more). They are used for storage media such as:
- Flash memory
- SD cards
- eMMC
- NAND/NOR (via `/dev/mtdblockX`)

Operations: `open()`, `read()`, `write()`, `ioctl()`, often buffered via page cache.

## Device Numbers
Each device file is associated with a pair of numbers:
- **Major number**: Identifies the driver associated with the device.
- **Minor number**: Distinguishes between different devices handled by the same driver.

## Creating Device Files

