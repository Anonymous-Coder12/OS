#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex coutMutex;
// Function to be executed by the thread
void threadFunction(int threadID) {
    lock_guard<mutex> lock(coutMutex);
    cout << "Thread " << threadID << " is running" << endl;
}

int main() {
    // Create three thread objects
    thread t1(threadFunction, 1);
    thread t2(threadFunction, 2);
    thread t3(threadFunction, 3);

    // Check if each thread is joinable and wait for them to finish
    if (t1.joinable()) {
        cout << "Thread 1 is joinable" << endl;
        t1.join();
    }

    if (t2.joinable()) {
        cout << "Thread 2 is joinable" << endl;
        t2.join();
    }

    if (t3.joinable()) {
        cout << "Thread 3 is joinable" << endl;
        t3.join();
    }

    cout << "All threads have finished" << endl;

    return 0;
}
