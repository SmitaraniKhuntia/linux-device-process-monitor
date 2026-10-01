#include "driver_interface.h"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

void testDriver()
{
    int fd = open("/dev/linux_monitor", O_RDWR);

    if (fd < 0)
    {
        perror("Failed to open /dev/linux_monitor");
        return;
    }

    const char *message = "C++ application connected to Linux driver";

    write(fd, message, strlen(message));

    char buffer[256] = {0};

    lseek(fd, 0, SEEK_SET);

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);

    if (bytesRead > 0)
    {
        buffer[bytesRead] = '\0';
        std::cout << "\n===== Linux Driver Test =====\n";
        std::cout << "Driver response: " << buffer;
    }

    close(fd);
}
