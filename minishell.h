#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct pwd{

    char *pwd;
    char *pwd_old;
    struct pwd *next;
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
t_path	*ft_lstnew(char *content);


void    free_double(char **s);
char    symbol_checker(char s);
int     malloc_safe(char **res, int position, size_t len);
int     checker_tokens(char *s, char symbol, int tokens, int inside);
char    **tokenization_char(char *input);
void     malloc_everything(char **res,char *s,int tokens, int position);

void    echo_cmd(char **str);
int     filler_last(char **res,char *s,int position,int len);
void    pwd_cmd(void);
void    cd_cmd(char **str, t_path **paths, char **env);
char    *new_path(char *cwd, int id);
