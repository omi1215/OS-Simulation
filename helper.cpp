#include <iostream>
#include <string> // Need to include this header to use string class
#include <cstdlib> // Need to include this header to use system function

using namespace std;

int main(int argc, char* argv[])
{
    string deallocate_cmd = "./deallocate " + string(argv[1]); // Need to convert char* to string
    string compile_cmd = "g++ -o deallocate dealloc_resource.cpp";
    system(compile_cmd.c_str()); // Need to add a closing parenthesis after the function call
    system(deallocate_cmd.c_str()); // Need to add a closing parenthesis after the function call
    return 0;
}

