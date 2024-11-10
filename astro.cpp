 #include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iomanip>
#include <sys/ioctl.h>
#include<pthread.h>
#include<vector>
#include<string>
#include<semaphore.h>
#include <dirent.h>
#include <cstring>
#include<ncurses.h>

using namespace std;

#define MAX 15

string process_sequence_name[MAX] = { "TOWEROFHANOI", "CALCULATOR", "HANGMAN", "NUMBERGUESSING", "VPLAYER", "QUOTES", "CREATE", "DELETE", "COPY", "CALENDER", "CLOCK", "TICTAC", "RENAME", "NOTEPAD" ,"KERNEL"};
const char* myfifo = "/tmp/myfifo";
long int ram = 0, hdd = 0, cores = 0;
long int need[MAX] = { 0 };
int core_threads = 0;
int active_processes[MAX] = { 0 };
int** active_cores;
bool mode;
int k_choice;
vector<int> readyQueue;
vector<int> waitingQueue;

pthread_t ptid;
pthread_t dispatcher;
pthread_t switcher;

sem_t semaphore;

void printMainMenu();
void displayRunningProcs();


bool check_free_cores()
{
    for (int i = 0; i < cores; ++i)
        for (int j = 0; j < core_threads; ++j)
            if (active_cores[i][j] == -1)
                return true;

    return false;
}

void assign_core(int process)
{
  for (int i = 0; i < cores; ++i)
    for (int j = 0; j < core_threads; ++j)
      if (active_cores[i][j] ==  -1)
      {
        active_cores[i][j] = process;
        return;
      }
}

void dealloc_core(int process)
{
  for (int i = 0; i < cores; ++i)
    for (int j = 0; j < core_threads; ++j)
      if (active_cores[i][j] ==  process)
      {
        active_cores[i][j] = -1;
        return;
      }
}


void display_running_cores(void)
{
  for (int i = 0; i < cores; ++i) {
  for (int j = 0; j < core_threads; ++j) {
    if (active_cores[i][j] != -1) {
      cout << "  /\\_/\\     Core " << i+1 << " is executing:\n"
           << " ( o.o )     Process \"" << process_sequence_name[active_cores[i][j]] << "\"\n"
           << "  > ^ <      --------------------------------\n\n";
    }
  }
}

}

void delete_pipefile()
{
    // This command will delete the file myfifo which exists in tmp in Ubuntu and acts as a named pipe.
    // We are deleting it because we'll create our own.
    if (access(myfifo, F_OK) != -1) {
        system("rm /tmp/myfifo");
        if (unlink(myfifo) != 0) {
            perror("Error deleting file");
        }
    }
}

void release_resources(char* str)
{
   string str1, str2;
int index = -1;

for (int i = 0; i < 15; ++i) {
    str1 = process_sequence_name[i];
    str2 = str;

    if (str1 == str2) {
        index = i;
        break;
    }
}

if (index != -1) {
    system("clear");
    dealloc_core(index);
    sem_wait(&semaphore);
    active_processes[index] -= 1;
    ram += need[index];
    sem_post(&semaphore);
    displayRunningProcs();
    printMainMenu();
}

}

void * thread_for_inter_terminal_comm(void * arg)
{
  int fd;
  const char* myfifo = "/tmp/myfifo";
  mkfifo(myfifo, 0666); //giving permissions

  char arr1[80], arr2[80];
  while (true)
  {

    fd = open(myfifo, O_RDONLY);
    // Read from FIFO
    read(fd, arr1, sizeof(arr1));
    string temp = "notify-send '"+ string(arr1) +" Has Been Closed!'";
    system(temp.c_str());
    release_resources(arr1);
    close(fd);
  }
}




