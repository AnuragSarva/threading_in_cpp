
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

int main(){
    // create the thread and that will execute at its own pace.
    // with parallel to this the main() function is also running..
    // OS will take some time to create thread and execute.

    thread t(run, 10);
    cout << "main()" << endl;

    // here the main function will wait for the thread to execute completely.

    t.join();
    // t.join(); // this will forcely terminate the main() thread.


    // after so many lines of code, if we forget we already wrote t.join(), in this case this will helps
    // actualy joinable(), firstly checks whether it is already joined or not.
    if(t.joinable())
        t.join();

    cout<< "after main()" << endl;
    return 0;
}
