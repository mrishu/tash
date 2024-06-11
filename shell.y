%{
#include <stdio.h>
#include "command.c"

#define YYSTYPE char*
int yylex(YYSTYPE* yylval);

void yyerror(const char *s)
{
    fprintf(stderr, "error: %s\n", s);
}

Command* currCmd = NULL; SimpleCommand* currSimCmd = NULL;
%}

/* declare tokens */
%token WORD 
%token PIPE
%token GREAT LESS GREATGREAT AMPERSANDGREAT AMPERSANDGREATGREAT
%token AMPERSAND 
%token EOL NOTOKEN

%define api.pure full
%define parse.error detailed

%%
command_line:
            /*nothing*/ { printf("$ "); }
            | command_line command EOL { printf("$ "); }
            | command_line EOL { printf("$ "); }
            | command_line error EOL { 
                printf("$ ");
                freeCmd(currCmd);
                freeSimCmd(currSimCmd);
                currCmd = NewCmd(); currSimCmd = NewSimCmd();
                yyerrok;
            }
            ;
command:
       pipe_list io_modifier_list background_opt {
            execute(currCmd);
            freeCmd(currCmd);
            freeSimCmd(currSimCmd);
            currCmd = NewCmd(); currSimCmd = NewSimCmd();
       }
io_modifier_list:
                io_modifier_list io_modifier
                | /*empty*/
                ;
io_modifier:
           GREAT WORD { currCmd -> outFile = $2; }
           | LESS WORD { currCmd -> inFile = $2; }
           | GREATGREAT WORD
           | AMPERSANDGREAT WORD { currCmd -> errFile = $2; }
           | AMPERSANDGREATGREAT WORD
           ;
pipe_list:
         pipe_list PIPE cmd_and_args {
            insertArgument(currSimCmd, NULL);
            insertSimpleCommand(currCmd, currSimCmd);
            currSimCmd = NewSimCmd();
         }
         | cmd_and_args {
            insertArgument(currSimCmd, NULL);
            insertSimpleCommand(currCmd, currSimCmd);
            currSimCmd = NewSimCmd();
         }
         ;
cmd_and_args:
            WORD { insertArgument(currSimCmd, $1); }
            | cmd_and_args WORD { insertArgument(currSimCmd, $2); }
            ;
background_opt:
              AMPERSAND { currCmd -> background = 1; }
              | /*empty*/
              ;
%%

int main(int argc, char **argv)
{
    currCmd = NewCmd(); currSimCmd = NewSimCmd();

    int ret = yyparse();
    
    freeCmd(currCmd);
    freeSimCmd(currSimCmd);

    return ret;
}
