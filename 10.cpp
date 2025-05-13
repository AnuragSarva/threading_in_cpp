
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m;
int buffer = 0;

// EXAMPLE - 1

// void task(const char* threadNumber, int loopFor){
//    unique_lock<mutex> lock(m); // automatically calls lock on mutex m.
//    for(int i=0; i<loopFor; ++i){
//        buffer++;
//        cout << threadNumber << buffer << endl;
//    }
//    // here not use unlock(), because it is happeming in the destructor of this unique lock, so this will automatically be called when the scope is go off.
//    // but with the lock(), we have to explictly unlock() the lock. 
//}

// EXAMPLE - 2

void task(const char* threadNumber, int loopFor){
    unique_lock<mutex> lock(m, defer_lock); // does not call lock on mutex m, because used defer_lock
    lock.lock(); // but then we will have to explicitly tell to lock when ever we want to lock mutex m.
    // the benifite of this is, it no imideatly lock, we need explicitly lock it, before it we can write any number line of code.
    for(int i=0; i<loopFor; ++i){
        buffer++;
        cout << threadNumber << buffer << endl;
    }
    // lock.unlock() is not needed as it will be unlocked in destructor of unique_lock().
}

int main(){
    thread t1(task, "t1 ", 5);
    thread t2(task, "t2 ", 5);
    t1.join();
    t2.join();
    return 0;
}
