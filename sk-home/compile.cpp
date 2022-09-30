#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

// input:
string PROGRAM_SRC_FILE = "program.cpp";

// output:
//--stdout--

string PROGRAM_EXE_FILE = "program";
string COMPILE_COMMAND = "g++ " + PROGRAM_SRC_FILE + " 2> error.txt";

int main()
{
    if(system(COMPILE_COMMAND.c_str())==-1){
       cout << "error execute:" << COMPILE_COMMAND; return  EXIT_FAILURE;
    }
    
    ifstream f_error("error.txt");
    string line;
 
    if(getline(f_error, line)){
        cout << "compilation error in: " << COMPILE_COMMAND << endl;
        do{cout << line << endl;}while(getline(f_error, line));
        return EXIT_FAILURE;
    }
        
    cout << "compilation Ok" << endl;
    return EXIT_SUCCESS;
}
