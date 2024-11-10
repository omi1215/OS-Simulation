#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Array of quotes
    const char* quotes[] = {
        "Be yourself; everyone else is already taken. - Oscar Wilde",
        "Two things are infinite: the universe and human stupidity; and I'm not sure about the universe. - Albert Einstein",
        "In the end, it's not the years in your life that count. It's the life in your years. - Abraham Lincoln",
        "The only way to do great work is to love what you do. - Steve Jobs",
        "Believe you can and you're halfway there. - Theodore Roosevelt"
    };

    // Get the number of quotes
    const int numQuotes = sizeof(quotes) / sizeof(quotes[0]);

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random index
    int randomIndex = std::rand() % numQuotes;

    // Print the random quote
    std::cout << "Random Quote of the Day:\n";
    std::cout << quotes[randomIndex] << std::endl;

   std::cin.ignore();
    std::cout << "\t\t\t" << "Press any key to Exit..." << std::endl;
    std::cin.get();

  // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate QUOTES");
    return 0;
}

