#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <semaphore.h>

sem_t chopstick[5];
std::mutex mtx;

void eat(int ph) {
    std::cout << "Philosopher " << ph << " begins to eat" << std::endl;
}

void philosopher(int ph) {
    mtx.lock();
    std::cout << "Philosopher " << ph << " wants to eat" << std::endl;
    std::cout << "Philosopher " << ph << " tries to pick left chopstick" << std::endl;
    mtx.unlock();

    sem_wait(&chopstick[ph]);

    mtx.lock();
    std::cout << "Philosopher " << ph << " picks the left chopstick" << std::endl;
    std::cout << "Philosopher " << ph << " tries to pick the right chopstick" << std::endl;
    mtx.unlock();

    sem_wait(&chopstick[(ph + 1) % 5]);

    mtx.lock();
    std::cout << "Philosopher " << ph << " picks the right chopstick" << std::endl;
    mtx.unlock();

    eat(ph);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    mtx.lock();
    std::cout << "Philosopher " << ph << " has finished eating" << std::endl;
    mtx.unlock();

    sem_post(&chopstick[(ph + 1) % 5]);

    mtx.lock();
    std::cout << "Philosopher " << ph << " leaves the right chopstick" << std::endl;
    mtx.unlock();

    sem_post(&chopstick[ph]);

    mtx.lock();
    std::cout << "Philosopher " << ph << " leaves the left chopstick" << std::endl;
    mtx.unlock();
}

int main() {
    for (int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    std::vector<std::thread> philosophers;
    for (int i = 0; i < 5; i++) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& ph : philosophers) {
        ph.join();
    }

    for (int i = 0; i < 5; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}
