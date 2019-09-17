#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
using namespace std;


long long int * random1(int n, int seed){
    long long int * res = new long long int[n];
    auto m = 18446744073709551615;
    auto a = 6364136223846793005;
    auto c = 1442695040888963407;
    res[0] = seed;
    for(int i=1;i<n;i++){
        res[i] = (a*res[i-1]+c) % m;
    }

    return res;
}

long long int * random2(int n, int seed){
    long long int * res = new long long int[n];
    auto a = 2685821657736338717;
    auto x = seed;
    res[0] = x;
    for(int i=1;i<n;i++){
        x = x ^ x >> 12;
        x = x ^ x << 25;
        x = x ^ x >> 27;
        res[i] = x * a;
    }
    return res;
}


int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int seed = atoi(argv[2]);
    long long int *r1 = random1(n,seed);
    long long int *r2 = random2(n,seed);
    cout<<"-----------------FIRST RANDOM--------------------"<<endl;
    for(int i=0; i<n;i++){
        cout<<r1[i]<<endl;
    }
    cout<<"-----------------SECOND RANDOM--------------------"<<endl;
    for(int i=0; i<n;i++){
        cout<<r2[i]<<endl;
    }

    return 0;
}