#include <stdio.h>
#include <unistd.h>
#include "hello.h"

int main(int argc, char **argv) {
    static const char *str = "Hello World";
    int i;

    if (argc > 1)
        str = argv[1];
    print(str, 3);
    return 0;
}

// 10MB of data
#define SZ (2048)
int data[SZ][SZ];
void timeattack() {
    int i, j;
    for (i = 0; i < SZ; i++)
        for (j = 0; j < SZ; j++)
            data[j][i]++;
}

void print(const char *str, long num) {
    int i;
    for (i = 0; i < num; i++) {
        printf("%s\n", str);
        timeattack();
    }
}

