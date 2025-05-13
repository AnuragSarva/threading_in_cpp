
# include <iostream>
# include <thread>
# include <mutex>
using namespace std;

// only one thread will access it at once.
atomic<int> counter;
int times = 1000000;

void run(){
    for(int i=0; i<times; i++){
        ++counter;
    }
}

int main(){
    thread t1(run), t2(run);
    t1.join();
    t2.join();
    cout<< counter << endl;
    return 0;
}
