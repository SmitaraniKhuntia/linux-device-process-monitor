# Implementation Details

## 1. Process Monitoring

The process monitor uses the Linux `/proc` filesystem to obtain information about currently running processes.

Process directories are identified using numeric process IDs (PIDs).

The monitor reads process information and displays the PID and process name.

## 2. Process Watchdog

The process watchdog accepts a PID from the user and periodically checks whether the process is still running.

When the monitored process stops, the program generates an alert and records the event in:

logs/process.log

This provides a simple process lifecycle monitoring mechanism.

## 3. Device Monitoring

The device monitor listens for Linux device events and displays detected device changes.

Detected events are also recorded in:

logs/device.log

This allows the application to observe changes in the Linux device environment.

## 4. System Resource Monitoring

The system monitor displays basic system resource information:

- CPU load
- Memory usage
- Disk usage

This provides a quick overview of the current system state.

## 5. Linux Kernel Module

The project includes a custom Linux kernel module written in C.

The module implements a character device using the Linux misc device framework.

The device is registered with the kernel and exposed to user space as:

/dev/linux_monitor

## 6. File Operations

The driver implements read and write operations through the Linux file operations structure.

The read operation transfers information from the kernel-space driver buffer to user space.

The write operation receives information from the user-space application and stores it in the driver buffer.

## 7. User-Kernel Data Transfer

The driver uses:

- copy_to_user() for transferring data from kernel space to user space.
- copy_from_user() for transferring data from user space to kernel space.

These functions provide the controlled transfer of data across the user/kernel boundary.

## 8. Synchronization

A kernel mutex protects the shared driver buffer.

The mutex is acquired before reading or modifying the buffer and released after the operation is completed.

This prevents concurrent access from corrupting the shared data.

## 9. C++ Driver Interface

The C++ driver interface opens:

/dev/linux_monitor

It sends a message to the driver using write() and then reads the driver's response using read().

The interface is connected to the main application through the Kernel Driver Test menu option.

## 10. Build System

The project uses Makefiles to simplify compilation.

The main Makefile builds:

- Main monitoring application
- Process monitor
- Process watchdog
- Device monitor
- System monitor
- Linux kernel module

The driver has its own Makefile for building the kernel module against the currently running Linux kernel.

## 11. Project Integration

The final application combines Linux monitoring functionality with a custom kernel module.

The monitoring components operate in user space, while the character device driver operates in kernel space.

The C++ driver interface provides the communication bridge between the two layers.
