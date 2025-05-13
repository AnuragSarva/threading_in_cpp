// using async here
#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
#include<future>
using namespace std;
using namespace std::chrono;
typedef long int ull;

ull findOdd(ull start, ull end){
    ull OddSum = 0;
    cout << "Thread id : " << this_thread::get_id() << endl;
    for(ull i=start; i<=end; ++i){
        if(i & 1) OddSum += i;
    }
    return OddSum;
}

int main(){
    ull start = 0, end = 1900000000;
    cout << "Thread id : " << this_thread::get_id() << endl;            // differented id will be printed, one for main thread and another for child thread.
    cout << "Threa created if policy is std::launch::async!!" << endl;
    future<ull> OddSum = async(launch::async, findOdd, start, end);     // here both function will call by different thread.
    cout << "Waiting for result!!" << endl;
    cout << "OddSum : " << OddSum.get() << endl;                        // here one thread is waiting for the another threads value.
    cout << "Completed!!" << endl;
    return 0;
}
