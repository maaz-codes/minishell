NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = minishell.c tokenization.c echo_cmd.c pwd_cmd.c token_utils.c libft/ft_split.c libft/ft_strncmp.c libft/ft_strlcpy.c \
		libft/ft_strlen.c libft/ft_strdup.c libft/ft_strjoin.c 

OBJS = $(SRCS:.c=.o)
LDFLAGS = -lreadline

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