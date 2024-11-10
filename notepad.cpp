#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string filename = "note.txt";
    std::ifstream file(filename);
    if (file) {
        std::cout << "File contents:\n";
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        file.close();
    } else {
        std::cout << "File not found!\n";
    }

    std::cout << "Enter text to append to the file (or 'q' to quit):\n";
    std::string text;
    while (std::getline(std::cin, text)) {
        if (text == "q") {
            break;
        }
        std::ofstream outfile(filename, std::ios_base::app);
        outfile << text << '\n';
        outfile.close();
    }
    // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate NOTEPAD");

    return 0;
}

