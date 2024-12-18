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

void swap_node(t_exp *cur, t_exp *hold)
{
    char *tmp = cur->exp;
    cur->exp = hold->exp;
    hold->exp = tmp;
}

void sorted_exp(t_exp **head)
{
    int swap;
    t_exp *current;
    t_exp *holder;

    if(!(*head))
        return ;
    holder = current;
    swap = 1;
    while(swap)
    {
        swap = 0;
        current = (*head);
        while(current->next)
        {   
            if(ft_strncmp(current->exp,current->next->exp,ft_strlen(current->exp)) > 0)
            {
                swap_node(current,current->next);
                swap = 1;
            }
            current = current->next;
        }
        holder = current;
    }
}
void exp_print(t_path **paths)
{
    t_exp *tmp;
    t_exp *tmp_head;
    char *check;

    tmp = (*paths)->exp_struct;
    sorted_exp(&tmp);
    while(tmp)
    {   
        check = ft_strchr(tmp->exp,'=');
        if(check)
            printf("declare -x %.*s=\"%s\"\n",(int)(check - tmp->exp),tmp->exp,check + 1);
        else
            printf("declare -x %s\n",tmp->exp);
        tmp = tmp->next;
    }
}




