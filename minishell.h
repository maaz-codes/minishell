/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:07:18 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/21 16:40:34 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// general
#define TRUE 1
#define FALSE 0

// error_codes
typedef enum s_err_codes
{
	ERR_FORMAT = 1001,
	ERR_MALLOC,
	ERR_FORK,
	ERR_EXECVE,
	ERR_FILE
} t_err_codes;

typedef enum s_redir 
{
	REDIR_IN = 2001,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC
} t_redir;

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
	// char *env_expansion;
}					t_data;

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
void				add_node(t_tree **tree, t_tree *node);
void				print_data(t_tree *tree);
void				print_tree(t_tree *tree);

// tokenization
void				strip_spaces(char **str);
t_tree				*tokenization(char *str);
t_tree				*tokenizer(char *str, t_tree **node);

// syntax.c
int					check_log_op_node(t_tree *node);
int					check_op_node(t_tree *node);
int					check_redir_node(t_tree *node, t_tree *parent);
// check_cmd_node(t_tree *node);

// tokens.c
t_tree				*init_exp_node(char *str, int start, int end);
t_tree				*init_log_op_node(char spl_op);
t_tree				*init_op_node(char op);
t_tree				*init_redir_node(char *redir);
t_tree				*init_file_node(char *str, int start, int end);
t_tree				*init_cmd_node(char *str, int end);
t_tree				*init_args_node(char *str, int start, int end, char *cmd);
char 				*exp_after_redir_node(char *str, int j, int i);
char 				*extract_file_name(char *str, int start, int end);

// qoutes.c
int					inside_qoutes(int *qoutes, char c, char *str, int *i);
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
int					split_cmd(char *str, int *i, t_tree **node);
char				**split_args(char *str, char *cmd);

// gallows.c
void gallows(t_tree *tree, char **env);
void	execute(char **cmd, char *env[]);

// gallows_utils.c
char	*ft_cmd_exits(char **env, char *temp_cmd);

// main.c
int					qoutes_checker(char *str);