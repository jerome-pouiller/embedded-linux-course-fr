#include <stdio.h>
#include <stdlib.h>

void *a, *b;

void test1() {
    a = malloc(1);
    b = a;
 //   a = NULL;
 //   b = NULL;
 }

int test2() {
    int a[1];
    if (a[0])
        return 1;
    return 0;
}

int main(int argc, char **argv) {
    printf("Test1\n");
    test1();
    printf("Test2\n");
    test2();
    printf("Fin\n");
    return 0;
}
