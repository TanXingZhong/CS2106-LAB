#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
    if (ac != 2) {
        printf("\nPlease provide a sentence in quotes.\n");
        printf("Usage: %s \"<sentence>\"\n\n", av[0]);
        exit(-1);
    }

    char *sentence = strdup(av[1]);
    char *word = strtok(sentence, " ");

    int count = 0;
    while (word != NULL) {
        printf("%s\n", word);
        sleep(1);
        word = strtok(NULL, " ");
        count++;
    }

    printf("\nNumber of words: %d\n", count);

    // Try removing this exit to explore its effect
    exit(count);
}
