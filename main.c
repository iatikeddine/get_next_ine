#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *ptr;
    int i = 0;
    while(i < 3)
    {
        ptr = get_next_line(fd);
        printf("%s", ptr);
        free(ptr);
        i++;
    }
}