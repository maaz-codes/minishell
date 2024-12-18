NAME = minishell

CC = gcc -g3 #-fsanitize=address,undefined
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRCS = 	minishell.c \
		paths.c \
		signals.c \
		expansions/expansions.c \
		expansions/expansions_utils.c \
			execution/error.c \
			execution/gallows.c \
			execution/gallows_utils.c \
			execution/here_doc.c \
			execution/handle_nodes.c \
			execution/handle_utils.c \
				tree/lumberjack.c \
				tree/tree_utils.c \
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
		builtins/export_utils_3.c \
			helpers/ft_atol.c \
			helpers/ft_memset.c \
			helpers/ft_strlcpy.c \
			helpers/ft_atoi.c \
			helpers/ft_calloc.c \
			helpers/ft_bzero.c \
			helpers/ft_lstclear.c \

OBJS = $(SRCS:.c=.o)
LDFLAGS = -lreadline 
READLINEFLAGS = -L/opt/vagrant/embedded/lib/ -Iopt/vagrant/embedded/include/readline


all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(READLINEFLAGS) $^ -o $@ $(LDFLAGS)


#Add CFLAGS Later
%.o:%.c
	$(CC) -c $< -o $@ 

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: all clean fclean re bonus