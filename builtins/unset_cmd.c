#include "../minishell.h"
void remove_node(t_path **paths,int pos)
{
    t_env *tmp;
    t_env *prev;
    int i;

    tmp = (*paths)->env_struct;
    i = 0;
    while(tmp)
    {
        if(i == pos)
            break;
        i++;
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp == NULL)
        return ;
    if(prev != NULL)
        prev->next = tmp->next;
    else 
        (*paths)->env_struct = tmp->next;
    free(tmp);
}
void unset_cmd(char **str, t_path **paths)
{   
    t_env *tmp;
    int i;
    int pos;
    
    i = 1;
    tmp = (*paths)->env_struct;
    if(str[1] == NULL)
    {
        printf("unset: not enough arguments\n");
        return ;
    }
    while(str[i])
    {   
        tmp = (*paths)->env_struct;
        pos = 0;
        while(tmp)
        {
            if(!ft_strncmp(str[i],tmp->env,ft_strlen(str[i])))
                break ;
            pos++;
            tmp = tmp->next;
        }
        remove_node(paths,pos);
        i++;
    }
}
