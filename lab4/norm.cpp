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

void norm(int num, unsigned long long int seed1, unsigned long long int seed2){
    long double u1, u2, s, x, y, tmp1,tmp2;
    long double max = 18446744073415510704;
    for (int i=0; i<num; i=i+2){
        while (true) {
            tmp1 = generator_shift(seed1);
            tmp2 = generator_shift(seed2);
            u1 = tmp1/max*2-1;
            u2 = tmp2/max*2-1;
            s = u1*u1 + u2*u2;
            // cout << u1 << endl << u2 << endl << s<<endl<<endl;
            if (s>0 & s<=1) break;
            seed1 = tmp1;
            seed2 = tmp2;
        }
        x = u1 * sqrt(-2*log(s)/s);
        y = u2 * sqrt(-2*log(s)/s);
        cout << x << endl;
        cout << y << endl;
        seed1 = tmp1;
        seed2 = tmp2;
    }
    
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    int th_num = atoi(argv[2]);

    unsigned long long int *seeds = get_seeds(th_num*2);
    // cout<<"seeds:"<<endl;
    // for(int i=0;i<th_num;++i){
    //     cout<<seeds[i]<<endl;
    // }
    vector<thread> threads;
    // cout<<"Starting generators:"<<endl;
    for(int i = 0; i < th_num; i=i+2) {
        threads.push_back(thread(norm,num, seeds[i], seeds[i+1]));
        }
    for (auto& th: threads){
        th.join();
    }
    // norm(num, seeds[0],seeds[1]);
}