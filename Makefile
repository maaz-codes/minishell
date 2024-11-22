NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = minishell.c signals.c tokenization.c builtins/echo_cmd.c builtins/pwd_cmd.c builtins/cd_cmd.c builtins/exit_cmd.c \
		builtins/env_cmd.c builtins/cd_utils.c builtins/unset_cmd.c builtins/export_cmd.c token_utils.c libft/ft_split.c libft/ft_memset.c\
		libft/ft_strncmp.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_atoi.c \
		libft/ft_calloc.c libft/ft_bzero.c libft/ft_lstclear.c \

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