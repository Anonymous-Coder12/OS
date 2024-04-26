#include <iostream>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

using namespace std;
int main(){
    int fd[2],n;
    char buffer[100];
    pid_t p;
    pipe(fd);
    p=fork();
    if(p>0){
        cout<<"passing value to child"<<endl;
        write(fd[1],"some message\n",13);
    }
    else{
        cout<<"child received data"<<endl;
        read(fd[0],buffer,100);
        cout<<buffer<<endl;
    }
}