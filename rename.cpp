#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string fileName;
    string extension;
    string newName;
    int choice;

    cout << "Enter File Name: ";
    cin >> fileName;

    do {
        cout << "Select extension:" << endl
             << "1. Text (.txt)" << endl
             << "2. Data (.dat)" << endl
             << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            extension = ".txt";
        } else if (choice == 2) {
            extension = ".dat";
        } else {
            cout << "Wrong Extension" << endl;
        }
    } while (choice < 1 || choice > 2);

    fileName = fileName + extension;
    ifstream temp;
    temp.open(fileName);

    if (temp.fail()) {
        cout << "No file with this name exists" << endl;
    } else {
        cout << "Enter New Name of File: ";
        cin >> newName;
        temp.close();
        rename(fileName.c_str(), newName.c_str());
    }

    cin.ignore();
    cout << "\t\t\t" << "Press any key to Exit..." << endl;
    cin.get();

    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate RENAME");

    return 0;
}