void print_centered(std::string message) {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Get terminal dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Print moon logo
    mvprintw(2, (max_x - 60) / 2, "                           .-^-.");
    mvprintw(3, (max_x - 60) / 2, "                          /_/_\\_\\");
    mvprintw(4, (max_x - 60) / 2, "                       ' ' (o.o) ' '");
    mvprintw(5, (max_x - 60) / 2, "                            (_)");

    // Print initialization message
    mvprintw(8, (max_x - message.length()) / 2, message.c_str());
    refresh();

// Print loading bar
mvprintw(10, (max_x - 20) / 2, "[--------------------]");
for (int i = 0; i < 20; i++) {
    mvprintw(10, (max_x - 4) / 2, "%d%%", (i + 1) * 5);
    if (i % 2 == 0) {
        mvprintw(10, (max_x - 20) / 2 + 1 + i, " ");
    } else {
        mvprintw(10, (max_x - 20) / 2 + 1 + i, "*");
    }
    refresh();
    usleep(100000);
}



    // Clear screen and print welcome message
    clear();
    mvprintw(2, (max_x - 60) / 2, "                           .-^-.");
    mvprintw(3, (max_x - 60) / 2, "                          /_/_\\_\\");
    mvprintw(4, (max_x - 60) / 2, "                       ' ' (o.o) ' '");
    mvprintw(5, (max_x - 60) / 2, "                            (_)");

    mvprintw(8, (max_x - 33) / 2, "Welcome to the ASTRO command center!");
    mvprintw(10, (max_x - 27) / 2, "Initializing core modules...");
    refresh();
    usleep(1000000);

    // Print status messages
    mvprintw(12, (max_x - 16) / 2, "Scanning systems...");
    refresh();
    usleep(1500000);
    mvprintw(14, (max_x - 34) / 2, "Establishing connection to AI servers...");
    refresh();
    usleep(2000000);
    mvprintw(16, (max_x - 35) / 2, "Deploying machine learning algorithms...");
    refresh();
    usleep(2500000);
    mvprintw(18, (max_x - 25) / 2, "Connecting to user interface...");
    refresh();
    usleep(3000000);

    // Print completion message
    mvprintw(20, (max_x - 22) / 2, "Initialization complete!");
    refresh();
    usleep(2000000);

    // Clean up ncurses
    endwin();
}


void shut_down() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Get terminal dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    refresh();
    usleep(2000000);
      mvprintw(2, (max_x - 60) / 2, "                           .-^-.");
    mvprintw(3, (max_x - 60) / 2, "                          /_/_\\_\\");
    mvprintw(4, (max_x - 60) / 2, "                       ' ' (o.o) ' '");
    mvprintw(5, (max_x - 60) / 2, "                            (_)");

    mvprintw(8, (max_x - 33) / 2, "Welcome to the ASTRO command center!");
    mvprintw(10, (max_x - 30) / 2, "Initializing core modules...");
    refresh();
    usleep(1000000);
    // Print shutdown sequence
    mvprintw(10, (max_x - 30) / 2, "Initiating shutdown process...");
    refresh();
    usleep(1500000);
    mvprintw(12, (max_x - 30) / 2, "Saving user preferences...");
    refresh();
    usleep(2000000);
    mvprintw(14, (max_x - 30) / 2, "Closing active connections...");
    refresh();
    usleep(2500000);
    mvprintw(16, (max_x - 30) / 2, "Terminating core modules...");
    refresh();
    usleep(3000000);
    mvprintw(18, (max_x - 30) / 2, "Shutting down system...");
    refresh();
    usleep(4000000);

    // Print completion message
    clear();
    mvprintw(10, (max_x - 22) / 2, "System shutdown complete");
    refresh();
    usleep(2000000);

    // Clean up ncurses
    endwin();
}


void* process_shifter(void* argv)
{
   int process = -1;

while (true) {
    bool foundProcess = false;

    for (int i = 0; i < waitingQueue.size(); ++i) {
        if (need[waitingQueue[i] - 1] <= ram && check_free_cores()) {
            process = waitingQueue[i];
            waitingQueue.erase(waitingQueue.begin() + i);
            readyQueue.push_back(process);
            foundProcess = true;
            break;
        }
    }

    if (!foundProcess) {
        break;
    }
}

}

void displayRunningProcs() {
      bool noProcFlag = true;

system("tput setaf 3");
cout << "\n🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀 CURRENTLY RUNNING PROCESSES 🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀\n\n";
cout << "   💾 Available RAM: " << ram << " MB" << endl;
cout << "   💽 Available Storage: " << hdd << " MB" << endl;
cout << "   💻 Available Cores: " << cores << endl << endl;
display_running_cores();

for (int i = 0; i < 15; ++i) {
    if (active_processes[i]) {
        cout << "   🔥 " << "\033[1;32m" << process_sequence_name[i] << "\033[0m" << " is currently running " << "\033[1;31m" << active_processes[i] << "\033[0m" << " times" << endl;
        noProcFlag = false;
    }
}

if (noProcFlag) {
    cout << "\n   😴 No processes are currently running.\n\n";
}

cout << "🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀\n";
system("tput sgr0");

}

