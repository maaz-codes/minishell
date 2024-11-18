NAME 		= pipex
NAME_BONUS 	= pipex_bonus

SRC 		= 	pipex.c \
				process.c \
				errors.c \
				paths.c \
				libft/libft.c  libft/ft_split.c libft/ft_strtrim.c \
				get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

SRC_BONUS 	= 	pipex_bonus.c \
				process.c \
				errors.c \
				paths.c \
				here_doc.c \
				libft/libft.c  libft/ft_split.c libft/ft_strtrim.c \
				get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
REM		=	rm -rf

all: $(NAME)
bonus: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJ)
	cc $(CFLAGS) $^ -o $@

$(NAME_BONUS): $(OBJ_BONUS)
	cc $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(REM) $(OBJ)
	$(REM) $(OBJ_BONUS)

fclean: clean
	$(REM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
