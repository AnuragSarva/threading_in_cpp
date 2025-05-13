// Using 1. Function Pointer here -

// Find the addition of all odd number and even number from 1 to 1900000000

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
// #include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

typedef unsigned long long ull;
ull OddSum = 0, EvenSum = 0;

void even_sum(int start, int end){
    for(ull i = start; i<= end; ++i){
        if((i & 1) == 0) 
            EvenSum += i;
    }
}

void odd_sum(int start, int end){
    for(ull i = start; i<= end; ++i){
        if((i & 1) != 0) 
            OddSum += i;
    }
}

// default thread in any function (here funciton is not using an thread but it is considered as thread)
int main(){
    ull start = 0, end = 1900000000;
    
    auto start_time = high_resolution_clock::now();

    // thread needs callable objects.
    // here i am function pointer.
    // thread defination is here - 

    thread t1(even_sum, start, end); // even_sum(start, end);
    thread t2(odd_sum, start, end);  // odd_sum(start, end);

    // after using thread we have to join it into main thread, if we not did then may be main thread will over first and then the other so the output is not printed.

    t1.join();
    t2.join();

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    cout << "Odd Sum : " << OddSum << endl;
    cout << "Even Sum : " << EvenSum << endl;
    cout << "Duration in second : " << duration.count()/1000000 << endl;
    return 0;
}
