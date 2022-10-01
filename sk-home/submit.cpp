#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

// constant input
string TASKS_HOME_DIR = "sk-home";
string CURRENT_TASK_NUM_FILE = "sk-home/CURRENT_TASK_NUM_FILE.txt";

// input:
string PROGRAM_SRC_FILE = "program.cpp";

// output:
string TASK_NUM_FILE = "tasknum.txt";
//--stdout--

string PROGRAM_EXE_FILE = "program";
string PROGRAM_BAT_FILE = "slurm.batch";
string COMPILE_COMMAND = "g++ " + PROGRAM_SRC_FILE + " -o " + PROGRAM_EXE_FILE + " 2> error.txt";

string CURRENT_TASK_DIR;
int cur_task_num = -1;

int main()
{
    if(system(COMPILE_COMMAND.c_str())==-1){
       cout << "error execute:" << COMPILE_COMMAND; return  EXIT_FAILURE;
    }
    
    ifstream f_error("error.txt");
    string line;
 
    if(getline(f_error, line)){
        cout << "compilation error:" << COMPILE_COMMAND << endl;
        do{cout << line << endl;}while(getline(f_error, line));
        return EXIT_FAILURE;
    }
    
    string home_dir = getenv("HOME");
    TASKS_HOME_DIR = home_dir + "/" + TASKS_HOME_DIR;
    CURRENT_TASK_NUM_FILE = home_dir + "/" + CURRENT_TASK_NUM_FILE;
    
    ifstream f_cur_task_num(CURRENT_TASK_NUM_FILE.c_str());
    
    if(!f_cur_task_num.is_open()){
        cout << "error opennig file for reading:" << CURRENT_TASK_NUM_FILE << endl;
        return EXIT_FAILURE;
    }
    
    f_cur_task_num >> cur_task_num;
    f_cur_task_num.close();
            
    char c_dir_name[10];
    sprintf(c_dir_name,"task%.5i",cur_task_num);
    CURRENT_TASK_DIR = TASKS_HOME_DIR + "/" + c_dir_name;
    
    if(mkdir(CURRENT_TASK_DIR.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0){
        cout << "error cannot create dir:" << CURRENT_TASK_DIR << endl;
        return  EXIT_FAILURE;
    }

    ofstream f_task_num(TASK_NUM_FILE.c_str());
    if(!f_task_num.is_open()){
        cout << "error opennig file for writing:" << TASK_NUM_FILE << endl;
        return EXIT_FAILURE;    
    }
    f_task_num << cur_task_num;
    f_task_num.close();
    
    string MOVED_PROGRAM_EXE_FILE = CURRENT_TASK_DIR + "/" + PROGRAM_EXE_FILE;
    
    if(rename(PROGRAM_EXE_FILE.c_str(), MOVED_PROGRAM_EXE_FILE.c_str())){
        cout << "error cannot move file from:" << PROGRAM_EXE_FILE << endl;
        cout << "to:" << MOVED_PROGRAM_EXE_FILE << endl;
        return  EXIT_FAILURE;
    }
    
    string MOVED_PROGRAM_SRC_FILE = CURRENT_TASK_DIR + "/" + PROGRAM_SRC_FILE;
    
    if(rename(PROGRAM_SRC_FILE.c_str(), MOVED_PROGRAM_SRC_FILE.c_str())){
        cout << "error cannot move file from:" << PROGRAM_EXE_FILE << endl;
        cout << "to:" << MOVED_PROGRAM_EXE_FILE << endl;
        return  EXIT_FAILURE;
    }
    
    PROGRAM_BAT_FILE = CURRENT_TASK_DIR + "/" + PROGRAM_BAT_FILE;
    ofstream f_bat_file(PROGRAM_BAT_FILE.c_str());
    
    if(!f_bat_file.is_open()){
        cout << "error opennig file for writing:" << PROGRAM_BAT_FILE << endl;
        return EXIT_FAILURE; 
    }
        
    f_bat_file << "#!/bin/bash" << endl;
    //////////////////// todo: add slurm commands here //////////////////////
    f_bat_file.close();
	
	//////////////////// todo: add slurm run here //////////////////////
    
    ofstream f_cur_task_num_new(CURRENT_TASK_NUM_FILE.c_str(),ios::trunc);
    
    if(!f_cur_task_num_new.is_open()){
        cout << "error opennig file for writing:" << CURRENT_TASK_NUM_FILE << endl;
        return EXIT_FAILURE;    
    }
    
    f_cur_task_num_new << ++cur_task_num;
    f_cur_task_num_new.close();
    
    cout << "submit Ok" << endl;
        
    return EXIT_SUCCESS;
}
