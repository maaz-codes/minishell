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


void replace_env(t_path **paths, t_path *new)
{   
    t_env *tmp;
    tmp = (*paths)->env_struct;
    int checker = 0;
    int i = 0;
    printf("enter in replace\n");
    while(tmp)
    {   
        if(!ft_strncmp(tmp->env,"PWD=",4))
        {   
            printf("enter here\n");
            free(tmp->env);
            tmp->env = ft_strdup(new->pwd);
            checker = 1;
            printf("new_pwd: %s\n",tmp->env);
            // return ;
        }
        printf("i: %d %s\n",i,tmp->env);
        i++;
        tmp = tmp->next;
    }
    if(!checker)
        printf("no PWD\n");
    return ;
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
    replace_env(paths,temp);
    ft_lstadd_back_path(paths,temp);
}

char *switch_cd(t_path **paths)
{   
    t_path *temp;
    char *res;
    char *pwd;
    char *pwd_old; 

    pwd = ft_strdup(ft_lstlast_path(*paths)->pwd);
    pwd_old = ft_strdup(ft_lstlast_path(*paths)->pwd_old);
    temp = malloc(sizeof(t_path));
    if(!temp)
        return NULL;
    temp->pwd = pwd_old;
    temp->pwd_old = pwd;
    temp->next = NULL;
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

