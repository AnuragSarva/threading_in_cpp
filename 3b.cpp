
// DETACH()

// after detaching(), the OS knows that who is its parent if parent is get terminated the child is also get terminated.

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void run(int count){
    while(count-- > 0){
        cout << count << endl;
    }
    // this helps to sleep this thread for 3 seconds.
    this_thread::sleep_for(chrono::seconds(3));
}

// when we are working with the thread, the main() is considered as a parent thread, and the created thread is considered as a child thread.

int main(){
    // create the thread and that will execute at its own pace.
    // with parallel to this the main() function is also running..
    // OS will take some time to create thread and execute.

    thread t(run, 10);
    cout << "main()" << endl;

    // this thing will make seperate out the child thread for the main thread, now main thread will no longer wait for the child thread to finish
    t.detach();
    if(t.joinable())
        t.detach();
    cout<< "after main()" << endl;

    // parent thread is waiting for the child will finish but for the restricted amount of time.
    // this_thread::sleep_for(chrono::seconds(3));
    return 0;
}
