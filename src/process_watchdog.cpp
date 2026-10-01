#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

bool isProcessRunning(const string& pid) {
    string path = "/proc/" + pid + "/status";
    ifstream file(path);
    return file.good();
}

int main() {
    string pid;

    cout << "===== Linux Process Watchdog =====" << endl;
    cout << "Enter PID to monitor: ";
    cin >> pid;

    ofstream logFile("logs/process.log", ios::app);

    if (!logFile) {
        cout << "Unable to open log file." << endl;
        return 1;
    }

    cout << "Monitoring PID " << pid << "..." << endl;
    cout << "Press Ctrl+C to stop." << endl;

    while (true) {
        if (isProcessRunning(pid)) {
            cout << "PID " << pid << " is running." << endl;
        } else {
            cout << "ALERT: PID " << pid << " has stopped." << endl;
            logFile << "ALERT: PID " << pid << " has stopped." << endl;
            break;
        }

        this_thread::sleep_for(chrono::seconds(2));
    }

    logFile.close();

    return 0;
}
