#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

//
//int main()
//{
//   char *buf;
//    int size = 800;
//    printf("%s\n", getcwd(buf, size));
//}

int main()
{
    char *buf;
    int size = 40000;
    printf("%s\n", getcwd(buf, size));
}