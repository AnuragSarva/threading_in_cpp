
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
int myAmount = 0;
timed_mutex m;

void increment(int i){
    if(m.try_lock_for(chrono::seconds(2))){
        ++myAmount;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "thread " << i << " entered" << endl;
        m.unlock();
    }else{
        cout << "thread " << i << " couldn't enter" << endl;
    }
}

int main(){
    thread t1(increment, 1);
    thread t2(increment, 2);

    t1.join();
    t2.join();

    cout << myAmount << endl;
    return 0;
}
