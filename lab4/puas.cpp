#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <math.h>
using namespace std;

long double generator_shift(unsigned long long int seed){
    // unsigned long long int * res = new unsigned long long int[n];
    unsigned long long int a = 2685821657736338717;
    unsigned long long int x = seed;
    long double max =18446744073415510704;
    long double res;
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

void puas(int num, unsigned long long int seed, int la){
    long double l, p, u, tmp1,tmp2;
    int k;
    long double max = 18446744073415510704;
    l = exp(-la);
    for (int i=0; i<num; ++i){
        k = 0;
        p = 1;
        do {
            k = k + 1;

            tmp1 = generator_shift(seed);
            u = tmp1/max;
            p = p * u;
            // cout << u << endl << k << endl << p << endl << endl;
            seed = tmp1;
        }
        while (p>l);
        cout << k-1 << endl;
        
    }
    
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    int th_num = atoi(argv[2]);
    int la = atoi(argv[3]);

    unsigned long long int *seeds = get_seeds(th_num);
    // cout<<"seeds:"<<endl;
    // for(int i=0;i<th_num;++i){
    //     cout<<seeds[i]<<endl;
    // }
    vector<thread> threads;
    // cout<<"Starting generators:"<<endl;
    for(int i = 0; i < th_num; ++i) {
        threads.push_back(thread(puas,num/th_num, seeds[i], la));
        }
    for (auto& th: threads){
        th.join();
    }
    // norm(num, seeds[0],seeds[1]);
}