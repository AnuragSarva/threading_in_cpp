// 3. Functor ( Function Object ) {functor is operator()}

# include <iostream>
# include <thread>
using namespace std;

class Base {
    public: 
        void operator ()(int x) {
            while(x-- > 0){
                cout << x << endl;
            }
        }
};
int main(){
    thread t((Base()), 10);
    t.join();
    return 0;
}
