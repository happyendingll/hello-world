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
#define PORT 6789
int main(int argc, const char * argv[]) {
    int sockfd,newsockfd;
    struct sockaddr_in serve_addr;
    struct sockaddr_in client_addr;
    unsigned int addr_len=sizeof(struct sockaddr_in);
    
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1) {
        perror("socket created error");
        exit(1);
    }
    /*else{
        printf("socket created successfully!\n");
        printf("socket id :%d\n",sockfd);
    }*/
    bzero(&serve_addr, addr_len);
    serve_addr.sin_family=AF_INET;
    serve_addr.sin_port=htons(PORT);
    serve_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*)&serve_addr, sizeof(struct sockaddr))==-1) {
        perror("bind socket error");
        exit(1);
    }
    /*else{
        printf("bind socket successfully!\n");
        printf("the port is:%d\n",PORT);
    }*/
    if (listen(sockfd, 5)==-1) {
        perror("listen error");
        exit(1);
    }else{
        printf("i am listening.....\n");
    }
    printf("%d\n",serve_addr.sin_addr.s_addr);
    
    if ((newsockfd=accept(sockfd, (struct sockaddr *)(&client_addr), &addr_len))==-1) {
        perror("accept erroe");
        exit(1);
    }/*else{
        printf("i have accept a new cliet\n");
        printf("the new socket id is:%d\n",newsockfd);
    }*/
    printf("the client ip is :%s\nthe port is: %d\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_port);
    
    char sbuf[256];
    //接收函数
    recv(newsockfd, sbuf, sizeof(sbuf), 0);
    printf("i have receive:%s\n",sbuf);
    printf("i will change the element to client\n");

    
    return 0;
}
