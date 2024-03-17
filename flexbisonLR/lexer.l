%option noyywrap

%{
#include <stdio.h>

#include "parser.tab.h"

%}

%%

[ \t\n]          /* Ignore whitespace */
"+"              { return PLUS; }
"-"              { return MINUS; }
"*"              { return TIMES; }
"/"              { return DIVIDE; }
"("              { return LPAREN; }
")"              { return RPAREN; }
[0-9]+           { yylval.num = atoi(yytext); return NUMBER; }

.       {}

%%
