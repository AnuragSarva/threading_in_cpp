
# include <iostream>
# include <thread>
# include <mutex>
# include <chrono>
using namespace std;

long long bankBalance = 0;

// void addMoney(long long val){
//     bankBalance += val; // there is a problem of synchronization, actual value will be 3000, but here it will be either 1000 or 2000. so, the solution is mutex.
// }

mutex m;
void addMoney(long long val){
    m.lock();
    bankBalance += val;
    m.unlock();
}

int main(){
    thread T1(addMoney, 1000);
    thread T2(addMoney, 2000);

    T1.join();
    T2.join();
    cout << "Final Bank-Balance : " << bankBalance << endl;
    return 0;
}
