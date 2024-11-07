#include "../minishell.h"

t_path	*ft_lstlast(t_path *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void ft_append(t_path **paths, char *cwd)
{
    t_path *new_node;
    t_path *last_node;

    new_node = malloc(sizeof(t_path));
    last_node = ft_lstlast(*paths);
    if(!new_node)
        return ;
    if(last_node == NULL)
        *paths = new_node;
    else
        last_node->next = new_node;
    *paths = new_node;
    new_node->pwd = cwd;
    new_node->old_pwd = cwd;
    new_node->next = NULL; 
}

void cd_cmd(char **str, t_path **paths)
{  
    char cwd[1024];
    char *res;
    int len;

    (*paths) = malloc(sizeof(t_path));
    (*paths)->pwd = NULL;
    (*paths)->old_pwd = NULL;
    (*paths)->next = NULL;

    if(getcwd(cwd,sizeof(cwd)) == NULL)
        printf("error");

    if(str[1] != NULL && (!ft_strncmp(str[1],"..",3)))
        res = ft_strdup("testing");
    else
    {
        len = ft_strlen(cwd);
        res = ft_calloc(len + 1,sizeof(char *));
        ft_strlcpy(res,cwd,len + 1);
    }

    ft_append(paths,res);

    while((*paths))
    {
        printf("pwd: %s\n",(*paths)->pwd);
        printf("pwd_old: %s\n",(*paths)->old_pwd);
        (*paths) = (*paths)->next;
    }
    free(res);
    // ft_lstclear(paths);
}

