%{
#include "shell.tab.h"

#define YYSTYPE char*
%}

%%
\n           { return EOL; }
[ \t]        { /* Discard spaces and tabs */ }
'[^']+'|\"[^"]+\"|[^ '"><&|\t\n]+ {
    if (yytext[0] == '"' || yytext[0] == '\'') { // if within quotes
        yytext[strlen(yytext) - 1] = '\0'; // replace end quote with \0
        yytext = yytext + 1; // move pointer of yytext one step ahead of starting quote
    }
    *yylval = strdup(yytext); // duplicate the matched text (yytext) to yylval, this needs to be freed later
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
