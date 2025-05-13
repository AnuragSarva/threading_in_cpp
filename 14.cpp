
# include <iostream>
# include <thread>
# include <mutex>
# include <chrono>
using namespace std;
mutex m1, m2;

void task_a(){
    while(1){
        // lock(m1, m2); // here we have to ecplicetly unlock the lock, other wise we can use some wraper.
        m1.lock();
        m2.lock();
        cout << "task a" << endl;
        m1.unlock();
        m2.unlock();
    }
}

void task_b(){
    while(1){
        // lock(m2, m1); // now a days system is very fast, due to this it will not stuck into deadlock, for that we have to use that 
        m2.lock();
        m1.lock();
        cout << "task b" << endl;
        m2.unlock();
        m1.unlock();
    }
}

int main(){
    thread t1(task_a);
    thread t2(task_b);
    t1.join();
    t2.join();
    return 0;
}
