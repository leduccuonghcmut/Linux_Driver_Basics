# 06_hello_cdev

This is a Linux kernel module named hello_cdev that registers a character device. When the device file is opened, it logs the major and minor numbers, file position, mode, and flags. When the device file is closed, it logs a closure message. This module serves as a basic example of a character device driver for educational purposes. This example can be compiled and run on a Luckfox Pico Max/mini RV1106.

## Explaining the code

In the `struct file_operations fops` we can set callback functions for various syscalls, like `open`, `read`, `write`, `close`, ... For our character device we have overloaded the `open` function which will be called, when we call the `open` functions for the device file linked to the character device over the device number from userspace and the `release` function, which will be called when we call `close` from userspace.

Here are the prototypes of the callback functions we want to implement:

~~~
int my_open(struct inode *inode, struct file *filp);
int my_release(struct inode *inode, struct file *filp);
~~~

Both functions return 0 on success, else a negative error code. The arguments are also identical. Here is an explanation of the arguments and also some important fields:

- `struct inode *inode`: Kernel representation of a file. We can get the Major and Minor Device numbers from it
- `struct file *filp`: Represents the opened file. Important fields are:
    - `f_mode`: File permissions, e.g. read, write, ...
    - `f_ops`: Pointer to the file operations associated with this file
    - `f_pos`: Current position in file (0 on open)
    - `f_flags`: Flags set by the userspace `open` function, e.g. `O_RDONLY`, `O_RDWR`, ...

The major and minor device number can be read out the `inode`with the function `imajor` and `iminor`.

The file operations are bundled in the `fops` struct. 

