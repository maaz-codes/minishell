###Readline suppression
valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

####exp: > out
Behaviour : This it prints execve() fail err msg in out.
Desired : Creates an empty out file.
Status : FIXED!

####exp: ls < in1
Behaviour : ls shouldn't work if in1 doesn't exist.
Desired : It still prints ls content & doesn't print err for in1 not existing.
Status : FIXED!

####exp: echo" " hi
Behaviour : Still prints hi. (executes the echo by removing qoutes and spaces )
Desired : Prints a msg that echo doesnt exist. (Removes qoutes but not spaces)
Status : FIXED!

####exp: cat << eof1 << eof2 > out1 > out2
Behaviour : Exiting after executing everything correctly.
Desired : Shouldn't exit.
Status : FIXED!

####exp: ><
Behaviour : Taking it as a valid expression.
Desired : Should throw a syntax error.
Status : FIXED!

####exp: ls | |
Behaviour : Doesn't throw a syntax error.
Desired : Should throw a syntax error.
Status : FIXED!

####exp: "" | ""
Behaviour : Doesn't print anything.
Desired : Should parse the empty strings and give cmd not found twice.
Status : 

####exp: echo $SHLVL
Behaviour : Doesn't print the things that are just one char long.
Desired : Should print every value as long as it exists.
Status : 

####exp: echo $PWDPP
Behaviour : Still prints PWD (kinda trimmed PWD).
Desired : Should not print anything.
Status : 

###Fix the here_doc for appending

### expand $?

### env -i ./minishell

##CMDS
<!-- leaks: DONE! -->
<!-- fds : DONE! -->
<!-- behaviour: DONE! -->

#PIPES
<!-- leaks: DONE! -->
<!-- fds: DONE! -->
<!-- behaviour: DONE! -->

##BUILTINS
<!-- leaks: DONE! -->
<!-- fds: DONE! -->
behaviour: echo, export, unset

#REDIRECTIONS
leaks: 
fds:
behaviour:

#HEREDOC
leaks:
fds:
behaviour:

#SIGNALS
leaks:
fds:
behaviour:

#MIX
leaks:
fds:
behaviour:

###Redundant Code
1. Stop passing int j everywhere, it's value is always zero.
