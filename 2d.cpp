// 4. Non-Static member function

# include <iostream>
# include <thread>
using namespace std;

class Base{
    public:
        void run(int x){
            while(x-- > 0){
                cout << x << endl;
            }
        }
};
int main(){
    // object defination
    Base b;
    // non-static function needs object to call it.
    thread t(&Base::run, &b, 10); // address of the function is &Base::run, and object is &b
    t.join();
    return 0;
}
