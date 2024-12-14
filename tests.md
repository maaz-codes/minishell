1. 
2.      " "
3.      a
4.      "a"
####Commands
5.      ls
6.      wc -l
7.      cat

####Redirections
8.      ls > out
9.      ls >> out
10.     cat < Makefile
11.     cat << eof
12.     ls > out1 > out2 > out3
13.     ls >> out1 >> out2 > out3
14.     cat < Makefile > out1 >> out2
15.     ls << 1 << 2 << 3 << 4 > out


<!-- Builtins -->

<!-- CD : FIXED -->
need to fix cd- going back and fourth

<!-- ECHO : FIXED -->
echo -n -n Hello
{treat multiple flags as just one}

<!-- EXPORT -->
export =value
{should give error that '=value' is not a valid name}

export VAR=value
export VAR+=VALUE
{VAR should become "valueVALUE"}

need to update the old PWD and current PWD;

<!-- UNSET : FIXED --> 
unset
{should not give error}

unset 123VAR
{should give error as not a valid identifier}

<!-- PIPES -->
wrong_cmd | wrong_cmd
{leaks everywhere}

cmd | cmd
{perfect}

cmd | cmd | cmd
{leaks everywhere}

<!-- REDIRECTIONS -->
> out
{exits for sm reason}

echo hi > out
echo hi > out
{exits the second time you use redirections}
