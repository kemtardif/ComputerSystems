#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()

{
    char buf[100];
    char *bufp;
    int fd;
    struct stat stat;
    size_t size;
    // printf("Enter file name : ");
    // fgets(buf, sizeof(buf), stdin);


    if((fd = open("file.txt", O_RDWR)) == -1)
    {
        printf("Error opening file \n");
        exit(0);
    };

    fstat(fd, &stat);
    size = stat.st_size;

    bufp = mmap(NULL, stat.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
   // *bufp = 'J';

     printf("%s", bufp);

    munmap(bufp, stat.st_size);
    exit(0);

}