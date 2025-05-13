
# include <iostream>
# include <thread>
# include <mutex>
using namespace std;
mutex m;

int counter;
int times = 1000000;

void fun(){
    // m.lock();
    for(int i=0; i<times; ++i){
        m.lock();
        ++counter;
        m.unlock();
    }
    // m.unlock();
}

int main(){
    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();
    cout << counter << endl;
    return 0;
}
// here output must be 2000000, but due to race condition it is always less then 2000000.
