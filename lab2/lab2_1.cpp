#include <iostream>
#include <fstream>
#include <string>
using namespace std;


unsigned long long int * random1(int n, unsigned long long seed){
    unsigned long long int * res = new unsigned long long int[n];
    unsigned long long int m = 1844674407370955161;
    unsigned long long int a = 6364136223846793005;
    unsigned long long int c = 1442695040888963407;
    res[0] = seed;
    for(int i=1;i<n;i++){
        res[i] = (a*res[i-1]+c) % m;
    }

    return res;
}

unsigned long long int * random2(int n, unsigned long long seed){
    unsigned long long int * res = new unsigned long long int[n];
    unsigned long long int a = 2685821657736338717;
    unsigned long long int x = seed;
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

    ofstream res1, res2;

    ifstream devrand;
    devrand.open("/dev/random", ios::in | ios::binary);
    unsigned long long int seed;
    const auto bytes_num = sizeof seed;
    devrand.read((char *) &seed, bytes_num);
    devrand.close();
    
    unsigned long long int *r1 = random1(n,seed);
    unsigned long long int *r2 = random2(n,seed);
    cout<<"-----------------FIRST RANDOM--------------------"<<endl;

    res1.open("random1_" + to_string(n) + ".txt");
    for(int i=0; i<n;i++){
        res1 << r1[i] << endl;
        cout<<r1[i]<<endl;
    }
    res1.close();

    cout<<"-----------------SECOND RANDOM--------------------"<<endl;

    res2.open("random2_" + to_string(n) + ".txt");
    for(int i=0; i<n;i++){
        res2 << r2[i] << endl;;
        cout<<r2[i]<<endl;
    }
    res2.close();

    return 0;
}
