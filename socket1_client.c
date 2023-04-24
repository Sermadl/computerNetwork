#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 128

void main() {
    while(1){
        int cs;
        int len = 0;
        char quit_msg[] = "quit";
        char send_buf[MAX];
        int recv_buf[MAX];
        struct sockaddr_in csa;
        
        memset(&csa, 0, sizeof(csa));
        csa.sin_family = AF_INET;
        csa.sin_addr.s_addr = inet_addr("127.0.0.1");
        csa.sin_port = htons(11234);

        cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(cs == -1){
            perror("socket error: ");
            return;
        }
        
        if(connect(cs, (struct sockaddr *) &csa, sizeof(csa)) == -1){
            perror("connection error: ");
            return;
        }
        
        memset(send_buf, '\0', MAX);
        memset(recv_buf, '\0', MAX);

        printf("------------------------------------------\n");
        printf("Enter any string(enter 'quit' to quit): ");
        scanf("%s", send_buf);
        if(!strcmp(send_buf, quit_msg))
            break;
            
        send(cs, (char *)send_buf, MAX, 0);
        recv(cs, (int *)recv_buf, MAX, 0);
        
        printf("[CLIENT] ASCII code: ");
        while(recv_buf[len]){
            printf("%d ", recv_buf[len]);
            len++;
        }
        printf("\n");
        close(cs);
    }
}