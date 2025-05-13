
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex m1, m2;

void processData(int id){
    // acquire locks on m1 and m2 simultaneously
    std::scoped_lock lock(m1, m2);
    // critical section
    cout << "Thread " << id << ": Processing data with m1 and m2." << endl;
    // perform processing here
}

int main(){
    const int numThreads = 50;
    thread threads[numThreads];
    // create threads
    for(int i = 0; i < numThreads; i++){
        threads[i] = thread(processData, i);
    }
    // join threads
    for(int i = 0; i < numThreads; ++i){
        threads[i].join();
    }
    return 0;
}
// scoped_lock is available only in C++17 and later.
