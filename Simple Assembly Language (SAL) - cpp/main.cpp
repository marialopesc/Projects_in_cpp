#include <iostream>
#include <string>
#include "ALI.hpp"

using namespace std;


int main() {
    ALI ali;


    // Prompt for and load a SAL program from a specified file
    cout << "Enter the filename of the SAL program: ";
    string filename;
    getline(cin, filename);
    ali.load_program(filename);


    // Main loop to process commands from the user
    while (true) {
        cout << "Enter command (s = step, a = run all, q = quit): ";
        string command;
        getline(cin, command);

        // Execute one instruction at a time
        if (command == "s") {
            ali.step(true);
        }

        // Execute all instructions until halt or end of program
        else if (command == "a") {
            ali.run();
            ali.print_state();
        }


        // Exit the program
        else if (command == "q") {
            cout << "Quitting...\n";
            break;
        }

        // Handle unrecognized commands
        else {
            cout << "Invalid command.\n";
        }

        // Check if program has been set to halt for sfety
        if (ali.halt_program) {
            break;
        }
    }

    return 0;
}


