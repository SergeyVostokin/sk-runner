#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

string TASKS_HOME_DIR = "/sk-home/";
string CURRENT_TASK_NUM_FILE = "/sk-home/CURRENT_TASK_NUM_FILE.txt";

string PROGRAM_SRC_FILE = "program.cpp";
string PROGRAM_EXE_FILE = "program";

string CURRENT_TASK_DIR;

int cur_task_num;
string command;

int main()
{
    string home_dir = getenv("HOME");
    TASKS_HOME_DIR = home_dir + TASKS_HOME_DIR;
    CURRENT_TASK_NUM_FILE = home_dir + CURRENT_TASK_NUM_FILE;
    
    ifstream f_cur_task_num(CURRENT_TASK_NUM_FILE);
    
    if(!f_cur_task_num.is_open()){
        cout << "error opennig file for reading:" << CURRENT_TASK_NUM_FILE << endl;
        return EXIT_FAILURE;
    }
    
    f_cur_task_num >> cur_task_num;
    f_cur_task_num.close();
            
    char c_dir_name[10];
    sprintf(c_dir_name,"task%.5i",cur_task_num);
    CURRENT_TASK_DIR = TASKS_HOME_DIR + c_dir_name;
    
    PROGRAM_SRC_FILE = home_dir + "/" + PROGRAM_SRC_FILE;
    PROGRAM_EXE_FILE = CURRENT_TASK_DIR + "/" + PROGRAM_EXE_FILE;        
   
    if(mkdir(CURRENT_TASK_DIR.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0){
        cout << "error cannot create dir:" << CURRENT_TASK_DIR << endl;
        return  EXIT_FAILURE;
    }
	
	command = "g++ " + PROGRAM_SRC_FILE + " -o " + PROGRAM_EXE_FILE;
	
	if(system(command.c_str())==-1){
		cout << "error execute:" << command; return  EXIT_FAILURE;
	}
        
    ofstream f_cur_task_num_new(CURRENT_TASK_NUM_FILE,ios::trunc);
    
    if(!f_cur_task_num_new.is_open()){
        cout << "error opennig file for writing:" << CURRENT_TASK_NUM_FILE << endl;
        return EXIT_FAILURE;    
    }
    
    f_cur_task_num_new << ++cur_task_num;
    f_cur_task_num_new.close();
        
    return EXIT_SUCCESS;
}