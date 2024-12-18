#include "../minishell.h"

void ap_env(t_env **env, char *res)
{   
    t_env *temp;
    char *env_new;

    env_new = res;
    temp = malloc(sizeof(t_env));
    if(!temp)
        return ;
    temp->env = res;
    temp->next = NULL;
    if (*env)
		lstlast_env(*env)->next = temp;
	else
		*env = temp;
}

void export_t_env(t_path **paths, char *tmp_char, char *sep, char *str)
{
    t_env *tmp;
    int i;

    i = 0;
    tmp = (*paths)->env_struct;
    while(str[i] != '=' && str[i])
        i++;
    if(i == ft_strlen(str))
        return ;
    while(tmp)
    {
        if(!ft_strncmp(tmp_char,tmp->env, ft_strlen(tmp_char) - 1))
        {   
            free(tmp->env);
            tmp->env = ft_strjoin(tmp_char,sep);
            return ;
        }
        tmp = tmp->next;
    }
    ap_env(&(*paths)->env_struct,ft_strjoin(tmp_char,sep));
}

void export_t_exp(t_path **paths, char *tmp_char, char *sep, char *str)
{
    t_exp *tmp;
    int i;
    int check;
    char *joined_str;
    char *only_str;

    i = 0;
    check = 1;
    tmp = (*paths)->exp_struct;
    while(str[i] != '=' && str[i])
        i++;
    if(i == ft_strlen(str))
        check = 0;
    joined_str = ft_strjoin(tmp_char,sep);
    only_str = ft_strdup(str);
    while(tmp)
    {
        if(!ft_strncmp(tmp_char,tmp->exp, ft_strlen(tmp_char) - 1))
        {   
            free(tmp->exp);
            if(!check)
                tmp->exp = only_str;
            else
            {
                tmp->exp = joined_str;
                free(only_str);
            }
            return ;
        }
        tmp = tmp->next;
    }
    if(!check)
        ap_exp(&(*paths)->exp_struct, only_str);
    else
        ap_exp(&(*paths)->exp_struct,joined_str);
    (free(joined_str),free(only_str));
}

t_exp *int_exp(char **env)
{
    t_exp *node_new;
    int i;

    i = 1;
    if(!env || !env[0])
        return (NULL);
    node_new = (t_exp *)malloc(sizeof(t_exp));
    if(node_new == NULL)
        return (NULL);
    node_new->exp = ft_strdup(env[0]);
    if (!node_new->exp)
        return (NULL);
    node_new->next = NULL;
    while(env[i])
        ap_exp(&node_new,env[i++]);
    return(node_new);
}

int plus_equals_check(char *str)
{   
    int i;

    i = 0;
    if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
        i++;
    else
        return(0);
    while(str[i])
    {
        if(str[i] == '+')
        {
            if(str[i + 1] == '=')
                return (1);
            else
                return (0);
        }
        i++;
    }
    return (0);
}

void export_t_exp_plus(t_path **paths, char *tmp_char, char *sep, char *str)
{
    t_exp *tmp;
    char *holder;
    char *old_exp;    
    char *joined_str;
    int i;

    tmp = (*paths)->exp_struct;
    while(tmp)
    {
        if(!ft_strncmp(tmp_char,tmp->exp, ft_strlen(tmp_char) - 1))
        {   
            i = 0;
            holder = tmp->exp;
            while(holder[i] != '=' && holder[i])
                i++;
            if(holder[i + 1] == '\0' && sep[0] != '\0')
            {   
                free(tmp->exp);
                tmp->exp = ft_strjoin(tmp_char,sep);
                return ;
            }
            else if(holder[i + 1] != '\0')
            {   
                if(holder[i] != '\0')
                {
                    i++;
                    old_exp = ft_strdup(holder + i);
                    free(tmp->exp);
                    joined_str = ft_strjoin(tmp_char,old_exp);
                    tmp->exp = ft_strjoin(joined_str,sep);
                    free(old_exp);
                }
                free(joined_str);
                return ;
            }
            else if(sep[0] == '\0')
            {
                free(tmp->exp);
                tmp->exp = ft_strdup(tmp_char);
                return ;
            }
        }
        tmp = tmp->next;
    }
    ap_exp(&(*paths)->exp_struct,ft_strjoin(tmp_char,sep));
}

void export_t_env_plus(t_path **paths, char *tmp_char, char *sep, char *str)
{
    t_env *tmp;
    char *holder;
    char *old_exp;
    char *joined_str;
    int i;

    tmp = (*paths)->env_struct;
    while(tmp)
    {
        if(!ft_strncmp(tmp_char,tmp->env, ft_strlen(tmp_char) - 1))
        {   
            i = 0;
            holder = tmp->env;
            while(holder[i] != '=' && holder[i])
                i++;
            if(holder[i + 1] == '\0' && sep[0] != '\0')
            {   
                free(tmp->env);
                tmp->env = ft_strjoin(tmp_char,sep);
                return ;
            }
            else if(holder[i + 1] != '\0')
            {   
                if(holder[i] != '\0')
                {
                    i++;
                    old_exp = ft_strdup(holder + i);
                    free(tmp->env);
                    joined_str = ft_strjoin(tmp_char,old_exp);
                    tmp->env = ft_strjoin(joined_str,sep);
                    free(old_exp);
                }
                free(joined_str);
                return ;
            }
            else if(sep[0] == '\0')
            {
                free(tmp->env);
                tmp->env = ft_strdup(tmp_char);
                return ;
            }
        }
        tmp = tmp->next;
    }
    ap_env(&(*paths)->env_struct,ft_strjoin(tmp_char,sep));
}

void plus_equals_exp(t_path **paths, char **sep, char *str, int *i)
{
    char *tmp_char;
    char *new_str;

    new_str = ft_calloc(ft_strlen(sep[0]), sizeof(char *));
    ft_strlcpy(new_str, sep[0], ft_strlen(sep[0]));
    printf("name: %s\n",new_str);
    if(!sep)
        *i += 1;
    else
    {
        tmp_char = ft_strjoin(new_str,"=");
        export_t_exp_plus(paths,tmp_char,sep[1],str);
        export_t_env_plus(paths,tmp_char,sep[1],str);
        (free_array(sep),free(tmp_char),free(new_str));
        *i += 1;
    }
}

void normal_exp(t_path **paths, char **sep, char *str, int *i)
{   
    char *tmp_char;

    if(!sep)
        *i += 1;
    else
    {
        tmp_char = ft_strjoin(sep[0],"=");
        export_t_exp(paths,tmp_char,sep[1],str);
        export_t_env(paths,tmp_char,sep[1],str);
        (free_array(sep),free(tmp_char));
        *i += 1;
    }
}
void export_cmd(char **str, t_path **paths)
{   
    t_env *tmp;
    char **sep;
    int   i;
    int   check_for_plus;

    i = 1;
    int f = 0;
    while(str[f])
    {
        printf("%s\n",str[f]);
        f++;
    }
    if(!ft_strncmp("export",str[0],7) && str[1] == NULL)
        exp_print(paths);
    else if(!ft_strncmp("export",str[0],7) && str[1] != NULL)
    {   
        while(str[i])
        {   
            check_for_plus = plus_equals_check(str[i]);
            printf("0 normal 1 with plus: %d\n",check_for_plus);
            sep = separator(str[i], check_for_plus);
            if(!check_for_plus)
                normal_exp(paths,sep,str[i],&i);
            else
                plus_equals_exp(paths,sep,str[i],&i);
        }
    }
    return ;
}
