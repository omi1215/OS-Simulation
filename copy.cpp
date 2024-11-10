#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string sourceFileName, destinationFileName;
    std::cout << "Enter the name of the source file: ";
    std::cin >> sourceFileName;
    std::cout << "Enter the name of the destination file: ";
    std::cin >> destinationFileName;

    std::ifstream sourceFile(sourceFileName);
    if (!sourceFile) {
        std::cerr << "Failed to open the source file." << std::endl;
            system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
             system("./deallocate COPY");
   
        return 1;
    }

    std::ofstream destinationFile(destinationFileName);
    if (!destinationFile) {
        std::cerr << "Failed to create or open the destination file." << std::endl;
               system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate COPY");
   
        return 1;
    }

    std::string line;
    while (std::getline(sourceFile, line)) {
        destinationFile << line << std::endl;
    }

    std::cout << "File copied successfully." << std::endl;

    sourceFile.close();
    destinationFile.close();
 // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate COPY");
   
    return 0;
}

