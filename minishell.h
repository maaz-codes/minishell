#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

void    free_double(char **s);
char    symbol_checker(char s);
int     null_check(char **res, char *s);
int     malloc_safe(char **res, int position, size_t len);
int     checker_tokens(char *s, char symbol, int tokens, int inside);
char    **tokenization_char(char *input);
int     malloc_everything(char **res,char *s,int tokens, int position);