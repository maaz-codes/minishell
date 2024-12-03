NAME = minishell

CC = gcc -g -fsanitize=address,undefined
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRCS = 	minishell.c \
		error.c \
		gallows.c \
		gallows_utils.c \
		here_doc.c \
		expansions.c \
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
		signals.c \
		builtins/echo_cmd.c \
		builtins/pwd_cmd.c \
		builtins/cd_cmd.c \
		builtins/cd_utils.c \
		builtins/exit_cmd.c \
		builtins/env_cmd.c \
		builtins/unset_cmd.c \
		builtins/export_cmd.c \
		builtins/exit_utils.c \
		builtins/export_utils.c \
		builtins/export_utils_2.c \
			helpers/ft_atol.c \
			helpers/ft_memset.c \
			helpers/ft_strlcpy.c \
			helpers/ft_atoi.c \
			helpers/ft_calloc.c \
			helpers/ft_bzero.c \
			helpers/ft_lstclear.c \

OBJS = $(SRCS:.c=.o)
# LDFLAGS = -lreadline 
LDFLAGS = -L/usr/local/opt/readline/8.2.1/lib -lreadline 


all:$(NAME)

# potential flag needed
# $(CC) $(CFLAGS) -L/opt/vagrant/embedded/lib/ -Iopt/vagrant/embedded/include/readline
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