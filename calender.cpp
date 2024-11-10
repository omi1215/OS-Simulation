#include <iostream>
#include <iomanip>

int main() {
    // Get input for the year and month
    int year, month;
    std::cout << "Enter the year: ";
    std::cin >> year;
    std::cout << "Enter the month (1-12): ";
    std::cin >> month;

    // Calculate the total number of days in the month
    int daysInMonth;
    if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else {
        daysInMonth = 31;
    }

    // Calculate the weekday of the first day of the month (Zeller's Congruence)
    int q = 1;  // Day of the month
    int m = month < 3 ? month + 12 : month;
    int K = year % 100;
    int J = year / 100;
    int h = (q + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    // Print the calendar header
    std::cout << "-----------------------------" << std::endl;
    std::cout << "         " << std::setw(4) << year << " " << std::setw(9) << month << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << " Sun Mon Tue Wed Thu Fri Sat" << std::endl;

    // Print the calendar body
    int day = 1;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            if ((row == 0 && col < h) || day > daysInMonth) {
                std::cout << std::setw(4) << " ";
            } else {
                std::cout << std::setw(4) << day;
                day++;
            }
        }
        std::cout << std::endl;

        // Break if all days of the month have been printed
        if (day > daysInMonth) {
            break;
        }
    }

    std::cout << "-----------------------------" << std::endl;
  // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate CALENDER");
   
    return 0;
}

