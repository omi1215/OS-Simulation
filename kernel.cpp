#include <iostream>
#include <unistd.h>
#include <stdlib.h> // Added for system() function
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <dirent.h> // Added for opendir() and readdir()
#include <vector> // Added for vector
#include <signal.h>
#include <limits>

using namespace std;

bool is_running(pid_t pid) {
    char status_path[64];
    sprintf(status_path, "/proc/%d/status", pid);
    if (access(status_path, F_OK) != -1) {
        // Process is still running
        int status_file = open(status_path, O_RDONLY);
        if (status_file != -1) {
            close(status_file);
            return true;
        }
    }
    return false;
}

int main() {
    system("tput setaf 3");
    cout << "\n------------------------------------------------------------\n";
    cout << "--------------- KERNEL PANEL ---------------\n";
    cout << "------------------------------------------------------------\n\n";
    system("tput sgr0");

    cout << "\n \n Processes running with cmdline ./obj:\n";

    DIR* dir = opendir("/proc");
    if (!dir) {
        cerr << "Failed to open directory /proc.\n";
        return -1;
    }

    struct dirent* ent;
    vector<pid_t> pids;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type != DT_DIR) {
            continue;
        }
        const string pid_str = ent->d_name;
        if (pid_str.find_first_not_of("0123456789") != string::npos) {
            continue;
        }
        const pid_t pid = stoi(pid_str);
        char cmdline_path[64];
        sprintf(cmdline_path, "/proc/%d/cmdline", pid);
        FILE* cmdline_file = fopen(cmdline_path, "r");
        if (!cmdline_file) {
            continue;
        }
        char cmdline[1024];
        const size_t len = fread(cmdline, 1, sizeof(cmdline), cmdline_file);
        fclose(cmdline_file);
        if (len == 0) {
            continue;
        }
        cmdline[len] = '\0';
        if (strstr(cmdline, "./") == cmdline && strstr(cmdline, "./obj") != cmdline + 2) {
            if (is_running(pid)) {
                pids.push_back(pid);
                cout << pid << " " << cmdline << endl;
            }
        }
    }
    closedir(dir);

    string name;
    int pid;
    while (true) {
        cout << "Enter the process name PID to deallocate resources (or -1 to exit): ";
        if (!(cin >> name && cin >> pid) || name == "-1" || pid == -1) {
            break;
        }
        if (kill(pid, SIGTERM) == -1) {
            cerr << "Failed to kill process with PID " << pid << endl;
            continue;
        }
        string deallocate_cmd = "./help " + name; // Need to convert char* to string
        string compile_cmd = "g++ -o help helper.cpp";
        system(compile_cmd.c_str()); 
        system(deallocate_cmd.c_str());  
    }

    cin.ignore();
    cout << "\t\t\t" << "Press any key to Exit..." << endl;
    cin.get();

    // Deallocate resources for the kernel process
    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate KERNEL");

    return 0;
}

