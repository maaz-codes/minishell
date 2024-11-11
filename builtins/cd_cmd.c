#include "../minishell.h"

t_path	*ft_lstlast(t_path *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

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
        if(cwd[len] == '/' && len == 0)
            len += 1;
    }
    new_path = ft_calloc(len + 1,sizeof(char *));
    if(!new_path)
        return NULL;
    ft_strlcpy(new_path,cwd,len + 1);
    if(chdir(new_path) == -1)
    {
        (free(new_path),printf("error new path\n"));
        return NULL;
    }
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
            if(chdir(res) == -1)
                (free(res),printf("error home\n"));
            printf("new path: %s\n",res);
            return(res);
        }
        i++;
    }
    return (NULL);
}

void	ft_lstadd_back(t_path **lst, t_path *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

void ft_append(t_path **paths, char *res)
{   
    t_path *temp;

    temp = malloc(sizeof(t_path));
    if(!temp)
        return ;
    temp->pwd = ft_strdup(res);
    temp->pwd_old = ft_lstlast(*paths)->pwd;
    temp->next = NULL;
    ft_lstadd_back(paths,temp);
}

char *switch_cd(t_path **paths)
{   
    t_path *temp;
    char *res;
    temp = malloc(sizeof(t_path));
    if(!temp)
        return NULL;
    temp->pwd = ft_lstlast(*paths)->pwd_old;
    temp->pwd_old = ft_lstlast(*paths)->pwd;
    temp->next = NULL;
    ft_lstadd_back(paths,temp);
    res = ft_strdup(temp->pwd);
    if(chdir(res) == -1)
    {
        (free(res),printf("error switch: %s\n",res));
        return NULL;
    }
    printf("new path: %s\n",res);
    return (res);
}

void cd_cmd(char **str, t_path **paths, char **env)
{  
    char cwd[1024];
    t_path *temp;
    char *res;
    int check;

    check = 0;
    if(getcwd(cwd,sizeof(cwd)) == NULL)
        printf("error");
    if(!ft_strncmp(str[0],"cd",3) && str[1] == NULL)
        res = get_home(env);
    else if(str[1] != NULL && (!ft_strncmp(str[1],"..",3)))
        res = new_path(cwd,1); 
    else if(str[1] != NULL && (!ft_strncmp(str[1],"-",2)))
    {
        res = switch_cd(paths);
        check = 1;
    }
    else if(str[1] != NULL)
        res = new_path(str[1],0);
    if(check == 0 && res)
        ft_append(paths,res); 
    if(res)
        free(res);
}

