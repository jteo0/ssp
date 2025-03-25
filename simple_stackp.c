#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print(const char *msg) {
    write(1, msg, strlen(msg));
}

void readInput(size_t size) {
    char input[128];
    memset(input, 0, sizeof(input));
    print("Oh, really? How come?\n");
    read(0, input, size);  // Overflow if size > 128
    printf("Fascinating. \"%s\", I'll take it into consideration.\n", input);
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
    } else if ((int)size < 0x82) {
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