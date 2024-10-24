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

// int     tokenization(char *input);
char    symbol_checker(char s);
// int     checker_len(char *s);
int     checker_tokens(char *s);

char    **tokenization_char(char *input);
int     malloc_everything(char **res,char *s,int tokens);