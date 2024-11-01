#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct space_check
{
    int *spaces;
} t_check;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy_modif(char *dst, const char *src, size_t dstsize, char symbol);
char	*ft_strjoin(char const *s1, char const *s2);


void    free_double(char **s);
char    symbol_checker(char s);
int     inside_check(int inside, int tokens);
int     malloc_safe(char **res, int position, size_t len);
int     checker_tokens(char *s, char symbol, int tokens, int inside);
char    **tokenization_char(char *input);
void     malloc_everything(char **res,char *s,int tokens, int position);

void    echo_cmd(char **str,char *input);
int     filler_last(char **res,char *s,int position,int len);