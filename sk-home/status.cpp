#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

// constant input
string TASKS_HOME_DIR = "sk-home";

// input:
string TASK_NUM_FILE = "tasknum.txt";

// output:
//--stdout--
 
string CURRENT_TASK_DIR;
string PROGRAM_OUTPUT = "stdout";
int task_num = -1;

int main()
{ 
    ifstream f_task_num(TASK_NUM_FILE);
    
    if(!f_task_num.is_open()){
        cout << "error opennig file for reading:" << TASK_NUM_FILE << endl;
        return EXIT_FAILURE;
    }
    
    f_task_num >> task_num;
    f_task_num.close();
 
    string home_dir = getenv("HOME");
    TASKS_HOME_DIR = home_dir + "/" + TASKS_HOME_DIR;

    char c_dir_name[10];
    sprintf(c_dir_name,"task%.5i",task_num);
    CURRENT_TASK_DIR = TASKS_HOME_DIR + "/" + c_dir_name;

    DIR* dir=opendir(CURRENT_TASK_DIR.c_str());
    if(!dir){
        cout << "the task directory does not exist:" << CURRENT_TASK_DIR << endl;
        cout << "not a valid task number:" << task_num;
        return EXIT_FAILURE;
    }
    
    closedir(dir);
    
    PROGRAM_OUTPUT = CURRENT_TASK_DIR + "/" + PROGRAM_OUTPUT;
    ifstream f_output_file(PROGRAM_OUTPUT);
    
    if(!f_output_file.is_open()){
        cout << "error opennig file for reading:" << PROGRAM_OUTPUT << endl;
        cout << "the task may not be ready yet";
        return EXIT_FAILURE;
    }
    
    cout << "the task output:" << endl; 
    
    for(string line; getline(f_output_file, line);)cout << line << endl;
    f_output_file.close();
        
    return EXIT_SUCCESS;
}
