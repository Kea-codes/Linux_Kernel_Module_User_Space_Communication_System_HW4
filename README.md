# Linux Kernel Character Device – User-Space Communication (HW4)

**Author:** KEAMOGETSE MAREMELA  
**Student Number:** 221030105  
**Assignment:** Homework 4  

A Linux kernel module that registers a **character device** allowing bidirectional communication between user space and kernel space.

### Features
- Module parameter `name` (default: "Kernel") – passed at load time
- **Write** to the device → kernel stores: `name + user-provided string`
- **Read** from the device → returns the stored combined string
- Implements full set of basic file operations: `open`, `write`, `read`, `release`
- Uses legacy character device registration (`register_chrdev`)

### Key Learning Points
- `module_param()` for passing values from userspace at module load
- Safe memory transfer between kernel and user space (`copy_from_user`, `copy_to_user`)
- Implementing file operations for a character device
- Dynamic major number allocation
- Kernel-side string formatting with `sprintf`

### Requirements
- Linux kernel with development headers installed
  ```bash
  sudo apt update
  sudo apt install linux-headers-$(uname -r) build-essential

### How to build a module
make

sudo insmod main.ko name="HW4"

dmesg | tail -5

#### hello_cdev - MAJOR DEVICE NUMBER: 240

sudo mknod /dev/hello_cdev c 237 0

sudo chmod 666 /dev/hello_cdev

echo "completed assignment" > /dev/hello_cdev

cat /dev/hello_cdev

#### → HW4 completed assignment

sudo rm -f /dev/hello_cdev

sudo rmmod main

  
