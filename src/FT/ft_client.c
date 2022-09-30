#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../library/utility.h"  // for DieWithSystemMessage().

int main(int argc, char *argv[]) {
    int fd;
    int sock;
    struct sockaddr_in server;
    char buf[65536];
    int n;
    int ret;

    if(argc != 2) {
        fprintf(stderr,
                "File transport client\n\n"
                "Usage:\n\t%s <filename>\n\n"
                "Example:\n\t%s sample/water.jpg\n",
                argv[0], argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if(fd == -1) DieWithSystemMessage("open()");

    /* ソケットの作成 */
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) DieWithSystemMessage("socket()");

    /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);

    /* 127.0.0.1はlocalhost */
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);

    /* サーバに接続 */
    ret = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if(ret == -1) DieWithSystemMessage("connect()");

    while((n = read(fd, buf, sizeof(buf))) > 0) {
        ret = write(sock, buf, n);
        if(ret < 1) {
            perror("write()");
            break;
        }
    }

    /* socketの終了 */
    close(sock);

    return 0;
}
