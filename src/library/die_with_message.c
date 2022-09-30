#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "utility.h"

void DieWithSystemMessage(const char *msg) {
    perror(msg);
    fprintf(stderr, "errno: %d\n", errno);
    exit(1);
}
