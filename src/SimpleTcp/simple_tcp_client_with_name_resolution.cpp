#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>

#include "../library/utility.hpp"  // for DieWithSystemMessage().

int main(int argc, char *argv[]) {
    char *hostname, *portnum;
    struct addrinfo hints, *res0, *res;
    int sock;
    char buf[32];
    int n;
    int err;

    if(argc != 3) {
        fprintf(stderr,
                "Simple TCP client with name resolution\n\n"
                "Usage:\n\t%s <hostname> <port>\n\n"
                "Example:\n\t%s localhost 12345\n",
                argv[0], argv[0]);
        return 1;
    }

    hostname = argv[1];
    portnum = argv[2];

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = PF_UNSPEC;  // プロトコルは指定しない．IPv4 or IPv6.
    err = getaddrinfo(hostname, portnum, &hints, &res0);
    if(err != 0) {
        fprintf(stderr, "error %d: %s\n", err, gai_strerror(err));
        DieWithSystemMessage("getaddrinfo()");
    }

    /* addrinfoリストの要素を先頭から接続できるまで順に試行する */
    for(res = res0; res; res = res->ai_next) {
        // ソケットの作成．
        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(sock == -1) continue;

        /* ソケットが生成できたらサーバへ接続を試みる */
        err = connect(sock, res->ai_addr, res->ai_addrlen);
        if(err == -1) {  // 失敗したらリストの次の項目を試す．
            close(sock);
            sock = -1;
            continue;
        }

        break;  // ここではすでに接続に成功しているので，forループを脱出．
    }

    freeaddrinfo(res0);

    /* リストのすべての項目が失敗していないかチェック */
    if(sock == -1) {
        fprintf(stderr, "Cannot connect %s\n", hostname);
        return 1;
    }

    /* サーバからデータを受信 */
    memset(buf, 0, sizeof(buf));
    n = read(sock, buf, sizeof(buf));
    if(n == -1) DieWithSystemMessage("read()");

    printf("Message: %s\nSize: %d Byte\n", buf, n);

    /* socketの終了 */
    close(sock);

    return 0;
}
