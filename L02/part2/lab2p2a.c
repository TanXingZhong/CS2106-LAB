#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int slow(char *name, int time, char *sentence) {
    char *word = strtok(sentence, " ");
    int count = 0;
    while(word != NULL) {
        printf("%s: %s\n", name, word);
        sleep(time); // Simulate a delay for each word
        word = strtok(NULL, " ");
        count++;
    }
    printf("\n%s: Number of words: %d\n", name, count);
    return count;
}

int main() {
    int id;
    char sentence1[] = "This is a test sentence";
    char sentence2[] = "I have increased the number of words in this sentence";

    if((id = fork()) != 0) {
        int stat;
        int my_id = getpid();
        int parent_id = getppid();
        printf("\nI am the parent.\n");
        printf("My ID is %d\n", my_id);
        printf("My parent's ID is %d\n", parent_id);
        printf("My child's ID is %d\n\n", id);
        slow("Parent", 1, sentence1);
        printf("\nWaiting for child to exit.\n");
        wait(&stat);
        printf("CHILD HAS EXITED WITH STATUS %d\n", WEXITSTATUS(stat));
    } else {
        id = getpid();
        int parent_id = getppid();
        printf("\nI am the child.\n");
        printf("My ID is %d\n", id);
        printf("My parent's ID is %d\n\n", parent_id);
        int word_count = slow("Child", 2, sentence2);
        exit(word_count);
    }
}
