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
    int res;

    /* ソケットの作成 */
    sock0 = socket(PF_INET, SOCK_STREAM, 0);
    if(sock0 == -1) DieWithSystemMessage("socket()");

    /* ソケットの設定 */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    res = bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
    if(res == -1) DieWithSystemMessage("bind()");

    /* TCPクライアントからの接続要求を待てる状態にする */
    res = listen(sock0, 5);
    if(res == -1) DieWithSystemMessage("listen()");

    /* TCPクライアントからの接続要求を受け付ける */
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);
    if(sock == -1) DieWithSystemMessage("accept()");

    /* 5文字送信 */
    res = write(sock, "HELLO", 5);
    if(res == -1) DieWithSystemMessage("write()");

    /* TCPセッションの終了 */
    res = close(sock);
    if(res == -1) DieWithSystemMessage("close()");

    /* listen するsocketの終了 */
    res = close(sock0);
    if(res == -1) DieWithSystemMessage("close()");

    return 0;
}
