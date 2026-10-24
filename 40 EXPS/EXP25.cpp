#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <dirent.h>

int main()
{
    int fd = open("test.txt", O_CREAT | O_RDWR, 0644);
    write(fd, "Hello World\n", 12);

    printf("lseek (end) : %ld\n", (long)lseek(fd, 0, SEEK_END));

    struct stat s;
    stat("test.txt", &s);
    printf("stat size   : %ld bytes, mode: %o\n",
           (long)s.st_size, s.st_mode & 0777);
    close(fd);

    DIR *d = opendir(".");
    struct dirent *e;
    printf("Directory contents:\n");
    while ((e = readdir(d)) != NULL)
        printf("  %s\n", e->d_name);
    closedir(d);
    return 0;
}