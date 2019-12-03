#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
using namespace std;

void generator_shift(int n, unsigned long long int seed){
    // unsigned long long int * res = new unsigned long long int[n];
    unsigned long long int a = 2685821657736338717;
    unsigned long long int x = seed;
    // res[0] = x;
    for(int i=1;i<n+1;i++){
        x = x ^ x >> 12;
        x = x ^ x << 25;
        x = x ^ x >> 27;
        cout <<seed <<" : "<< x * a << endl;
    }
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

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    int th_num = atoi(argv[2]);

    unsigned long long int *seeds = get_seeds(th_num);
    cout<<"seeds:"<<endl;
    for(int i=0;i<th_num;++i){
        cout<<seeds[i]<<endl;
    }
    vector<thread> threads;
    cout<<"Starting generators:"<<endl;
    for(int i = 0; i < th_num; ++i) {
        threads.push_back(thread(generator_shift, num, seeds[i]));
        }
    for (auto& th: threads){
        th.join();
    }
}