#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



// error_codes
# define WRONG_FORMAT 1001

// general
# define TRUE 	1
# define FALSE 	0


// Node_types
# define NODE_COMMAND 		4201
# define NODE_OPERATOR 		4202
# define NODE_ARGUMENT 		4203
# define NODE_REDIRECTION 	4204
# define NODE_EXPRESSION 	4205

typedef struct s_tree {
    int type;
    union 
    {
        char *expression;
        char *command;      
        char *argument;    
        char operator;    
        char *redirection;
        char *env_expansion;  
    } t_data;
    struct s_tree *left;  
    struct s_tree *right;
} t_tree;

// helpers
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);

// tokens_utils
char	symbol_checker(char s);