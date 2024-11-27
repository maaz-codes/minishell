#include "../minishell.h"

void valid_num(char *s, t_path **paths)
{   
    int i;
    int len;

    i = 0;
    len = 0;
    if(s[i] == '+' || s[i] == '-')
        i++;
    while(s[i])
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            i++;
            len++;
        }
        else
            error_msg(s,paths);
    }
    if(len >= 20)
        error_msg(s,paths);
}