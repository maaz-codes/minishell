#include "../minishell.h"

// t_path	*ft_lstlast(t_path *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// void ft_append(t_path **paths, char *cwd)
// {
//     t_path *new_node;
//     t_path *last_node;

//     new_node = malloc(sizeof(t_path));
//     last_node = ft_lstlast(*paths);
//     if(!new_node)
//         return ;
//     if(last_node == NULL)
//         *paths = new_node;
//     else
//         last_node->next = new_node;
//     *paths = new_node;
//     new_node->pwd = cwd;
//     new_node->old_pwd = cwd;
//     new_node->next = NULL; 
// }


char *new_path(char *cwd, int id)
{
    int len;
    int i;
    char *new_path;

    len = ft_strlen(cwd);
    if(id == 1)
    {   
        len -= 1;
        while(cwd[len] != '/' && cwd[len])
            len--;
    }
    new_path = ft_calloc(len + 1,sizeof(char *));
    if(!new_path)
        return NULL;
    ft_strlcpy(new_path,cwd,len + 1);
    printf("new path: %s\n",new_path);
    return new_path;
}

char *get_home(char **env)
{
    int i;
    char **holder;
    char *res;

    i = 0;
    while(env[i])
    {
        if(!ft_strncmp(env[i],"HOME=",5))
        {
            holder = ft_split(env[i],'=');
            res = new_path(holder[1], 0);
            free_double(holder);
            return(res);
        }
        i++;
    }
    return (NULL);
}

void cd_cmd(char **str, t_path **paths, char **env)
{  
    char cwd[1024];
    char *res;
    int len;

    if(getcwd(cwd,sizeof(cwd)) == NULL)
        printf("error");
    printf("my cwd: %s\n",cwd);
    if(!ft_strncmp(str[0],"cd",3) && str[1] == NULL)
        res = get_home(env);
    else if(str[1] != NULL && (!ft_strncmp(str[1],"..",3)))
        res = new_path(cwd,1);
    else if(str[1] != NULL)
        res = new_path(str[1],0);

    if(chdir(res) == -1)
        printf("error dir\n");
    free(res);
}

