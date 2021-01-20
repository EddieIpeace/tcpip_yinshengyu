#include "inc.h"

int main(int argc, char* argv[]) {
    if (2 != argc) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == serv_sock) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (-1 == bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
        error_handling("bind() error");
    }

    if (-1 == listen(serv_sock, 5)) {
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if (-1 == clnt_sock) {
        error_handling("accept() error");
    }

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);

    return 0;
}