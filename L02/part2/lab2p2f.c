#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    printf("Be patient, the program will take around 7 seconds to run.\n");
    printf("At the end you can do \"cat results.out\" to see the result.\n");
    
    int p[2];
    if(pipe(p) < 0)
      perror("lab2p2f: ");

    if(fork() == 0) {
      char *args[] = {"./slow", "This is a test sentence", NULL};
      close(p[0]);
      dup2(p[1], STDOUT_FILENO);
      close(p[1]);
      execvp(args[0], args);
    } else {
      close(p[1]);
      dup2(p[0], STDIN_FILENO);
      close(p[0]);
      int fp_out = open("result.out", O_CREAT | O_WRONLY);
      dup2(fp_out, STDOUT_FILENO);
      close(fp_out);
      char *args[] = {"./talk", NULL};
      execvp(args[0], args);
      wait(NULL);
    }
}
