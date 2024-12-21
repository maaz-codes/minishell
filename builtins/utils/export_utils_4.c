#include "../../minishell.h"

char *if_with_equals_env(t_env *tmp, char *holder, char *tmp_char, char *sep)
{
    char *old_exp;
    char *joined_str;
    char *res_char;
    int i;
    
    i = 0;
    while(holder[i] != '=' && holder[i])
        i++;
    if(holder[i] == '=')
    {   
        i++;
        old_exp = ft_strdup(holder + i);
        free(tmp->env);
        joined_str = ft_strjoin(tmp_char,old_exp);
        res_char = ft_strjoin(joined_str,sep);
        free(old_exp);
        free(joined_str);
        return res_char;
    }
}

void holder_is_equals_env(t_env *tmp, char *sep, char *tmp_char)
{
    free(tmp->env);
    if(sep[0] != '\0')
        tmp->env = ft_strjoin(tmp_char,sep);
    else if(sep[0] == '\0')
        tmp->env = ft_strdup(tmp_char);
}

void holder_is_equals_exp(t_exp *tmp, char *sep, char *tmp_char)
{
    free(tmp->exp);
    if(sep[0] != '\0')
        tmp->exp = ft_strjoin(tmp_char,sep);
    else if(sep[0] == '\0')
        tmp->exp = ft_strdup(tmp_char);
}

char *if_with_equals_exp(t_exp *tmp, char *holder, char *tmp_char, char *sep)
{
    char *old_exp;
    char *joined_str;
    char *res_char;
    int i;
    
    i = 0;
    while(holder[i] != '=' && holder[i])
        i++;
    if(holder[i] == '=')
    {   
        i++;
        old_exp = ft_strdup(holder + i);
        free(tmp->exp);
        joined_str = ft_strjoin(tmp_char,old_exp);
        res_char = ft_strjoin(joined_str,sep);
        free(old_exp);
        free(joined_str);
        return res_char;
    }
    return (NULL);
}
