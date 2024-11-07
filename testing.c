#include <stdio.h>
#include <unistd.h>
int main()
{
    char *s = "hello world";
    while(*s)
    {
        write(1,s,1);
        s++;
    }
}