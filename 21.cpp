
# include <chrono>
# include <iostream>
# include <semaphore>
# include <thread>
using namespace std;

// global binary semaphore isinstance
// object counts are set to zero
// objects are in non-signaled state
binary_semaphore smphSignalMainToThread{0}, smphSignalThreadToMain{0}; // 0 means they are in blocked state

void ThreadProc()
{
    // wait for the signal from the main proc
    // by attempting to decrement the semaphore
    smphSignalMainToThread.acquire();

    // this call blocks until the semaphore's count
    // is increased from the main proc
    cout << "[thread] Got the signal\n" ; // response message

    using namespace std::literals;
    this_thread::sleep_for(3s);

    cout << "[thread] Send the signal" << endl; // message

    // siganl the main proc back
    smphSignalThreadToMain.release();
}

int main(){
    // create some worker thread
    thread thrWorker(ThreadProc);
    cout << "[main] Send the signal" << endl;       // message

    // signal the worker thread to start working
    // by increasing the semaphore's count
    smphSignalMainToThread.release();

    // wait until the worker thread is done doing the work
    // by attempting to decrement the semaphore's count
    smphSignalThreadToMain.acquire();

    cout << "[main] Got the signal" << endl; // response message
    thrWorker.join();

    return 0;
}
