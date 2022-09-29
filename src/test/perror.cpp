#include <sys/socket.h>
#include <sys/types.h>

#include <cerrno>
#include <cstdio>

int main() {
    int sock;

    sock = socket(3000, 4000, 5000);
    if(sock < 0) {
        perror("socket");
        fprintf(stderr, "%d\n", errno);
        return 1;
    }

    return 0;
}
