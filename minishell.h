/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:07:18 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/02 10:12:43 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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

// tree_utils.c
void				add_node(t_tree **tree, t_tree *node, int side);
void				print_data(t_tree *tree);
void				print_tree(t_tree *tree);

// tokenization
int					strip_spaces(char **str);
t_tree				*tokenization(char **str);
t_tree				*tokenizer(char *str, t_tree **node);

// tokens.c
t_tree				*init_exp_node(char **str);
t_tree				*init_log_op_node(char spl_op);
t_tree				*init_op_node(char op);
t_tree				*init_redir_node(char *redir);
t_tree				*init_file_node(char *str, int start, int end);
t_tree				*init_cmd_node(char *cmd_tmp);
t_tree				*init_args_node(char *args, char *cmd);
char 				*exp_after_redir_node(char *str, char *first_half, int start);
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
void 				free_str(char **str);

// lumberjack.c
void				lumberjack(t_tree *tree);
void				chop_branch(t_tree *node);
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
int					gallows(t_tree *tree, char **env, int pipe_flag, t_tree *ancient_one);
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