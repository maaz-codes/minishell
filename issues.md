####exp: > out
Behaviour : This it prints execve() fail err msg in out.
Desired : Creates an empty out file.
Status : FIXED!

####exp: echo" " hi
Behaviour : Still prints hi. (executes the echo by removing qoutes and spaces )
Desired : Prints a msg that echo doesnt exist. (Removes qoutes but not spaces)
Status : 

####exp: cat << eof1 << eof2 > out1 > out2
Behaviour : Exiting after executing everything correctly.
Desired : Shouldn't exit.
Status : 