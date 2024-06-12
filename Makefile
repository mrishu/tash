shell: shell.l shell.y shell_utils.c shell_builtins.c
	bison -d shell.y
	flex --bison-bridge shell.l
	gcc -o $@ -lfl lex.yy.c shell.tab.c

clean:
	rm -f shell.tab.h shell.tab.c lex.yy.c test
