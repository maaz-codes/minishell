#include "../minishell.h"

char *holder_env(char *str, int len, int check)
{
    char *holder;

    holder = malloc(sizeof(char *) * len + 1);
    if(!check)
        ft_strlcpy(holder,str,ft_strlen(holder));
    else
        ft_strlcpy(holder,str + (len + 1),ft_strlen(holder) - (len - 1));
    return (holder);
}

char **separator(char *str)
{
    int len;
    char **sep;
    char *holder;
    char **res;
    int check;

    sep = ft_split(str,'=');
    len = 0;
    check = 1;
    while(str[len] != '=' && str[len])
        len++;
    if(!len)
        return (NULL);
    if(ft_strlen(str) == len)
        check = 0;
    res = (char **)malloc(sizeof(char *) * 3);
    if(!res)
        return (NULL);
    holder = holder_env(str,len,check);
    res[0] = ft_strdup(sep[0]);
    res[1] = holder;
    res[2] = NULL;
    free_double(sep);
    return(res);
}
