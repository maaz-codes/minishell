#include "../minishell.h"

void valid_num(char *s, char **str, t_ancient *ancient_one)
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
            error_msg(str, ancient_one);
    }
    if(len >= 20)
        error_msg(str, ancient_one);
}
