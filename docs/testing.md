# Testing and Verification

## 1. Build Test

The complete project was built using:

make

The build process generates the C++ applications and the Linux kernel module.

## 2. Process Monitor Test

The process monitor was executed from the main application.

Test:

- Select option 1.
- The application displays currently running Linux processes.
- Process IDs and process names are displayed.

Result:

Process information was displayed successfully.

## 3. Process Watchdog Test

A temporary process was started and its PID was provided to the watchdog.

Example:

sleep 15 &

The watchdog monitored the process.

After the process terminated, the application generated:

ALERT: PID has stopped.

The alert was also recorded in:

logs/process.log

Result:

Process termination was detected successfully.

## 4. Device Monitor Test

The device monitor was started using the main application.

Test:

- Select option 3.
- The application waits for Linux device events.
- Detected device changes are displayed.

Device events were also recorded in:

logs/device.log

Result:

Linux device events were detected successfully.

## 5. System Resource Monitor Test

The system resource monitor was executed using option 4.

The application displayed:

- CPU load
- Memory usage
- Disk usage

Result:

System resource information was displayed successfully.

## 6. Kernel Driver Build Test

The Linux kernel module was built using:

cd driver
make

The generated module was:

monitor_driver.ko

Result:

The kernel module compiled successfully for the running Linux kernel.

## 7. Kernel Driver Loading Test

The driver was loaded using:

sudo insmod monitor_driver.ko

The module was verified using:

lsmod | grep monitor_driver

Result:

The Linux Monitor Driver was loaded successfully.

## 8. Device Node Test

After loading the driver, the following device node was available:

/dev/linux_monitor

The device was verified using:

ls -l /dev/linux_monitor

Result:

The character device was created successfully.

## 9. Driver Read Test

The driver was tested using:

cat /dev/linux_monitor

The driver returned:

Linux Monitor Driver: ACTIVE

Result:

Kernel-space data was successfully read through the device node.

## 10. C++ Driver Communication Test

The main application was executed and option 5 was selected.

The application displayed:

===== Linux Driver Test =====

Driver response: C++ application connected to Linux driver

Result:

Communication between the C++ user-space application and the Linux kernel driver was successfully verified.

## 11. Final Verification

All major project components were tested:

- Process monitoring
- Process watchdog
- Device monitoring
- System resource monitoring
- Kernel module
- Character device
- C++ to kernel communication
- Logging

The project components operated successfully in the Ubuntu Linux environment.
