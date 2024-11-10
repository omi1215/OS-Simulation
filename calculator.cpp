#include <iostream>
#include <unistd.h>
#include <stdlib.h> // Added for system() function
#include <string>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
#include <cstring>
using namespace std;

void welcome() {
    // Welcome message and loading animation
    cout << "Welcome to Astro Calculator!\n";
    cout << "Loading...";
    string animation = "|/-\\";
    system("clear");
    for (int i = 0; i < 20; i++) {
        cout << animation[i % 4] << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "\n";
}

int main() {
    welcome();
    bool exitFlag = false;
    while (!exitFlag) {
        // Display menu options
        cout << "Please select an operation:\n";
        cout << "1. Addition (+)\n";
        cout << "2. Subtraction (-)\n";
        cout << "3. Multiplication (*)\n";
        cout << "4. Division (/)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";

        // Get user input
        int choice;
        cin >> choice;

        // Execute chosen operation or exit program
        switch (choice) {
            case 1:
                cout << "Enter two numbers to add:\n";
                float num1, num2;
                cin >> num1 >> num2;
                cout << "Result: " << num1 + num2 << "\n\n";
                break;
            case 2:
                cout << "Enter two numbers to subtract:\n";
                cin >> num1 >> num2;
                cout << "Result: " << num1 - num2 << "\n\n";
                break;
            case 3:
                cout << "Enter two numbers to multiply:\n";
                cin >> num1 >> num2;
                cout << "Result: " << num1 * num2 << "\n\n";
                break;
            case 4:
                cout << "Enter two numbers to divide:\n";
                cin >> num1 >> num2;
                if (num2 == 0) {
                    cout << "Error: division by zero.\n\n";
                } else {
                    cout << "Result: " << num1 / num2 << "\n\n";
                }
                break;
            case 5:
                exitFlag = true;
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 5.\n\n";
                break;
        }
    }
    cin.ignore();
    cout << "\t\t\t" << "Press any key to Exit..." << endl;
    cin.get();

    // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate CALCULATOR");
   
    return 0;
}

