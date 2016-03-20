#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

namespace{
    volatile unsigned i = 0;
    mutex mutexTest;
    void Fct(){
        mutexTest.lock();
        cout << "bonjour " <<flush;
        cout << "tout le monde "
             << "le nombre : "
             << ++i
             << endl;
        mutexTest.unlock();
    }

    void initVector(vector <unsigned> & vectInt){
        mutexTest.lock();
        for(unsigned i=0; i < 10;++i){
            vectInt.push_back(i);
        }
        mutexTest.unlock();
    }

    void showVector(vector <unsigned> & vectInt){
        for(unsigned i = 0; i < vectInt.size();++i){
            cout << i << flush;
        }
        cout <<endl;
    }

}

int main(int argc, char *argv[])
{
    vector <unsigned> vectInt;
    cout << thread::hardware_concurrency() << endl;
    thread thread1(Fct);
    thread thread2(Fct);
    thread1.join();
    thread2.join();
    thread initVect(initVector, ref(vectInt));
    thread showVect(showVector,ref(vectInt));
    initVect.join();
    showVect.join();
    return 0;
}
