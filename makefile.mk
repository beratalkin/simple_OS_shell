all: myshell execx writef
myshell: myshell.c
	gcc myshell.c -o m
	
execx: execx.c
	gcc execx.c -o e
	
writef: writef.c
	gcc writef.c -o w
