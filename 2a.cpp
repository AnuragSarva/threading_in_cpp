// 1. Function Pointer

# include <iostream>
# include <thread>
using namespace std;

void fun(int x){
    while(x-- < 0)
        cout << x << endl;
}
int main(){
    thread t(fun, 11);
    t.join();
    return 0;
}
