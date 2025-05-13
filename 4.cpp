
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
int myAccount = 0;
// without this two or more thread or process will modify the data samultaniously, that make data inconsistency.
mutex m;

void addMoney(){
    m.lock();
    ++myAccount;
    m.unlock();
}

int main(){
    thread t1(addMoney);
    thread t2(addMoney);

    t1.join();
    t2.join();

    cout << myAccount << endl;
    return 0;
}
