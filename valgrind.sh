valgrind --suppressions=readline_supp.txt --trace-children=yes --track-fds=yes --leak-resolution=high -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell
