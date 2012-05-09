/*
 * Test with:
 *   echo 123456 | valgrind --leak-check=yes ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fun() {
  int        var;
  int        *stck = &var;
  int        *heap = malloc(2 * sizeof(int));
  static int *bss;

  printf("%d\n", var);            // var hasn't been initialized
  printf("%d\n", heap[0]);        // heap hasn't been initialized
  heap[2] = 42;                   // wrote past the end of the block
  printf("%d\n", heap[-1]);       // read from before start of the block
  printf("%d\n", stck[-15]);      // reading from a bad stack location (detected if outside current frame)
  read(0, heap, 10);              // buffer passed to syscall is too small
  //read(0, stck, 10);            // buffer passed to syscall is too small (not detected)
  free(heap);
  printf("%d\n", *heap);          // heap was already freed
  heap = malloc(sizeof(int));     // memory leaks (definitely lost)
  stck = heap;                    // .. even if another variable point on it
  bss = malloc(sizeof(int));      // memory leaks (still reachable)
  bss[0] = 1;
}

int main(int argc, char **argv) {
  fun();
  return 0;
}

