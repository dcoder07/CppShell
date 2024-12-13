#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdlib> // For getenv

using namespace std;

// Function to check if the command is a valid shell builtin
bool isValid(string command) {
    string str = command.substr(0, command.find(" "));
    return (str == "type" || str == "echo" || str == "exit" || str == "cd");
}

// Function to get the absolute path of a command from the PATH environment variable
string getPathEnv(string command) {
    string path_env = getenv("PATH");
    stringstream ss(path_env);
    string temp;

    while (getline(ss, temp, ':')) { // Tokenize PATH variable
        string commandPath = temp + '/' + command;
        if (filesystem::exists(commandPath)) {
            return commandPath;
        }
    }
    return "";
}

int main() {
    bool exitShell = false;

    while (!exitShell) {
        cout << "$ "; // Shell prompt
        string input;
        getline(cin, input);

        if (input.empty()) {
            continue; // Ignore empty input
        }

        string command = input.substr(0, input.find(" ")); // Extract command name
        string args = input.substr(input.find(" ") + 1);   // Extract arguments

        if (command == "cd") {
            cout << "cd: command not implemented yet" << endl;
        } else if (command == "echo") {
            cout << args << endl;
        } else if (command == "exit") {
            exitShell = true; // Exit the shell
        } else if (command == "type") {
            if (isValid(args)) {
                cout << args << " is a shell builtin" << endl;
            } else {
                string path = getPathEnv(args);
                if (!path.empty()) {
                    cout << args << " is " << path << endl;
                } else {
                    cout << args << ": command not found" << endl;
                }
            }
        } else {
            string path = getPathEnv(command);
            if (!path.empty()) {
                cout << command << " found at: " << path << endl;
            } else {
                cout << command << ": command not found" << endl;
            }
        }
    }

    return 0;
}
