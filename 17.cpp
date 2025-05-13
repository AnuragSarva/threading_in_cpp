
// using async here
#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
#include<future>
using namespace std;

deque<int> buffer;
const unsigned int maxBufferSize = 50;
mutex mu;
condition_variable cond;

void producer(int val){
    while(val){
        unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() < maxBufferSize;});         // it will check condition if it is failed, it wait here only by releasing the mutex.
        buffer.push_back(val);
        cout << "Producer: " << val << endl;
        --val;
        locker.unlock();
        cond.notify_one();
    }
}

void consumer(){
    while(1){
        unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() > 0;});
        int val = buffer.back();
        buffer.pop_back();
        cout << "Consumer: " << val << endl;
        --val;
        locker.unlock();
        cond.notify_one();
    }
}

// one major thing i noticed here is whenever producer is producing something and consumer is consuming then, when producer is producing something then the pointer again should start from 100 and reducing one by one when prodecer is producing something and pushing it into the buffer.

int main(){
    thread t1(producer, 100);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
