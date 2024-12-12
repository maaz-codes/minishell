#include "../minishell.h"

t_path	*ft_lstlast_path(t_path *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_env	*lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_path(t_path **lst, t_path *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast_path(*lst)->next = new;
	else
		*lst = new;
}

void add_NEWPWD(t_path **paths, t_path *new)
{   
    t_env *tmp_env;
    t_exp *tmp_exp;
    char *path_name;

    path_name = ft_strdup("PWD=");
    tmp_env = (*paths)->env_struct;
    tmp_exp = (*paths)->exp_struct;
    while(tmp_env)
    {   
        if(!ft_strncmp(tmp_env->env,"PWD=",4))
        {   
            free(tmp_env->env);
            tmp_env->env = ft_strjoin(path_name,new->pwd);
        }
        tmp_env = tmp_env->next;
    }
    while(tmp_exp)
    {   
        if(!ft_strncmp(tmp_exp->exp,"PWD=",4))
        {   
            free(tmp_exp->exp);
            tmp_exp->exp = ft_strjoin(path_name,new->pwd);
            free(path_name);
            return ;
        }
        tmp_exp = tmp_exp->next;
    }

    return ;
}

void add_OLDPWD(t_path **paths, t_path *new)
{
    t_env *tmp;
    char *path_name;
    t_env *old_pwd;

    path_name = ft_strdup("OLDPWD=");
    tmp = (*paths)->env_struct;
    old_pwd = malloc(sizeof(t_env));
    while(tmp)
    {
        if(!ft_strncmp(tmp->env,"OLDPWD=",7))
        {   
            free(tmp->env);
            tmp->env = ft_strjoin(path_name,new->pwd_old);
            free(path_name);
            free(old_pwd);
            return ;
        }
        tmp = tmp->next;
    }
    old_pwd->env = ft_strjoin(path_name,new->pwd_old);
    old_pwd->next = NULL;
    lstlast_env((*paths)->env_struct)->next = old_pwd;
    free(path_name);
    return ;
}
