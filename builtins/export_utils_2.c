#include "../minishell.h"

t_exp	*lstlast_exp(t_exp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void ap_exp(t_exp **exp, char *res)
{   
    t_exp *temp;

    temp = malloc(sizeof(t_exp));
    if(!temp)
        return ;
    temp->exp = ft_strdup(res);
    temp->next = NULL;
    if(*exp)
        lstlast_exp(*exp)->next = temp;
    else
        *exp = temp;   
}

t_exp *int_exp(char **env)
{
    t_exp *node_new;
    int i;

    i = 1;
    if(!env)
        return (NULL);
    node_new = (t_exp *)malloc(sizeof(t_exp));
    if(node_new == NULL)
        return (NULL);
    node_new->exp = ft_strdup(env[0]);
    node_new->next = NULL;
    while(env[i])
        ap_exp(&node_new,env[i++]);
    return(node_new);
}



