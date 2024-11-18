<!-- Valgrind Flags -->
valgrind --leak-check=full --leak-resolution=high -s --trace-children=yes --track-fds=yes --track-origins=yes --show-leak-kinds=all

<!-- arguments count check -->
1. ./pipex  
2. ./pipex Makefile cat
3. ./pipex Makefile cat wc
4. ./pipex Makefile cat wc out
5. ./pipex Makefile cat wc out

<!-- Wrong arguments -->
6. ./pipex MAKE cat wc out
7. ./pipex Makefile ct wc out
8. ./pipex Makefile ct qwerty out
9. ./pipex Makefile ct qwerty out
0. ./pipex Makefile "" "" out

<!-- Change permissions for both files -->
10. chmod 000 outfile
11. chmod 000 infile

<!-- Path instead of cmd -->
12. ./pipex Makefile /usr/bin/cat /usr/bin/wc out

<!-- Unset path -->
13. unset PATH

<!-- Remove env -->
14. env -i /bin/valgrind ./pipex Makefile cat wc outfile

<!-- Random cases -->
15. ./pipex /dev/urandom cat "head -5" outfile
16. ./pipex /dev/urandom cat wc outfile
17. ./pipex Makefile "sleep 5" "echo hi" outfile 
17. ./pipex Makefile "sleep 3" "sleep 2" outfile 
18. ./pipex Makefile "sleep 2" "crt" outfile 
00. ./pipex Makefile "grep p" "awk '{count++} END {print count}'" outfile 

<!-- program that fails on purpose -->
19. ./pipex Makefile test/a.out /usr/bin/wc out

<!-- Creating script that uses wrong interpreter for execve() -->
<!-- Valid script -->
#!/bin/bash
echo "this script works!"
<!-- Invalid script -->
#!/wrong_interpreter
echo "This script does not work"

<!-- Garbage -->
garbage=$(cat /dev/urandom | head -10)
./pipex Makefile "$age" "$garbage" get_next_line/test

<!-- For bonus -->

1. 
