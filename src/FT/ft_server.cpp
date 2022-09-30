#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>

#include "../library/utility.hpp"  // for DieWithSystemMessage().

int main(int argc, char *argv[]) {
    const char OUTPUT_DIR[] = "output/";

    char filepath[128];
    int fd;
    int sock0;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    socklen_t len;
    int sock;
    char buf[65536];
    int n;
    int ret;

    if(argc != 2) {
        fprintf(stderr,
                "File transport server\n\n"
                "Usage:\n\t%s <outputfilename>\n\n"
                "Example:\n\t%s data.jpg\n",
                argv[0], argv[0]);
        return 1;
    }

    snprintf(filepath, 128, "%s%s", OUTPUT_DIR, argv[1]);
    fd = open(filepath, O_WRONLY | O_CREAT, 0600);  // 0600 -> "-rw-------"
    if(fd == -1) DieWithSystemMessage("open()");

    /* ソケットの作成 */
    sock0 = socket(PF_INET, SOCK_STREAM, 0);
    if(sock0 == -1) DieWithSystemMessage("socket()");

    /* ソケットの設定 */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    ret = bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) DieWithSystemMessage("bind()");

    /* TCPクライアントからの接続要求を待てる状態にする */
    ret = listen(sock0, 5);
    if(ret == -1) DieWithSystemMessage("listen()");

    /* TCPクライアントからの接続要求を受け付ける */
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);
    if(sock == -1) DieWithSystemMessage("accept()");

    while((n = read(sock, buf, sizeof(buf))) > 0) {
        ret = write(fd, buf, n);
        if(ret < 1) {
            perror("write()");
            break;
        }
    }

    /* TCPセッションの終了 */
    close(sock);

    /* listen するsocketの終了 */
    close(sock0);

    return 0;
}
