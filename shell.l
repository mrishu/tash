%{
#include <string.h>
#include "shell.tab.h"

#define YYSTYPE char*
%}

%%
\n          { return EOL; }
[ \t]       { /* Discard spaces and tabs */ }
">"         { return GREAT; }
"<"         { return LESS; }
"|"         { return PIPE; }
">>"        { return GREATGREAT; }
">&"        { return GREATAMPERSAND; }
"&"         { return AMPERSAND; }

[^ ><&|\t\n]+ {
    *yylval = strdup(yytext);
    return WORD;
}
. {
    /* Invalid character */
    return NOTOKEN;
}
%%
