#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Generate a random number between 1 and 100
    srand(static_cast<unsigned int>(time(0)));
    int secretNumber = rand() % 100 + 1;

    int guess;
    int attempts = 0;

    
std::cout<<"To Quit enter 0"<<std::endl;
int n; std::cin>>n;
while(n != 0)
{std::cout << "Welcome to the Number Guessing Game!" << std::endl;
    // Game loop
    while (true) {
        std::cout << "Enter your guess (1-100): ";
        std::cin >> guess;

        attempts++;

        if (guess == secretNumber) {
            std::cout << "Congratulations! You guessed the correct number in " << attempts << " attempts." << std::endl;
            break;
        } else if (guess < secretNumber) {
            std::cout << "Too low! Try again." << std::endl;
        } else {
            std::cout << "Too high! Try again." << std::endl;
        }
    }
    std::cout<<"to play exit enter 0"<<std::endl;
    std::cin>>n;
   if(n != 0)
system("clear");
}
// Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate NUMBERGUESSING");
   
    return 0;
}

