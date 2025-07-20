# Cross-compiler settings
CROSS_COMPILE ?= /home/cuongleduc/buildroot-rv1106/output/host/bin/arm-rockchip830-linux-uclibcgnueabihf-
ARCH ?= arm

# Kernel source directory - update this to your kernel source path
KERNEL_SRC ?= /home/cuongleduc/buildroot-rv1106/output/build/linux-24ab4f26ef4270d678595aee738f15a21c7338d3
# Module name
MODULE_NAME = hello_cdev

# Source files
obj-m += $(MODULE_NAME).o

# Default target
all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

# Clean target
clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean

.PHONY: all clean
