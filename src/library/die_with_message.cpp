#include <cerrno>
#include <cstdio>
#include <cstdlib>

#include "utility.hpp"

void DieWithSystemMessage(const char *msg) {
    perror(msg);
    fprintf(stderr, "errno: %d\n", errno);
    exit(1);
}
