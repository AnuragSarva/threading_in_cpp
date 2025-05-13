
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex m;
int counter = 0;

void fun(){
    for(int i=0; i<100000; ++i){
        if(m.try_lock()){
            ++counter;
            m.unlock();
        }
    }
}

int main()
{
    thread t1(fun);
    thread t2(fun);

    t1.join();
    t2.join();

    cout << counter << endl;
    return 0;
}
