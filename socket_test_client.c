#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

void main() {
    int cs;
    char buf[5];
    struct sockaddr_in csa;
    
    memset(&csa, 0, sizeof(csa));
    csa.sin_family = AF_INET;
    csa.sin_addr.s_addr = inet_addr("127.0.0.1");
    csa.sin_port = htons(11234);

    cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(cs, (struct sockaddr *) &csa, sizeof(csa));

    recv(cs, buf, 5, 0);
    printf("Receive [%s]\n", buf);

    close(cs);
}