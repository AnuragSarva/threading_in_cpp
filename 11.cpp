
# include <iostream>
# include <thread>
# include <mutex>
# include <condition_variable>
# include <chrono>
using namespace std;

condition_variable cv;
mutex m;
long balance = 0;

void addMoney(int money){
    lock_guard<mutex> lg(m); // locking mutex
    balance += money;
    cout << "Amount Added to Current Balance: " << balance << endl;
    cv.notify_one();
}

void withdrowMoney(int money){
    unique_lock<mutex> ul(m); // locking mutex
    cv.wait(ul, [] {return (balance != 0) ? true : false; }); // if condition is false, then it will wait by releasing the mutex and wait for notify_one(), if it get this then agian check condition
    if(balance >= money){
        balance -= money;
        cout << "Amount Deducted: " << money << endl;
    }else{
        cout << "Amount can't be Deducted, Current Balance is less than " << money << endl;
    }
    cout << "Current balance is: " << balance <<  endl;
}

int main(){
    thread t1(withdrowMoney, 600);
    // this_thread::sleep_for(chrono::seconds(5));
    thread t2(addMoney, 500);
    t1.join();
    t2.join();
    return 0;
}
