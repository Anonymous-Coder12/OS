#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;
void signalHandler(int signum) {
    cout << "Signal received: " << signum << endl;
    exit(signum);
}

int main() {
    // Register signal handler
    signal(SIGINT, signalHandler);

    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        cout << "Child process executing..." << endl;
        sleep(2); // Simulate some work
        exit(0);  // Terminate child process
    } else {
        // Parent process
        cout << "Parent process waiting for child..." << endl;
        int status;
        waitpid(pid, &status, 0); // Wait for child to terminate
        if (WIFEXITED(status)) {
            cout << "Child process exited with status: " << WEXITSTATUS(status) << endl;
        } else {
            cerr << "Child process terminated abnormally" << endl;
        }
    }

    return 0;
}
