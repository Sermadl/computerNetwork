#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 128

void toASCII(char* str, int* ascii);

void main() {
    int ss, sa, len;
    char recv_buf[MAX];
    int send_buf[MAX] = {0, };
    struct sockaddr_in ssa;
    
    memset(&ssa, 0, sizeof(ssa));
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = htonl(INADDR_ANY);
    ssa.sin_port = htons(11234);

    ss = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(ss == -1){
        perror("socket error: ");
        return;
    }

    if(bind(ss, (struct sockaddr *) &ssa, sizeof(ssa)) == -1){
        perror("bind error: ");
        return;
    }

    while(1){
        memset(send_buf, '\0', MAX);
        memset(recv_buf, '\0', MAX);

        listen(ss, 10);
        sa = accept(ss, 0, 0);
        len = recv(sa, (char *)recv_buf, MAX, 0);
        if(len == -1){
            perror("recieve error: ");
            break;
        }
        printf("[SERVER] recieved: %s\n", recv_buf);

        toASCII(recv_buf, send_buf);

        send(sa, send_buf, MAX, 0);
    }

    close(sa);
}

void toASCII(char* str, int* ascii) {
    char* str_ps = str;
    int* asc_ps = ascii;

    while(*str_ps != '\0'){
        int tmp = *str_ps;
        *asc_ps = tmp;
        str_ps++;
        asc_ps++;
    }
}