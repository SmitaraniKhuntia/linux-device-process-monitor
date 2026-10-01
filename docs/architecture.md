# System Architecture

## 1. Overview

The Linux Device & Process Monitoring System consists of a C++ user-space monitoring application and a Linux kernel character device driver.

The application provides process monitoring, process watchdog functionality, device event monitoring, system resource monitoring, and communication with the kernel driver.

## 2. High-Level Architecture

Linux Monitoring Application
        |
        +-------------------+
        |         |         |
        v         v         v
Process Monitor  Device Monitor  System Monitor
        |
        v
Process Watchdog

        |
        v
C++ Driver Interface
        |
        v
/dev/linux_monitor
        |
        v
Linux Kernel
        |
        v
Character Device Driver

## 3. User Space

The main application and monitoring components operate in user space.

The user-space components are:

- Process Monitor
- Process Watchdog
- Device Monitor
- System Resource Monitor
- C++ Driver Interface

The main application provides a menu through which these components can be accessed.

## 4. Kernel Space

The project contains a Linux kernel module implemented in C.

The module implements a character device using the Linux misc device framework and creates the device node:

/dev/linux_monitor

The driver provides read and write operations for communication with the user-space application.

## 5. User Space to Kernel Space Communication

The C++ driver interface opens the device using open().

It sends information to the driver using write() and receives information using read().

The communication path is:

C++ Application
       |
       | open()
       | write()
       | read()
       v
/dev/linux_monitor
       |
       v
Linux Character Device Driver
       |
       v
Linux Kernel

## 6. Synchronization

A kernel mutex is used inside the driver to protect the shared driver buffer during read and write operations.

This prevents simultaneous access from causing inconsistent data.

## 7. Logging

Monitoring events are stored in the logs directory.

- process.log stores process watchdog alerts.
- device.log stores detected device events.

## 8. Architecture Summary

The project combines Linux system-level monitoring with a custom kernel module.

The monitoring components provide system information, while the character device driver demonstrates direct communication between user space and kernel space.
