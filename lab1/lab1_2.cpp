#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <chrono>
using namespace std;

void thread_print_to_file(int i)
{
    ofstream myfile;
    myfile.open("time.txt");
    for (int t=0;t<i;t++){
        sleep(1);
        auto current_time = chrono::system_clock::now();
        time_t str_time = chrono::system_clock::to_time_t(current_time);
        myfile << ctime(&str_time);
    }
    myfile.close();
}

int main(int argc, char *argv[])
{
    int max = atoi(argv[1]);
    cout <<"Daemon will work "<< max<<" seconds"<<endl;
    cout <<"Main will wait "<< 5<<" seconds"<<endl;
    thread mythread = thread(thread_print_to_file, max);
    mythread.detach();
    cout<<"Daemon was detached"<<endl;
    sleep(5);
    cout<<"Main was closed"<<endl;
    return 0;
}