#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <arpa/inet.h>

int sockfd;
void sig_handler(int signo){
    if (signo==SIGINT) {
        printf("serve close\n");
        close(sockfd);
        exit(1);
    }
}
void out_addr(struct sockaddr_in* clientaddr){
    int port=ntohs(clientaddr->sin_port);
    char ip[16];
    memset(ip, 0, sizeof(ip));
    inet_ntop(AF_INET, &clientaddr->sin_addr.s_addr, ip, sizeof(ip));
    printf("client:%s(%d) connected\n",ip,port);
}
void do_server(int fd){
    long t=time(0);
    char *s=ctime(&t);
    size_t size=strlen(s)*sizeof(char);
    if (write(fd, s, size)!=size) {
        perror("write error");
    }
}
int main(int argc, const char * argv[]) {
    
    if (argc<2) {
        printf("usage: %s #port\n",argv[0]);
    }
    if (signal(SIGINT, 0)==SIG_ERR) {
       // perror("signal sigint error");
    }
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(atoi(argv[1]));
    
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))<0) {
        perror("bind error");
        exit(1);
    }
    
    if (listen(sockfd, 10)<0) {
        perror("listen error");
        exit(1);
    }
    int fd;
    struct sockaddr_in clientaddr;
    socklen_t client_len=sizeof(clientaddr);
    while (1) {
        fd=accept(sockfd, (struct sockaddr*)&clientaddr, &client_len);
        if (fd<0) {
            perror("accept error！");
            continue;
        }
        out_addr(&clientaddr);
        do_server(fd);
        close(fd);
    }
    
    
    return 0;
}
