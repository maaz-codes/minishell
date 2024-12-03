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
