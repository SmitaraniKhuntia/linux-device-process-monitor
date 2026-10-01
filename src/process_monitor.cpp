#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    DIR* directory = opendir("/proc");

    if (directory == nullptr) {
        cout << "Unable to access /proc" << endl;
        return 1;
    }

    cout << "===== Linux Process Monitor =====" << endl;
    cout << "PID\tProcess Name" << endl;
    cout << "-----------------------------" << endl;

    struct dirent* entry;

    while ((entry = readdir(directory)) != nullptr) {
        string name = entry->d_name;

        // Process directories inside /proc have numeric names
        if (all_of(name.begin(), name.end(), ::isdigit)) {
            string statusPath = "/proc/" + name + "/comm";
            ifstream processFile(statusPath);

            string processName;

            if (processFile.is_open()) {
                getline(processFile, processName);
                cout << name << "\t" << processName << endl;
            }
        }
    }

    closedir(directory);

    return 0;
}

