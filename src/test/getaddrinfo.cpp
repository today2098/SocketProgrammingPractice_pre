#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstdio>
#include <cstring>

int main() {
    char *hostname = "localhost";
    // char *hostname = "DESKTOP-RHINHNB";
    struct addrinfo hints, *res;
    struct in_addr addr;
    char buf[16];
    int err;

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    if((err = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "error %d\n", err);
        return 1;
    }

    addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;
    inet_ntop(AF_INET, &addr, buf, sizeof(buf));
    printf("ip address : %s\n", buf);

    freeaddrinfo(res);

    return 0;
}
