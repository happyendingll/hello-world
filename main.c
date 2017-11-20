#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define FLAGS O_WRONLY|O_CREAT|O_TRUNC
#define MODE S_IRWXG|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH
int main(int argc, const char * argv[]) {
    const char* pathname;
    int fd;
    char pn[30];
    printf("place input the filepath\n");
    gets(pn);
    pathname=pn;
    if ((fd=open(pathname, FLAGS,MODE))==-1) {
        printf("open file error\n");
    }
    printf("open file successfully\n");
    printf("fd=%d\n",fd);
    
    return 0;
}
