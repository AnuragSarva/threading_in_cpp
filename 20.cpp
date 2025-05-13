
# include <iostream>
# include <thread>
# include <mutex>
using namespace std;

// the purpose of staic variable is, it is initialises only once in a scope, but if you write int s=0; then it will created multiple times.
static int s = 0;       // Not thread safe. It will not print 200000, some of the time write is not properly synchronized.

mutex m;
void fun(){
    int count = 100000;
    // m.lock(); // solution
    while(count--){
        // m.lock(); // not a good practice to use lock() here
        ++s;
        // m.unlock();
    }
    // m.unlock();
    cout << s << endl;
}

int main(){
    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();
    return 0;
}
