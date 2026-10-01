# Linux Device & Process Monitoring System

## 1. Project Overview

The Linux Device & Process Monitoring System is a Linux-based monitoring application developed using C++ and a Linux kernel module written in C.

The system provides a simple interface for monitoring running processes, tracking selected processes, observing Linux device events, checking system resources, and communicating with a custom Linux character device driver.

## 2. Objectives

- Monitor running Linux processes.
- Monitor a selected process and detect when it stops.
- Monitor Linux device events.
- Display CPU, memory, and disk usage.
- Implement a Linux kernel character device driver.
- Demonstrate communication between user-space C++ code and kernel-space driver code.
- Maintain logs for monitoring activities.

## 3. Features

### Process Monitoring
Reads information from the Linux `/proc` filesystem and displays running processes.

### Process Watchdog
Accepts a process ID and monitors the process until it stops. An alert is generated and recorded in the process log.

### Device Monitoring
Monitors Linux device events and displays detected device changes.

### System Resource Monitoring
Displays:
- CPU load
- Memory usage
- Disk usage

### Linux Kernel Driver
A custom Linux character device driver is implemented as a kernel module.

The driver creates:

`/dev/linux_monitor`

The C++ application communicates with the driver using standard Linux file operations such as `open()`, `write()`, and `read()`.

## 4. System Architecture

```text
                 Linux Monitoring Application
                           |
             +-------------+-------------+
             |             |             |
             v             v             v
       Process Monitor  Device Monitor  System Monitor
             |
             v
       Process Watchdog

                           |
                           v
                 C++ Driver Interface
                           |
                    /dev/linux_monitor
                           |
                           v
                 Linux Kernel Module
                  Character Device Driver
