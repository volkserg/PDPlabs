#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <math.h>
#include <queue>
using namespace std;
using namespace std::chrono_literals;

unsigned long long int generator_shift(unsigned long long int seed){
    // unsigned long long int * res = new unsigned long long int[n];
    unsigned long long int a = 2685821657736338717;
    unsigned long long int x = seed;
    unsigned long long int max =18446744073415510704;
    unsigned long long int res;
    // res[0] = x;
    x = x ^ x >> 12;
    x = x ^ x << 25;
    x = x ^ x >> 27;
    res = x * a;
    return res;
}

unsigned long long int * get_seeds(int n){
    ifstream devrand;
    devrand.open("/dev/random", ios::in | ios::binary);
    unsigned long long int * seed = new unsigned long long int[n];
    const auto bytes_num = sizeof seed;
    for (int i=0;i<n;++i){
        devrand.read((char *) &seed[i], bytes_num);
    }
    
    devrand.close();
    return seed;
}

void producer(queue<unsigned long long int> *Q){
    unsigned long long int seed = get_seeds(1)[0];
    unsigned long long int tmp = generator_shift(seed);
    for(int i=0;i<100;i++){
        Q->push(tmp);
        cout << "producer:: number was generated: "<< tmp << endl;
        tmp = generator_shift(tmp);
        this_thread::sleep_for(1s);
    }
}

void consumer (queue<unsigned long long int> *Q){
    for(int i=0;i<100;i++){
        while(Q->empty()){
            this_thread::sleep_for(3s);
        }
        cout <<"consumer:: ";
        while(!Q->empty()) {
            // Получаем значение первого элемента
            cout << Q->front() << " ";
            // Удаляем первый элемент
            Q->pop();
        }
        cout<<endl;
    }
}

int main(int argc, char *argv[])
{
    int th_num = 1;
    int la = 15;
    queue<unsigned long long int> Q;
    thread prod1(producer,&Q);
    thread cons1(consumer, &Q);
    this_thread::sleep_for(1s);
    thread cons2(consumer, &Q);
    prod1.join();
    cons1.join();
    cons2.join();
}