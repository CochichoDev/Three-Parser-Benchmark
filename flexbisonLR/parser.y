%{
#include <stdio.h>
#include <stdlib.h>
#include "code_generator.h"
%}

%union {
	int num;
    char op;
    struct sASTNode *node;
}

%token<num> NUMBER
%token<op> PLUS MINUS TIMES DIVIDE LPAREN RPAREN

%type<node> factor term expression
%%

input: expression {
        generateLLVMCode(stdout, $1);
    }
;

expression: term
          | expression PLUS term    { $$ = createNode('+', 0, $1, $3); }
          | expression MINUS term   { $$ = createNode('-', 0, $1, $3); }
          ;

term: factor
    | term TIMES factor   { $$ = createNode('*', 0, $1, $3); }
    | term DIVIDE factor  { $$ = createNode('/', 0, $1, $3); }
    ;

factor: NUMBER  { $$ = createNode('\0', $1, NULL, NULL); }
      | LPAREN expression RPAREN   { $$ = $2; }
      ;

%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
