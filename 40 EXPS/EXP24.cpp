#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char buf[50];
    int fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);   
    write(fd, "Hello UNIX\n", 11);                                  
    lseek(fd, 0, SEEK_SET);                                       
    int n = read(fd, buf, sizeof(buf) - 1);                        
    buf[n] = '\0';
    printf("Read: %s", buf);
    close(fd);                                                     
    unlink("test.txt");                                            
    return 0;
}