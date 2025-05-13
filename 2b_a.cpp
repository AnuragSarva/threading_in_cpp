// 2. Lambda Function
// a.

# include <iostream>
# include <thread>
using namespace std;

int main(){
    // lambdata function

    auto fun = [](int x){
        while(x-- > 0){
            cout << x << endl;
        }
    };

    tread t(fun, 10);
    t.join();
    return 0;
}