void* dispatch(void* argv)
{
    pid_t  pid;
    string str;
    string temp;
    int active = -1;
    //thread which checks the ready queue and calls the exec file as soon as it gets resources
    while (true)
    {
        if (!readyQueue.empty())
        {
            active = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
        }
        else
            active = -1;

        if (active != -1)
        {
            active_processes[active - 1]++;
            ram -= need[active - 1];
            cout << process_sequence_name[active - 1] << " has been dispatched from the ready queue!" << std::endl;
            assign_core(active - 1);
            system("clear");

            displayRunningProcs();
            //printMainMenu();
            
            
                switch (active)
                {
                case 1:
                    pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./tower";

                        // Check if the executable file exists
                        if (access("tower", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o tower towerofhanoi.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 2:  //Calculator
                     pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./calculator";

                        // Check if the executable file exists
                        if (access("calculator.cpp", F_OK) == -1) {
                            // Compile the program
                                 return 0;
                            system("g++ -o calculator calculator.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 3:  //Tic Tac Toe
                    pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./hangman";

                        // Check if the executable file exists
                        if (access("hangman", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o hangman hangman.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 4: 
                   pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./numberguessing";

                        // Check if the executable file exists
                        if (access("numberguessing", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o numberguessing numberguessing.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 5: //Notepad
                   pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./vplayer";

                        // Check if the executable file exists
                        if (access("vplayer", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o vplayer vplayer.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 6: 
                     pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./quotes";

                        // Check if the executable file exists
                        if (access("quotes", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o quotes quotes.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 7: 
                    pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./create";

                        // Check if the executable file exists
                        if (access("create", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o create create.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }

                    break;
                case 8:  
                     pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./delete";

                        // Check if the executable file exists
                        if (access("delete", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o delete delete.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }    
                    break;
                case 9: 
                     pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./copy";

                        // Check if the executable file exists
                        if (access("copy", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o copy copy.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 10:  //create

                    pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./calender";

                        // Check if the executable file exists
                        if (access("calender", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o calender calender.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }

                    break;
                case 11:  //delete

                     pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./clock";

                        // Check if the executable file exists
                        if (access("clock", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o clock clock.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 12:  //rename

                     pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./tictac";

                        // Check if the executable file exists
                        if (access("titac", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o tictac tictactoe.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }

                    break;
                case 13:

                     pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./rename";

                        // Check if the executable file exists
                        if (access("rename", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o rename rename.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }

                    break;
                case 14:

                    pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./notepad";

                        // Check if the executable file exists
                        if (access("notepad", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o notepad notepad.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                case 15:

                    pid = fork();
                    if (pid == -1)
                    {
                        cout << "Error in forking\n";
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        const char* command = "gnome-terminal";
                        const char* arg1 = "--";
                        const char* arg2 = "sh";
                        const char* arg3 = "-c";
                        const char* arg4 = "./kernel";

                        // Check if the executable file exists
                        if (access("kernel", F_OK) == -1) {
                            // Compile the program
                            system("g++ -o kernel kernel.cpp");
                        }

                        char* args[] = { const_cast<char*>(command), const_cast<char*>(arg1), const_cast<char*>(arg2), const_cast<char*>(arg3), const_cast<char*>(arg4), NULL };
                        execvp(command, args);
                    }
                    break;
                }
        }
            


    }
}


    void printMainMenu()
    {
        system("tput setaf 3");
cout << "\n------------------------------------------------------------\n";
cout << "--------------- WELCOME TO THE ASTRO OS MAIN MENU ---------------\n";
cout << "------------------------------------------------------------\n\n";
system("tput sgr0");

cout << "Welcome to the Interactive Adventure OS!\n\n";
cout << "Choose your next adventure...\n\n";

cout << "Enter 1 for the Tower of Hanoi challenge! Test your skills and conquer the mystical towers!\n";
cout << "Enter 2 for the Calculator. Let's crunch some numbers and solve equations!\n";
cout << "Enter 3 for Hangman. Guess the word and save the poor stick figure!\n";
cout << "Enter 4 for Number Guessing. Can you predict the secret number?\n";
cout << "Enter 5 for the Video Player. Dive into a world of entertainment with movies and shows!\n";
cout << "Enter 6 for to see a Quote. Get Inspired!\n";
cout << "Enter 7 to Create a File. Unleash your creativity and start a new digital masterpiece!\n";
cout << "Enter 8 to Delete a File. Say goodbye to the old and make room for fresh beginnings!\n";
cout << "Enter 9 to Copy a File. Duplicate and preserve your precious memories!\n";
cout << "Enter 10 for the Calendar. Stay organized and plan your days like a pro!\n";
cout << "Enter 11 for the Clock. Keep track of time in style and never miss a beat!\n";
cout << "Enter 12 for Tic Tac Toe. Challenge a friend and become the ultimate champion!\n";
cout << "Enter 13 to Rename a File. Give your files a brand new identity!\n";
cout << "Enter 14 for Notepad. Express your thoughts, ideas, and dreams in digital ink!\n";
cout << "Enter 15 for Kernel Mode lets get authorized!\n";
cout << "Enter 16 to terminate the OS. Goodbye for now!\n";
cout << "\nEnter your choice: ";
cout << endl;

return;

}
    void scheduler(void)
    {
        int choice;
        while (true)
        {
            displayRunningProcs();
            printMainMenu();
            cin >> choice;
            if (choice == 16)
            {
                system("clear");
                pthread_cancel(ptid);
                pthread_cancel(dispatcher);
                pthread_cancel(switcher);
                cout << "Terminating all the processes" << endl;
                sleep(2);
                system("clear");
                 ram= ram + 1024;
                shut_down();
                sleep(2);
                system("killall -9 gnome-terminal-server");
                exit(0);
            }
            if (choice <= 16 && choice >= 1)
            {
                if ((ram >= need[choice - 1]) && check_free_cores())
                {
                    // Ready Queue Implementation
                    readyQueue.push_back(choice);
                }
                else
                {
                    // Waiting Queue Implementation
                    system("notify_send 'NOT ENOUGH SPACE'");
                    waitingQueue.push_back(choice);
                    continue;

                }
            }
        }
    }




    int main()
    {
        delete_pipefile();
        system("clear");
        sem_init(&semaphore,0,1);
       print_centered("Welcome to ASTRO");
        need[0] = 150; 
        need[1] = 50; 
        need[2] = 100; 
        need[3] = 900;
        need[4] = 100; 
        need[5] = 150; 
        need[6] = 100; 
        need[7] = 50; 
        need[8] = 100; 
        need[9] = 50; 
        need[10] = 50; 
        need[11] = 50; 
        need[12] = 50; 
        need[13] = 50; 
        need[14] = 100;
  cout << "Press 1 for user mode and 0 for kernel mode" << endl;
        cin >> mode;
      int mod=0,res;
        if (mode == 0) {
            system("notify-send 'Kernel Mode'");
        
        cout<<"Enter 1 to upate resources or -1 to not"<<endl;
        int c; cin>>c;
         if(c == 1)
         {
            for(int i =0;i<MAX;i++)
             {  
               cout<<i<<" "<<process_sequence_name[i]<<" "<< need[i]<<endl;
              }
            
             while(mod != -1)
            {
             cout<<"Enter the number of the process which you want to change the resources for or -1 to exit"<<endl;
             cin>>mod;
                  if(mod != -1)
               {
              cout<<"Enter the the new resources"<<endl;
             cin>>res;
            need[mod]= res;
             cout<<"to continue press 1 to exit press -1"<<endl;
              cin>>mod;
               }
            }
           
          }
          
}
   system("clear");

        do {
            cout << "Enter RAM in GBs: ";
            cin >> ram;
            cout << endl;

            cout << "Enter HDD in GBs: ";
            cin >> hdd;
            cout << endl;

            cout << "Enter number of cores: ";
            cin >> cores;
            cout << endl;

            cout << "Enter number of threads per core: ";
            cin >> core_threads;;
            cout << endl;

            if (ram == 0) {
                cout << "RAM is insufficient" << endl;
            }

            if (hdd == 0) {
                cout << "HDD is insufficient" << endl;
            }
            if (cores == 0)
                cout << "cores are insufficient" << endl;

            if (core_threads <= 1);
            cout << "threads is insufficient" << endl;
            system("clear");

        } while (ram == 0 || hdd == 0 || core_threads <= 1 || cores == 0);

        ram = ram * 1024; hdd = hdd * 1024;

         ram = ram - 1024;
        system("clear");
         int status;
        pthread_create(&dispatcher, NULL, dispatch, NULL);
        pthread_create(&switcher, NULL, process_shifter, NULL);
        pthread_create(&ptid, NULL, thread_for_inter_terminal_comm, NULL);


        active_cores = new int* [cores];
        for (int i = 0; i < cores; ++i)
            active_cores[i] = new int[core_threads];
        for (int i = 0; i < cores; ++i)
            for (int j = 0; j < core_threads; ++j)
                active_cores[i][j] = -1;


        scheduler();
        pthread_join(ptid, NULL);
        pthread_join(dispatcher, NULL);
        pthread_join(switcher, NULL);

        return 0;

    }
