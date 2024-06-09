shell: shell.l shell.y
	bison -d shell.y
	flex --bison-bridge shell.l
	gcc -o $@ -lfl lex.yy.c shell.tab.c

clean:
	rm -f shell.tab.h shell.tab.c lex.yy.c test

test:
	gcc -o $@ command_test.c
