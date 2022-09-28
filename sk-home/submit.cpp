#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

string TASKDIRS = "/taskdir/";
string LASTTASK = "/taskdir/lasttask.txt";
string PROGFILE = "program.cpp";

string CURTASKDIR;
string CURPROGFILE;
int last_task;

int main()
{
    string home_dir = getenv("HOME");
    TASKDIRS = home_dir + TASKDIRS;
    LASTTASK = home_dir + LASTTASK;
    
    ifstream f_last_task(LASTTASK);
    
    if(!f_last_task.is_open()){
        cout << "error opennig file for reading:" << LASTTASK << endl;
        return EXIT_FAILURE;
    }
    
    f_last_task >> last_task;
    f_last_task.close();
            
    char c_dir_name[10];
    sprintf(c_dir_name,"task%.5i",last_task);
    CURTASKDIR = TASKDIRS + c_dir_name;
    
    CURPROGFILE = CURTASKDIR + "/" + PROGFILE; 
    
    cout << endl << "last task dir:" << CURTASKDIR << endl;
   
    if(mkdir(CURTASKDIR.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0){
        cout << "error cannot create dir:" << CURTASKDIR << endl;
        return  EXIT_FAILURE;
    }
    
    if(rename (PROGFILE.c_str(), CURPROGFILE.c_str()) !=0 ){
        cout << "error cannot move prog file from:" << PROGFILE << endl;
        cout << "error cannot move prog file to:" << CURPROGFILE << endl;
        return  EXIT_FAILURE;
    }
    
    ofstream f_last_task_new(LASTTASK,ios::trunc);
    
    if(!f_last_task_new.is_open()){
        cout << "error opennig file for writing:" << LASTTASK << endl;
        return EXIT_FAILURE;    
    }
    
    f_last_task_new << ++last_task;
    f_last_task_new.close();
        
    return EXIT_SUCCESS;
}