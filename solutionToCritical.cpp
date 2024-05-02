#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
std::mutex mtx;
void process(int id)
{
    // Attempt to enter the critical section
    mtx.lock();
    // Inside the critical section
    std::cout << "Process " << id << " entered the critical
        section " << std::endl;
        // Simulating some work in the critical section
        std::this_thread::sleep_for(std::chrono::seconds(1));
    // Exiting the critical section
    std::cout << "Process " << id << " exited the critical
                                     section " << std::endl;
                                     // Release the lock
                                     mtx.unlock();
}
int main()
{
    // Create two threads representing two processes
    std::thread t1(process, 1);
    std::thread t2(process, 2);
    // Join the threads with the main thread
    t1.join();
    t2.join();
    return 0;
}
