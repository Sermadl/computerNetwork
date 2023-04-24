#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

void main() {
    int ss, sa;
    struct sockaddr_in ssa;
    
    memset(&ssa, 0, sizeof(ssa));
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = htonl(INADDR_ANY);
    ssa.sin_port = htons(11234);

    ss = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(ss, (struct sockaddr *) &ssa, sizeof(ssa));

    while(1){
        listen(ss, 10);
        sa = accept(ss, 0, 0);
        send(sa, "test", 5, 0);
        close(sa);
    }
}