NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = 	minishell.c \
		token_utils.c \
		qoutes.c \
		tokens.c \
		token_utils.c \
		tree_utils.c \
		error.c \
		tokenization.c \
		splits.c \
		free_tree.c \
		syntax.c \
		execution.c \
		helpers/ft_strchr.c helpers/ft_strdup.c helpers/ft_strlen.c helpers/ft_strtrim.c helpers/ft_substr.c helpers/ft_strncmp.c helpers/ft_strjoin.c \
				pipex/process.c \
				pipex/errors.c \
				pipex/paths.c \
				pipex/here_doc.c \
				pipex/libft/libft.c  pipex/libft/ft_split.c pipex/libft/ft_strtrim.c \
				pipex/get_next_line/get_next_line.c pipex/get_next_line/get_next_line_utils.c \
		

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