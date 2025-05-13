
# include <iostream>
# include <thread>
# include <mutex>
# include <chrono>
using namespace std;

mutex m1, m2;

void thread1(){
    m1.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m2.lock();
    cout << "Critical Section of thread T1" << endl;
    m1.unlock();
    m2.unlock();
}

void thread2(){
    m2.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m1.lock();
    cout << "Critical Section of thread T2" << endl;
    m2.unlock();
    m1.unlock();
}

int main(){
    thread T1(thread1);
    thread T2(thread2);

    T1.join();
    T2.join();
    return 0;
}
