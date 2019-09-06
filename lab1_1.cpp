#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
using namespace std;

void thread_print(int i)
{
    sleep(i);
    cout << "Some message from " <<i+1<<" thread. "<< "Waited "<<i<<" seconds."<< endl;
}

int main(int argc, char *argv[])
{
    int max = atoi(argv[1]);
    cout <<"Number of threads: "<< max <<endl;
    vector<thread> threads;
    for(int i = 0; i < max; ++i) {
        threads.push_back(thread(thread_print, i));
        }
    for (auto& th: threads){
        th.join();
    }
    return 0;
}