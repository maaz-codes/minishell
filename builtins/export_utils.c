#include "../minishell.h"

char *holder_env(char *str, int len, int check)
{
    char *holder;

    holder = malloc(sizeof(char *) * len + 1);
    if(!check)
        ft_strlcpy(holder,str,ft_strlen(str));
    else
        ft_strlcpy(holder,str + (len + 1),ft_strlen(str) - (len - 1));
    return (holder);
}

int error_exp(char *str, char **res, char **sep)
{
    printf("export: \'%s\': not a valid identifier\n",str);
    if(res)
        free_array(res);
    if(sep)
        free_array(sep);
    return (0);
}
int valid_export(char *str, char **res, char **sep, int check_for_plus)
{
    int i;
    int check;
    int len; 

    len = 1;
    check = 1;
    i = 0;
    if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
        i++;
    else
        check = error_exp(str, res, sep);
    if(!check)
        return (0);
    while(str[i])
    {   
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
            len++;
        else if((str[i] >= '0' && str[i] <= '9'))
            len++;
        i++;
    }
    if(len != ft_strlen(str) && !check_for_plus)
    {
        printf("enter here\n");
        check = error_exp(str, res, sep);
    }
    return (check);
}

char **append_exp(char *sep,char *holder)
{
    char **res;
    char *sep_str;
    char *holder_str;

    sep_str = ft_strdup(sep);
    holder_str = ft_strdup(holder);
    res = (char **)malloc(sizeof(char *) * 3);
    if(!res)
        return (NULL);
    res[0] = sep_str;
    res[1] = holder_str;
    res[2] = NULL;
    return (res);
}
char **separator(char *str, int check_for_plus)
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
    {   
        error_exp(str,NULL,sep);
        return (NULL);
    }
    if(ft_strlen(str) == len)
        check = 0;
    holder = holder_env(str,len,check);
    res = append_exp(sep[0],holder);
    if(!valid_export(sep[0],res,sep,check_for_plus))
        return (NULL);
    free_array(sep);
    free(holder);
    return(res);
}

