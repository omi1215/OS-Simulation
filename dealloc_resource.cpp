#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
#include <cstring>
using namespace std;
int main(int argc, char** argv)

{
  int fd1;
  const char * myfifo = "/tmp/myfifo";
  mkfifo(myfifo, 0666);

  char str1[80];
  char * str2;
  // while (1)
  // {
    // Now open in write mode and write
    // cout << "ENTER: ";
    fd1 = open(myfifo,O_WRONLY);
    // fgets(str2, 80, stdin);
    write(fd1, argv[1], strlen(argv[1])+1);
    close(fd1);
  // }
  return 0;
}
