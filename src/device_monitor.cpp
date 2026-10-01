#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

using namespace std;

int main() {
    int socketFd;
    char buffer[4096];

    socketFd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);

    if (socketFd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_nl address{};
    address.nl_family = AF_NETLINK;
    address.nl_pid = getpid();
    address.nl_groups = 1;

    if (bind(socketFd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Socket bind failed");
        close(socketFd);
        return 1;
    }

    ofstream logFile("logs/device.log", ios::app);

    if (!logFile) {
        cout << "Unable to open device log file." << endl;
        close(socketFd);
        return 1;
    }

    cout << "===== Linux Device Monitor =====" << endl;
    cout << "Waiting for device events..." << endl;
    cout << "Press Ctrl+C to stop." << endl;

    while (true) {
        ssize_t length = recv(socketFd, buffer, sizeof(buffer) - 1, 0);

        if (length > 0) {
            buffer[length] = '\0';

            cout << "\n[DEVICE EVENT]" << endl;
            cout << buffer << endl;

            logFile << "[DEVICE EVENT]\n";
            logFile << buffer << "\n";
            logFile.flush();
        }
    }

    logFile.close();
    close(socketFd);

    return 0;
}
