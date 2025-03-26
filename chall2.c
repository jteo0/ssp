#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void win(void) {
    printf("HOW'D YOU GET HERE???\n");
    execl("/bin/cat", "cat", "flag.txt", NULL);  
}

void print(const char *msg) {
    write(1, msg, strlen(msg));
}

void readInput(void) {
    char small_buffer[8];
    print("Oh, really? How come?\n");
    read(0, small_buffer, 16);
    printf("Fascinating. \"%s\", I'll take it into consideration.\n", small_buffer);
}

void meat() {
    char rating[32];
    print("How is e-hacking? Having fun? Rate it on a scale from 0-9.\n");
    read(0, rating, 32);
    printf("Rating at: %p\n", rating);
    print("Yeah, that sounds about right.\n");
    readInput();
}

int main() {
    setvbuf(stdin,  NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    meat();
    return 0;
}
