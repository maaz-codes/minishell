/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:07:18 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/03 12:32:29 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

// general
#define TRUE 1
#define FALSE 0
#define LEFT 0
#define RIGHT 1

// error_codes
typedef enum s_err_codes
{
	ERR_FORMAT = 1001,
	ERR_MALLOC,
	ERR_FORK,
	ERR_EXECVE,
	ERR_FILE,
	ERR_PIPE,
	ERR_CMD
}					t_err_codes;

typedef struct env
{
	char			*env;
	struct env		*next;
}					t_env;

typedef struct s_exp
{
	char			*exp;
	struct s_exp	*next;
}					t_exp;

typedef struct s_path
{
	char			*pwd;
	char			*pwd_old;
	struct s_path	*next;
	t_env			*env_struct;
	t_exp			*exp_struct;
}					t_path;

typedef enum s_node_types
{
	NODE_COMMAND = 4201,
	NODE_OPERATOR,
	NODE_ARGUMENT,
	NODE_REDIRECTION,
	NODE_EXPRESSION,
	NODE_LOG_OPERATOR,
	NODE_FILE
}					t_node_types;

typedef union s_data
{
	char			*expression;
	char			*log_operator;
	char			operator;
	char			*redirection;
	char			*file;
	char			*command;
	char			**argument;
	int				here_doc;
	// char *env_expansion;
}					t_data;

typedef struct s_std_fds
{
	int				std_in;
	int				std_out;
	int				std_err;
}					t_std_fds;

typedef struct s_tree
{
	t_node_types	type;
	char			pos;
	int				level;
	t_data			data;
	struct s_path   *paths; //new raph
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

// helpers
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(const char *s, char c);

// int	ft_strncmp(const char *s1, const char *s2, size_t n);
// char	**ft_split(char *s, char c);
// size_t	ft_strlen(const char *s);
// char	*ft_strdup(const char *s1);
// char	*ft_strchr(const char *s, int c);
// char	*ft_strjoin(char const *s1, char const *s2);
// size_t	ft_strlcpy_modif(char *dst, const char *src, size_t dstsize, char symbol);
// void	ft_lstdelone(t_path **lst);

// helpers - raph
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int     ft_atoi(char *s);
void    *ft_memset(void *b, int c, size_t len);
unsigned long long	ft_atol(char *s);

// raph
void	ft_lstclear(t_path **lst);
void	ft_lstclear_env(t_env **lst);
void    free_double(char **s);

// char    symbol_checker(char s);
// int     malloc_safe(char **res, int position, size_t len);
// int     checker_tokens(char *s, char symbol, int tokens, int inside);
// char    **tokenization_char(char *input);
// void     malloc_everything(char **res,char *s,int tokens, int position);
// int     filler_last(char **res,char *s,int position,int len);

// raph - builtins
void    echo_cmd(char **str);
void    pwd_cmd(char **str);
void    exit_cmd(t_path **paths, char **str);
void    valid_num(char *s, t_path **paths);
void    error_msg(char *str,t_path **paths);

void    env_cmd(char **str, t_tree *tree);
t_env   *int_env(char **env);

void    cd_cmd(char **str, t_path **paths);
char 	*get_cwd(void);
t_path	*int_cd(void);
char    *new_path(char *cwd, int id);
t_path	*ft_lstlast_path(t_path *lst);
void	ft_lstadd_back_path(t_path **lst, t_path *new);
void    add_NEWPWD(t_path **paths, t_path *new);
void    add_OLDPWD(t_path **paths, t_path *new);
char 	*new_path(char *cwd, int id);
char 	*get_home(t_path **paths);	

void    unset_cmd(char **str, t_path **paths);

void    export_cmd(char **str, t_path **paths);
t_env	*lstlast_env(t_env *lst);
char    **separator(char *str);
t_exp   *int_exp(char **env);
void    exp_print(t_path **paths);
t_exp	*lstlast_exp(t_exp *lst);
void    ap_exp(t_exp **paths, char *res);

// raph - signals
void    set_signals(void);
void    set_signals_after(void);

// tree_utils.c
void				add_node(t_tree **tree, t_tree *node, int side);
void				print_data(t_tree *tree);
void				print_tree(t_tree *tree);

// tokenization
int					strip_spaces(char **str);
t_tree				*tokenization(char *str);
t_tree				*tokenizer(char *str, t_tree **node);

// tokens.c
t_tree				*init_exp_node(char *str, int start, int end);
t_tree				*init_log_op_node(char spl_op);
t_tree				*init_op_node(char op);
t_tree				*init_redir_node(char *redir);
t_tree				*init_file_node(char *str, int start, int end);
t_tree				*init_cmd_node(char *str, int end);
t_tree				*init_args_node(char *str, int start, int end, char *cmd);
char				*exp_after_redir_node(char *str, int start, int end,
						int append);
char				*extract_file_name(char *str, int start, int end);

// qoutes.c
int					inside_qoutes(char qoute, char *str, int i);
int					count_qoutes(char *str);
char				*remove_qoutes(char *str);

// tokens_utils.c
char				symbol_checker(char s);
int					redirection_ahead(char *str, int i);
int					spl_operator_ahead(char *str, int i);
int					operator_ahead(char *str, int i);
int					skip_spaces(char *str, int *i);

// error.c
int					print_error(int code);
void				print_exit(int code);

// free_tree.c
void				free_tree(t_tree *tree);
void				free_node(t_tree *node);
void				free_array(char **array);

// splits.c
int					count_args(char *str);
int					split_log_operator(char *str, t_tree **node, int i, int j);
int					split_operator(char *str, t_tree **node, int i, int j);
int					split_redirection(char *str, t_tree **node, int i, int j);
int					split_file(char *str, int *i, t_tree **node);
int					split_cmd(char *str, int i, t_tree **node);
char				**split_args(char *str, char *cmd);

// gallows.c
void				gallows(t_tree *tree, char **env, int fork_flag);
void				execute(char **cmd, char *env[]);

// gallows_utils.c
char				*ft_cmd_exits(char **env, char *temp_cmd);

// here_doc
void				find_docs(t_tree *tree);
int					ft_here_doc(char *limiter);

// syntax.c
int					check_log_op_node(t_tree *node);
int					check_op_node(t_tree *node);
int					check_redir_node(t_tree *node);
int					syntax_checker(t_tree *tree);

// expansions.c
char				*extract_env_var(char *str, int start, int *index);
char				*assign_value(char *env_var, t_env *env);
char				*expanded_str(char *str, char *env_var, int start, int end);
char				*env_expansion(char *str, t_env *env);

// main.c
int					qoutes_checker(char *str);