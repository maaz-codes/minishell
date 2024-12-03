NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = 	minishell.c \
		error.c \
		gallows.c \
		gallows_utils.c \
		here_doc.c \
		expansions.c \
			tree/tree_utils.c \
			tree/free_tree.c \
				helpers/ft_strchr.c \
				helpers/ft_strdup.c \
				helpers/ft_strlen.c \
				helpers/ft_strtrim.c \
				helpers/ft_substr.c \
				helpers/ft_strncmp.c \
				helpers/ft_strjoin.c \
				helpers/ft_split.c \
					parsing/qoutes.c \
					parsing/splits.c \
					parsing/syntax.c \
					parsing/token_utils.c \
					parsing/tokenization.c \
					parsing/tokens.c \
	signals.c \
		builtins/echo_cmd.c \
		builtins/pwd_cmd.c \
		builtins/cd_cmd.c \
		builtins/cd_utils.c \
		builtins/cd_utils_2.c \
		builtins/exit_cmd.c \
		builtins/env_cmd.c \
		builtins/unset_cmd.c \
		builtins/export_cmd.c \
		builtins/exit_utils.c \
		builtins/export_utils.c \
		builtins/export_utils_2.c \
			libft/ft_atol.c \
			libft/ft_memset.c \
			libft/ft_strlcpy.c \
			libft/ft_atoi.c \
			libft/ft_calloc.c \
			libft/ft_bzero.c \
			libft/ft_lstclear.c \
			libft/ft_atol.c \
			libft/ft_free_double.c 
			

OBJS = $(SRCS:.c=.o)
LDFLAGS = -l readline

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

#Add CFLAGS Later
%.o:%.c
	$(CC) -c $< -o $@ 

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: all clean fclean re bonus