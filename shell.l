%{
#include "shell.tab.h"

#define YYSTYPE char*
%}

%%
\n           { return EOL; }
[ \t]        { /* Discard spaces and tabs */ }
'[^'\n]+'|\"[^"\n]+\"|[^ '"><&|\t\n]+ {
    if (*yytext == '"' || *yytext == '\'') { // if within quotes
        *(yytext + strlen(yytext) - 1) = '\0'; // replace end quotes with \0
        yytext = yytext + 1; // move pointer of yytext one step ahead of starting quotes
    }
    *yylval = strdup(yytext); // this needs to be freed
    return WORD;
}
"|"          { return PIPE; }
">"          { return GREAT; }
"<"          { return LESS; }
">>"         { return GREATGREAT; }
"&>"         { return AMPERSANDGREAT; }
"&>>"        { return AMPERSANDGREATGREAT; }
"&"          { return AMPERSAND; }
. {
    /* Invalid character */
    return NOTOKEN;
}
%%
