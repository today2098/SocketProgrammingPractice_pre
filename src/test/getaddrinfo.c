#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    char hostname[] = "localhost";
    // char hostname[] = "DESKTOP-RHINHNB";
    struct addrinfo hints, *res0, *res;
    struct in_addr addr;
    char buf[16];
    int err;

    if(argc > 2) {
        fprintf(stderr,
                "Test getaddrinfo()\n\n"
                "Usage:\n\t%s [hostname]\n\n"
                "Example:\n\t%s localhost\n\t%s google.com\n",
                argv[0], argv[0], argv[0]);
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    if((err = getaddrinfo((argc == 2 ? argv[1] : hostname), NULL, &hints, &res0)) != 0) {
        fprintf(stderr, "error %d: %s\n", err, gai_strerror(err));
        return 1;
    }

    for(res = res0; res; res = res->ai_next) {
        addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;
        inet_ntop(AF_INET, &addr, buf, sizeof(buf));
        printf("ip address : %s\n", buf);
    }

    freeaddrinfo(res0);

    return 0;
}
