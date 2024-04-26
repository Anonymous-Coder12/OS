#include <iostream>
#include <thread>
#include <semaphore.h>
#include <fcntl.h>
#include <vector>
#include <chrono>
#include <unistd.h>
// Shared resource
#include <cstring>
const char* file_path = "./resource.txt";
// Semaphores
sem_t mutex, write_block;
int read_count = 0;

void reader(int id) {
    while (true) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_block);
        }
        sem_post(&mutex);

        // Read from the shared resource
    int fd = open(file_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    // Read from file
    char buffer[256];
    read(fd, buffer, sizeof(buffer));
    // Print file content
    std::cout << "File content: " << buffer << std::endl;

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&write_block);
        }
        sem_post(&mutex);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void writer(int id) {
    while (true) {
        sem_wait(&write_block);
        int fd = open(file_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        // Write to the shared resource
        if (lseek(fd, 0, SEEK_END) == -1) {
        std::cerr << "Failed to seek to end of file." << std::endl;
        close(fd);
        }
        const char* new_content="message";
        write(fd,new_content , strlen(new_content));
        

        sem_post(&write_block);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&write_block, 0, 1);

    std::vector<std::thread> readers;
    for (int i = 0; i < 5; ++i) {
        readers.emplace_back(reader, i);
    }

    std::vector<std::thread> writers;
    for (int i = 0; i < 2; ++i) {
        writers.emplace_back(writer, i);
    }

    for (auto& reader_thread : readers) {
        reader_thread.join();
    }

    for (auto& writer_thread : writers) {
        writer_thread.join();
    }

    sem_destroy(&mutex);
    sem_destroy(&write_block);

    return 0;
}
