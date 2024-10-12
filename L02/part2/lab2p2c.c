#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    if(fork() ==  0) {
        //execlp("cat", "cat", "file.txt", NULL);
        char *args[] = {"cat", "file.txt", NULL};
        execvp("cat", args);
    }
    else
        wait(NULL);
}

