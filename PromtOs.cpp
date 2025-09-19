#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

void login() {
    string password;
    ofstream outputFile("password.txt");
    
    if (outputFile.is_open()) {
        cout << "Enter password to login: ";
        cin >> password;
        outputFile << password;
        outputFile.close();
    } else {
        cout << "Error: Could not open password file" << endl;
    }
}
int main() {
    bool turn_off = false;
    cin.ignore(); // Clear input buffer

    while (!turn_off) {
        string s;
        cout << "Enter the path: ";
        getline(cin, s);
        if (s == "?help") {
            cout << "Type 'command?' for the list of commands" << endl;
        }
        else if (s == "command?") {
            cout << "open~file.type -- opens a file or an application" << endl;
            cout << "status?sysStatus -- Check system status" << endl;
            cout << "system=(status=bool(0)) -- turn off operating system" << endl;
            cout << "password.change -- Changes password" << endl;
        }

        else if (s == "status?sysStatus") {
            cout << "status -- online" << endl;
            if (system("ping -n 1 google.com > nul") == 0) {
                cout << "WiFi -- connected!" << endl;
            } else {
                cout << "WiFi -- not connected!" << endl;
            }
        }
        else if (s == "system=(status=bool(0))") {
            cout << "turning off..." << endl;
            Sleep(100);
            system("shutdown /s /f /t 0");
            turn_off = true;
        }
        else if (s.substr(0, 5) == "open~")
        {
            string fileType = s.substr(5);
            string command = "start " + fileType;
            system(command.c_str());
        }
        else if (s == "password.change") {
            bool flag = false;
            ifstream pasiExist("passiExist.txt");
            string stored_password;

            if (pasiExist.is_open()) {
                string data;
                pasiExist >> data;
                flag = (data == "true");
                pasiExist.close();
            } else {
                cout << "An error occurred.\nError code: 64'76" << endl;
            }

            if (!flag) {
                // New password creation
                string new_password, confirm_password;
                cout << "New password: ";
                cin >> new_password;
                cout << "Confirm password: ";
                cin >> confirm_password;

                if (confirm_password == new_password) {
                    ofstream infile("password.txt");
                    if (infile.is_open()) {
                        infile << new_password;
                        infile.close();
                        cout << "Password changed successfully!" << endl;
                    } else {
                        cout << "An error occurred.\nError code: 99'108" << endl;
                    }
                } else {
                    cout << "Passwords do not match.\nPlease try again." << endl;
                }
            } else {
                // Change existing password
                string old_password;
                ifstream passFile("password.txt");
                string stored_password;
                
                if (passFile.is_open()) {
                    passFile >> stored_password;
                    passFile.close();

                    cout << "Enter old password: ";
                    cin >> old_password;

                    if (old_password == stored_password) {
                        string new_password, confirm_password;
                        cout << "New password: ";
                        cin >> new_password;
                        cout << "Confirm password: ";
                        cin >> confirm_password;

                        if (confirm_password == new_password) {
                            ofstream outFile("password.txt");
                            if (outFile.is_open()) {
                                outFile << new_password;
                                outFile.close();
                                cout << "Password changed successfully!" << endl;
                            } else {
                                cout << "An error occurred.\nError code: 99'108" << endl;
                            }
                        } else {
                            cout << "Passwords do not match.\nPlease try again." << endl;
                        }
                    } else {
                        cout << "Incorrect old password!" << endl;
                    }
                } else {
                    cout << "An error occurred while reading password file." << endl;
                }
                cin.ignore(); // Clear input buffer after password operations
            }
        }
        else if (!s.empty()) {
            // Run the command directly
            system(s.c_str());
        }
    }
    return 0;
}