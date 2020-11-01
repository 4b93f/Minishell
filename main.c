#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"


int main(void)
{
    int size;
    int ret;

    size = 40000;
    char buff[size];
    while (1)
    {
        if(strcmp(buff, "exit") == 0)
            exit(1);
        else
        {
            ret = read(1, buff, size);
            buff[ret - 1] = '\0';
            system(buff);
        }
    }
}



int ft_scan(char *tap)
{
    if (tap = "pwd")
    {
        ft_pwd();
    }
}

int ft_pwd()
{
    char *buf;
    int size = 40000;
    printf("%s\n", getcwd(buf, size));
}

int ft_cd(char *tap)
{
    if (*tap == "cd" || *tap == "cd ~" || *tap == "cd /")
        chdir("~");
}