%{
#include "shell.tab.h"

#define YYSTYPE char*
%}

%%
\n           { return EOL; }
[ \t]        { /* Discard spaces and tabs */ }
"|"          { return PIPE; }
">"          { return GREAT; }
"<"          { return LESS; }
">>"         { return GREATGREAT; }
"&>"         { return AMPERSANDGREAT; }
"&>>"        { return AMPERSANDGREATGREAT; }
"&"          { return AMPERSAND; }
[^ ><&|\t\n]+ {
    *yylval = strdup(yytext);
    return WORD;
}
. {
    /* Invalid character */
    return NOTOKEN;
}
%%
