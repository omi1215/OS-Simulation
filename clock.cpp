#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main()
{
  system("tty-clock -Sra 100000000 -d 0");
  system("clear");
  cout << "\t\t\t" << "Press any key to Exit..." << endl;
  cin.ignore(); // Ignore the previous newline character
  cin.get();    // Wait for user input

    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate CLOCK"); 

  return 0;
}

