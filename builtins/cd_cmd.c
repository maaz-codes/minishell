#include "../minishell.h"

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

void ft_append(t_path **paths, char *res)
{   
    t_path *temp;
    char *old_path;
    char *new_path;

    old_path = ft_strdup(ft_lstlast_path(*paths)->pwd);
    new_path = ft_strdup(res);
    temp = malloc(sizeof(t_path));
    if(!temp)
        return ;
    temp->pwd = new_path;
    temp->pwd_old = old_path;
    temp->next = NULL;
    (add_NEWPWD(paths,temp),add_OLDPWD(paths,temp));
    ft_lstadd_back_path(paths,temp);
}
int check_old_pwd(t_path **paths)
{
    t_env *tmp;

    tmp = (*paths)->env_struct;
    while(tmp)
    {
        if(!ft_strncmp(tmp->env,"OLDPWD=",7))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

int valid_old_pwd(t_path **paths)
{
    t_env *tmp;
    char **old_pwd;

    tmp = (*paths)->env_struct;
    while(tmp)
    {
        if(!ft_strncmp(tmp->env,"OLDPWD=",7))
        {
           old_pwd = ft_split(tmp->env,'=');
           if(chdir(old_pwd[1]) == -1)
           {    
                printf("minishell: cd: %s: No such file or directory\n",old_pwd[1]);
                free_double(old_pwd);
                return (0);         
           }
        }
        tmp = tmp->next;
    }
    return (1);
}

//
char *switch_cd(t_path **paths)
{   
    t_path *temp;
    char *res;
    
    if(!check_old_pwd(paths))
    {
        printf("OLDPWD is not set\n");
        return (NULL);
    }
    if(!valid_old_pwd(paths))
        return (NULL);
    temp = malloc(sizeof(t_path));
    if(!temp)
        return NULL;
    temp->pwd = ft_strdup(ft_lstlast_path(*paths)->pwd_old);
    temp->pwd_old = ft_strdup(ft_lstlast_path(*paths)->pwd);
    temp->next = NULL;
    (add_NEWPWD(paths,temp),add_OLDPWD(paths,temp));
    ft_lstadd_back_path(paths,temp);
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
    char *res;
    int check;

    check = 0;
    if(getcwd(cwd,sizeof(cwd)) == NULL)
        printf("error");
    if(!ft_strncmp(str[0],"cd",3) && str[1] == NULL)
        res = get_home(paths);
    else if(!ft_strncmp(str[0],"cd",3) && (!ft_strncmp(str[1],"~",2)))
        res = get_home(paths);
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

