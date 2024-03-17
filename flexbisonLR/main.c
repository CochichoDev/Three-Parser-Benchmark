#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        exit(1);
    }

	yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: Couldn't open input file %s\n", argv[1]);
        exit(1);
    }

	do {
		yyparse();
	} while(!feof(yyin));

    fclose(yyin);

	return 0;
}
