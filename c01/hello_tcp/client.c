#include "inc.h"

int main(int argc, char* argv[]) {
    if (3 != argc) {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;

    struct sockaddr_in serv_addr;

    char message[30];

    serv_sock == socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == serv_sock) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (-1 == connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
        error_handling("connect() error");
    }

    if (-1 == read(serv_sock, message, sizeof(message) - 1)) {
        error_handling("read() error");
    }
    printf("Message from server: %s\n", message);
    close(serv_sock);
    return 0;
}
