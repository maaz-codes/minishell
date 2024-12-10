#include "../minishell.h"

static t_env	*last_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void appending_env(t_env **env, char *res)
{
    t_env *new_node;
    new_node = malloc(sizeof(t_env));
    if(!new_node)
        return ;
    new_node->env = res;
    new_node->next = NULL;
    if(*env)
        last_env(*env)->next = new_node;
    else
        *env = new_node;   
}

t_env *int_env(char **env)
{
    t_env *node_new;
    char *str;
    int i;

    i = 1;
    str = ft_strdup(env[0]);
    if(!env)
        return (NULL);
    node_new = (t_env *)malloc(sizeof(t_env));
    if(!node_new)
        return (NULL);
    node_new->env = str;
    node_new->next = NULL;
    while(env[i])
        appending_env(&node_new,ft_strdup(env[i++]));
    return(node_new);
}

void env_cmd(char **str, t_path **paths)
{   
    t_env *new_node;
    new_node = (*paths)->env_struct;
    if(str[1] != NULL)
    {
        printf("env: too many arguments\n");
        return ;
    }
    while(new_node)
    {
        printf("%s\n",new_node->env);
        new_node = new_node->next;
    }
}
