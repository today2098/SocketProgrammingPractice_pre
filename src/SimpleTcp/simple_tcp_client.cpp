#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>

#include "../library/utility.hpp"

int main() {
    struct sockaddr_in server;
    int sock;
    char buf[32];
    int n;
    int res;

    /* ソケットの作成 */
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) DieWithSystemMessage("socket()");

    /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);

    /* 127.0.0.1はlocalhost */
    res = inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    if(res == -1) DieWithSystemMessage("inet_pton()");

    /* サーバに接続 */
    res = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if(res == -1) DieWithSystemMessage("connect()");

    /* サーバからデータを受信 */
    memset(buf, 0, sizeof(buf));
    n = read(sock, buf, sizeof(buf));
    if(n == -1) DieWithSystemMessage("read()");

    printf("Message: %s\nSize: %d Byte\n", buf, n);

    /* socketの終了 */
    res = close(sock);
    if(res == -1) DieWithSystemMessage("close()");

    return 0;
}
