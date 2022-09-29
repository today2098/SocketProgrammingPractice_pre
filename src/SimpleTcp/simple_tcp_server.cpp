#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>

#include "../library/utility.hpp"

int main() {
    int sock0;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    socklen_t len;
    int sock;
    int err;

    /* ソケットの作成 */
    sock0 = socket(PF_INET, SOCK_STREAM, 0);
    if(sock0 == -1) DieWithSystemMessage("socket()");

    /* ソケットの設定 */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    err = bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
    if(err == -1) DieWithSystemMessage("bind()");

    /* TCPクライアントからの接続要求を待てる状態にする */
    err = listen(sock0, 5);
    if(err == -1) DieWithSystemMessage("listen()");

    /* TCPクライアントからの接続要求を受け付ける */
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);
    if(sock == -1) DieWithSystemMessage("accept()");

    /* 5文字送信 */
    err = write(sock, "HELLO", 5);
    if(err == -1) DieWithSystemMessage("write()");

    /* TCPセッションの終了 */
    close(sock);

    /* listen するsocketの終了 */
    close(sock0);

    return 0;
}
