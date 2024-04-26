#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* file_path = "./example.txt";
    const char* new_content = "This is new content.";

    // Open file in read-write mode (O_RDWR) and create if not exists (O_CREAT)
    int fd = open(file_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // Read from file
    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        std::cerr << "Failed to read from file." << std::endl;
        close(fd);
        return 1;
    }

    // Print file content
    buffer[bytes_read] = '\0';
    std::cout << "File content: " << buffer << std::endl;

    // Append new content to file
    if (lseek(fd, 0, SEEK_END) == -1) {
        std::cerr << "Failed to seek to end of file." << std::endl;
        close(fd);
        return 1;
    }
    ssize_t bytes_written = write(fd, new_content, strlen(new_content));
    if (bytes_written == -1) {
        std::cerr << "Failed to write to file." << std::endl;
        close(fd);
        return 1;
    }

    // Close file
    if (close(fd) == -1) {
        std::cerr << "Failed to close file." << std::endl;
        return 1;
    }

    std::cout << "File appended successfully." << std::endl;
    return 0;
}
