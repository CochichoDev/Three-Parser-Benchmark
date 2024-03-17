grammar ANTLRGrammar;

expression : term ( (PLUS | MINUS) term )* ;
term       : factor ( (TIMES | DIVIDE) factor )* ;
factor     : digit | LPAREN expression RPAREN ;

digit      : NUMBER ;

WS         : [ \t\r\n]+ -> skip ;

PLUS : '+';
MINUS : '-';
TIMES : '*';
DIVIDE : '/';
NUMBER : [0-9]+;
LPAREN : '(';
RPAREN : ')';
