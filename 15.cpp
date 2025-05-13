
# include <iostream>
# include <thread>
# include <mutex>
# include <future>
# include <algorithm>
using namespace std;
using namespace std::chrono;
typedef long int ull;

void findOdd(promise<ull>&& OddSumPromise, ull start, ull end){                 // 2. here it will promising object.
    ull OddSum = 0;
    for(ull i=start; i<=end; ++i){
        if(i & 1) OddSum += i;
    }
    OddSumPromise.set_value(OddSum);                                            // 3. after calculating the value, it will send the value to the feature object, it is waiting to get() it.
}

int main(){
    ull start = 0, end = 1900000000;

    promise<ull> OddSum;                                                        // creating a promise object.
    future<ull> OddFuture = OddSum.get_future();                                // creating a futire object using promise object.

    cout << "Thread Created!!" << endl;
    thread t1(findOdd, std::move(OddSum), start, end);                              // 1. sending the promise object to the function.
    
    cout << "Waiting for Result!!" << endl;
    cout << "OddSum : " << OddFuture.get() << endl;                             // 4. here future object will receive the value.
    cout << "completed!!" << endl;
    t1.join(); 
    return 0;
}
