// 2. Lambda Function
// b. 

# include <iostream>
# include <thread>
using namespace std;

int main(){
    // we can directly inject lambda ar thread creation time.

    tread t([](int x){
        while(x-- > 0){
            cout << x << endl;
        }
    }, 10);
    t.join();
    return 0;
}
