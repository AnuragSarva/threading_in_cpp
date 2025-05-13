
# include <iostream>
# include <thread>
# include <chrono>
# include <semaphore>
using namespace std;

binary_semaphore signal_to_producer{1}, signal_to_consumer{0};
# define buff_size 5
int buff[buff_size];

void producer(){
    while(1){
        signal_to_producer.acquire();
        cout << "Producer = " ;
        for(int i=0; i<buff_size; i++){
            buff[i] = i*i;
            cout << buff[i] << " " << flush;
            this_thread::sleep_for(milliseconds(200));
        }
        cout << endl;
        signal_to_consumer.release();
    }
}

void consumer(){
    while(1){
        signal_to_consumer.acquire();
        cout << "Consumer = " ;
        for(int i=buff_size-1; i>=0; --i){
            cout << buff[i] << " " << flush;
            buff[i] = 0;
            this_thread::sleep_for(milliseconds(200));
        }
        cout << endl;
        signal_to_producer.release();
    }
}

int main(){
    thread t1(consumer);
    thread t2(producer);
    t1.join();
    t2.join();
    return 0;
}
