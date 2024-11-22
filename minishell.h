#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct env{
    
    char *env;
    struct env *next;
}   t_env;

typedef struct pwd{

    char *pwd;
    char *pwd_old;
    struct pwd *next;
    t_env *env_struct;
}   t_path;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy_modif(char *dst, const char *src, size_t dstsize, char symbol);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_lstclear(t_path **lst);
void	ft_lstdelone(t_path **lst);
int     ft_atoi(char *s);
void    *ft_memset(void *b, int c, size_t len);


void    free_double(char **s);
char    symbol_checker(char s);
int     malloc_safe(char **res, int position, size_t len);
int     checker_tokens(char *s, char symbol, int tokens, int inside);
char    **tokenization_char(char *input);
void     malloc_everything(char **res,char *s,int tokens, int position);
int     filler_last(char **res,char *s,int position,int len);


void    echo_cmd(char **str);
void    pwd_cmd(char **str);
void    exit_cmd(t_path **paths, char **str);

void    env_cmd(char **str, t_path **paths);
t_env   *int_env(char **env);

void    cd_cmd(char **str, t_path **paths, char **env);
char    *new_path(char *cwd, int id);
t_path	*ft_lstlast_path(t_path *lst);
void	ft_lstadd_back_path(t_path **lst, t_path *new);
void    add_NEWPWD(t_path **paths, t_path *new);
void    add_OLDPWD(t_path **paths, t_path *new);

void    unset_cmd(char **str, t_path **paths);

void    export_cmd(char **str, t_path **paths);
t_env	*lstlast_env(t_env *lst);

void    set_signals(void);
void    set_signals_after(void);


