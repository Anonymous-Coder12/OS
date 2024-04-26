#include <iostream>
#include <thread>
using namespace std;

int sharedVariable=0;

void func(){
    cout<<"Value printed:\t"<<sharedVariable<<endl;
    sharedVariable++;
}

int main(){
    thread threads[5];
    for(int i=0;i<5;i++){
        threads[i]=thread(func);
    }
    for(int i=0;i<5;i++){
        threads[i].join();
    }
}