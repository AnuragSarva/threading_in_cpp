
// using deferred here, benifit of uisng deferred is we no need to create thread but the task is runnign in parallel like a thread and using get() to take value in feature.
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
    ull start = 0, end = 190000000;
    cout << "Thread id : " << this_thread::get_id() << endl;                    // same will be printed, because running by the same thread.
    cout << "Threa created if policy is std::launch::async!!" << endl;
    std::future<ull> OddSum = std::async(std::launch::deferred, findOdd, start, end);   // here both function will call by one task.
    cout << "Waiting for result!!" << endl;
    cout << "OddSum : " << OddSum.get() << endl;                        // here one task is waiting for the output return by the function.
    cout << "Completed!!" << endl;
    return 0;
}
