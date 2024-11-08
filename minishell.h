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

// tree_utils.c
void add_node(t_tree **tree, t_tree *node);
void print_data(t_tree *tree);
void print_tree(t_tree *tree);

// tokens.c
t_tree *init_op_node(char op);
t_tree *init_exp_node(char *str, int start, int end);

// qoutes.c
int	inside_qoutes(int *qoutes, char c, char *str, int *i);
int count_qoutes(char *str);
char *remove_qoutes(char *str);

// tokens_utils.c
char	symbol_checker(char s);