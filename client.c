#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#define Port 6789
#define serve_ip "127.0.0.1"
#define client_ip "192.168.0.10"

int main(int argc, const char * argv[]) {
    
    int sockfd;
    struct sockaddr_in serve_addr;
    struct sockaddr_in client_addr;
    char buf[256];
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0) {
        perror("socket created error");
        exit(1);
    }/*else{
        printf("socket created successfully\n");
        printf("socket id is :%d\n",sockfd);
    }*/
//设置客户端端套接口结构
    bzero(&client_addr, sizeof(struct sockaddr_in));
    client_addr.sin_addr.s_addr=inet_addr(client_ip);
    client_addr.sin_port=9876;
    client_addr.sin_family=AF_INET;
    
    if (bind(sockfd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr))<0) {
        perror("bind client error");
        exit(1);
    }/*else{
        printf("bind client successfully\n");
        printf("client_ip is %s\n",inet_ntoa(client_addr.sin_addr));
    }*/
    
    
    
//设置服务器端套接口结构
    bzero(&serve_addr, sizeof(struct sockaddr_in));
    serve_addr.sin_addr.s_addr=inet_addr(serve_ip);
    serve_addr.sin_port=htons(Port);
    serve_addr.sin_family=AF_INET;
    
    if (connect(sockfd, (struct sockaddr*)(&serve_addr), sizeof(struct sockaddr))<0) {
        perror("connect error");
        exit(1);
    }else{
        printf("connect successfully the server port is:%d\n",Port);
    }
//发送数据
    send(sockfd,"iloveyou", sizeof("iloveyou"), 0);
    printf("i already send a state to serve\n");

    
   
    
    
    
    return 0;
}
