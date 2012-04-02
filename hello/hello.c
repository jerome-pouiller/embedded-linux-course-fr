#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "hello.h"

int main(int argc, char **argv) {
    static const char *str = "Hello World";
    long num = -1;
    char *end = NULL;

    if (argc > 1) {
        num = strtol(argv[1], &end, 10);
        if (!*argv[1] || *end || num < 0) {
            fprintf(stderr, "Invalid iteration number\n");
            num = -1;
        }
    }
    print(str, num);
    return 0;
}

void print(const char *str, long num) {
    int i;
    for (i = 0; i != num; i++) {
        printf("%s\n", str);
        sleep(1);
    }
}

