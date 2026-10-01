#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    int choice;

    while (true) {
        cout << "\n====================================" << endl;
        cout << "   Linux Device & Process Monitoring" << endl;
        cout << "====================================" << endl;
        cout << "1. View Running Processes" << endl;
        cout << "2. Monitor a Process" << endl;
        cout << "3. Monitor Device Events" << endl;
	cout << "4. System Resource Monitor" << endl;
	cout << "5. Exit" << endl;
        
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                system("./process_monitor");
                break;

            case 2:
                system("./process_watchdog");
                break;

            case 3:
                system("./device_monitor");
                break;
	    case 4:
                system("./system_monitor");
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
