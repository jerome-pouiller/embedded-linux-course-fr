#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

unsigned int sleep(unsigned int s) {
    printf("Delay action to try to reveal race-conditions\n");
    unsigned int (*orig_sleep)(unsigned int s) = dlsym(RTLD_NEXT, "sleep");
    return orig_sleep(5 * s);
}
