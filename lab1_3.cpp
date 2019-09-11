#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::chrono_literals;


int text = 0;
mutex text_mutex;

void writer() {
    cout << "W: mutex locking...\n";
    text_mutex.lock();
    cout << "W: mutex locked...\n";
    text = 10;
    this_thread::sleep_for(5s);
    text_mutex.unlock();
    cout << "W: mutex unlocked...\n";
}

void reader() {
    cout << "R: mutex locking...\n";
    text_mutex.lock();
    cout << "R: mutex locked...\n";
    cout << text << endl;
    text_mutex.unlock();
    cout << "R: mutex unocked...\n";
}
int main(void) {
    thread th02(writer);
    this_thread::sleep_for(1s);
    thread th01(reader);
    th01.join();
    th02.join();
    cout << text << endl;
    return 0;
}