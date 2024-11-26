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

int error_exp(char *str, char **res, char **sep)
{
    printf("export: \'%s\': not a valid identifier\n",str);
    free_double(res);
    free_double(sep);
    return (0);
}
int valid_export(char *str, char **res, char **sep)
{
    int i;
    int check;

    check = 1;
    i = 0;
    if(str[i])
    {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
            i++;
        else
            check = error_exp(str, res, sep);
    }
    while(str[i])
    {   
        if(!check)
            return (0);
        if(!(str[i] >= 'a' && str[i] <= 'z') || !(str[i] >= 'A' && str[i] <= 'Z') || str[i] != '_')
            check = error_exp(str, res, sep);
        else if(!(str[i] >= '0' && str[i] <= '9'))
            check = error_exp(str, res, sep);
        i++;
    }
    return (check);
}
char **append_exp(char *sep,char *holder)
{
    char **res;

    res = (char **)malloc(sizeof(char *) * 3);
    if(!res)
        return (NULL);
    res[0] = ft_strdup(sep);
    res[1] = holder;
    res[2] = NULL;
    return (res);
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
    holder = holder_env(str,len,check);
    res = append_exp(sep[0],holder);
    if(!valid_export(sep[0],res,sep))
        return (NULL);
    free_double(sep);
    return(res);
}

