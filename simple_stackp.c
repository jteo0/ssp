#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// WIN FUNCTION - The exploitation target
void win(void) {
    printf(">>> CODE REDEMPTION ACTIVATED <<<\n");
    system("/bin/sh");  // Prize for successful exploitation
}

void print(const char *msg) {
    write(1, msg, strlen(msg));
}

// Modified to force stack pivoting
void readInput(size_t size) {
    char input[8];  // TINY buffer - forces stack pivot
    memset(input, 0, sizeof(input));
    print("Oh, really? How come?\n");
    read(0, input, size);  // Severe overflow now
    printf("Fascinating. \"%.8s\", I'll take it into consideration.\n", input);
}

void meat() {
    char inputSize[9];
    unsigned int size;

    print("How is e-hacking? Having fun? Rate it on a scale from 0-9.\n");
    read(0, inputSize, 9);
    inputSize[8] = '\0'; 
    size = atoi(inputSize);

    if ((int)size < 1) {
        print("Yeah, that sounds about right.\n");
    } else if ((int)size < 0x82) {  // Increased max size for pivot space
        readInput(size);
    } else {
        print("Enthusiastic, are we?\n");
    }
}

int main() {
    setvbuf(stdin,  NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    meat();
    return 0;
}