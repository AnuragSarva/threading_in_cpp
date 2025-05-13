// 5. Static Member Function

# include <iostream>
# include <thread>
using namespace std;

class Base{
    public:
    static void run(int x){
        while(x-- > 0){
            cout << x << endl;
        }
    }
};
int main(){
    thread t(&Base::run, 10); // with the static member no need of object to use it.
    t.join();
    return 0;
}
