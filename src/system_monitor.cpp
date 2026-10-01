#include <iostream>
#include <fstream>
#include <string>
#include <sys/statvfs.h>

using namespace std;

void showMemory() {
    ifstream file("/proc/meminfo");

    string line;
    long total = 0;
    long available = 0;

    while (getline(file, line)) {
        if (line.find("MemTotal:") == 0)
            total = stol(line.substr(10));

        if (line.find("MemAvailable:") == 0)
            available = stol(line.substr(14));
    }

    long used = total - available;

    cout << "Memory Usage : "
         << used / 1024 << " MB / "
         << total / 1024 << " MB" << endl;
}

void showDisk() {
    struct statvfs disk;

    if (statvfs("/", &disk) == 0) {
        unsigned long long total =
            disk.f_blocks * disk.f_frsize;

        unsigned long long freeSpace =
            disk.f_bavail * disk.f_frsize;

        unsigned long long used = total - freeSpace;

        cout << "Disk Usage   : "
             << used / (1024 * 1024 * 1024)
             << " GB / "
             << total / (1024 * 1024 * 1024)
             << " GB" << endl;
    }
}

void showCPU() {
    ifstream file("/proc/loadavg");

    double load1;

    if (file >> load1) {
        cout << "CPU Load     : "
             << load1 << endl;
    }
}

int main() {
    cout << "====================================" << endl;
    cout << "       Linux System Monitor" << endl;
    cout << "====================================" << endl;

    showCPU();
    showMemory();
    showDisk();

    return 0;
}
