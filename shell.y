%{
#include "shell.h"
#include "shell_builtins.c"
#include "command.c"
#include "shell_utils.c"
#define YYSTYPE char*
int yylex(YYSTYPE* yylval);

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

Command *currCmd = NULL; SimpleCommand *currSimCmd = NULL;
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
            /*empty*/ { print_prompt(); }
            | command_line command EOL { print_prompt(); }
            | command_line EOL { print_prompt(); }
            | command_line error EOL { 
                freeCmd(currCmd); freeSimCmd(currSimCmd);
                print_prompt();
                currCmd = NewCmd(); currSimCmd = NewSimCmd();
                yyerrok;
            }
            ;
command:
       pipe_list io_modifier_list background_opt {
            execute(currCmd);
            freeCmd(currCmd); freeSimCmd(currSimCmd);
            currCmd = NewCmd(); currSimCmd = NewSimCmd();
       }
       ;
io_modifier_list:
                io_modifier_list io_modifier
                | /*empty*/
                ;
io_modifier:
           GREAT WORD { currCmd -> outFile = $2; }
           | LESS WORD { currCmd -> inFile = $2; }
           | GREATGREAT WORD { currCmd -> outFile = $2; currCmd -> out_append =1;}
           | AMPERSANDGREAT WORD { currCmd -> errFile = $2; }
           | AMPERSANDGREATGREAT WORD { currCmd -> errFile = $2; currCmd -> err_append =1;}
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

int main(int argc, char **argv) {
    currCmd = NewCmd(); currSimCmd = NewSimCmd();
    welcome_msg();
    yyparse();
    freeCmd(currCmd); freeSimCmd(currSimCmd);
    return 0;
}
