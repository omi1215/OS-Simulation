#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string filename;
    cout << "Enter the name of the video file to play: ";
    cin >> filename;
    string command = "vlc " + filename + ".mp4 &";
    system(command.c_str());

    // Wait for the user to close the video player
    cout << "Press any key to close the video player...";
    cin.ignore();
    cin.get();

    // Close the video player
    string closeCommand = "killall vlc";
    system(closeCommand.c_str());
   // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate VPLAYER");
    return 0;
}

