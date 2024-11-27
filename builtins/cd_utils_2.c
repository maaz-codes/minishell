#include "../minishell.h"

char *get_cwd(void)
{
    char cwd[1024];
    char *res;
    if(getcwd(cwd,sizeof(cwd)) == NULL)
        printf("error");
    res = new_path(cwd,0);
    return(res);
}

t_path	*int_cd(void)
{
	t_path	*node_new;
    char    *str1;
    char    *str2;

    str1 = get_cwd();
    str2 = get_cwd();
	node_new = (t_path *)malloc(sizeof(t_path));
	if (node_new == NULL)
		return (NULL);
	node_new->pwd = str1;
	node_new->pwd_old = str2;
	node_new->next = NULL;
	return (node_new);
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

char *get_home(t_path **paths)
{
    char **holder;
    char *res;

    while((*paths)->env_struct)
    {
        if(!ft_strncmp((*paths)->env_struct->env,"HOME=",5))
        {   
            holder = ft_split((*paths)->env_struct->env, '=');
            res = new_path(holder[1],0);
            free_double(holder);
            if(chdir(res) == -1)
                (free(res),printf("error home\n"));
            return (res);
        }
        (*paths)->env_struct = (*paths)->env_struct->next;
    }
    printf("minishell: cd: HOME not set\n");
    return (NULL);
}