#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// error_codes
# define ERR_FORMAT 1001
# define ERR_MALLOC 1002

// general
# define TRUE 	1
# define FALSE 	0

// Node_types
// # define NODE_COMMAND 		4201
// # define NODE_OPERATOR 		4202
// # define NODE_ARGUMENT 		4203
// # define NODE_REDIRECTION 	4204
// # define NODE_EXPRESSION 	4205

typedef enum S_TYPES
{
    NODE_COMMAND = 4201,
    NODE_OPERATOR,
    NODE_ARGUMENT,
    NODE_REDIRECTION,
    NODE_EXPRESSION
} t_types;

typedef struct s_tree {
    t_types type;
    char pos;
    int level;
    union 
    {
        char *expression;
        char *command;      
        char *argument;    
        char operator;    
        char *redirection;
        char *env_expansion;  
    } data;
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

// tokenization
void strip_spaces(char **str);
char	**tokenization(char *str);
t_tree *tokenizer(char *str, t_tree **node);

// tokens.c
t_tree *init_op_node(char op);
t_tree *init_exp_node(char *str, int start, int end);
t_tree *init_cmd_node(char *str, int end);
t_tree *init_args_node(char *str, int start, int end);

// qoutes.c
int	inside_qoutes(int *qoutes, char c, char *str, int *i);
int count_qoutes(char *str);
char *remove_qoutes(char *str);

// tokens_utils.c
char	symbol_checker(char s);

// error.c
void	print_error(int code);
void	print_exit(int code);

// main.c
int operator_ahead(char *str, int i);
int cmd_split(char *str, int *i, t_tree **node);
int operator_split(char *str, t_tree **node, int i, int j);
int qoutes_checker(char *str);