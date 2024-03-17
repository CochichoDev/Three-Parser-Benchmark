#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define LF 0x0a

/* Minimal lexer */

FILE *input;    // source input file
int token;      // last token read
int source_index;
void next_token() { source_index++; token = fgetc(input); }

/* Minimal syntax checker */

void expect_token(int expected_token) {
    if (token != expected_token) {
        fprintf(stderr,"Error at character position %d, ",source_index);
        fprintf(stderr,"read '%c' instead of '%c'\n", token,expected_token);
    }
    next_token();
}

/* Mini LLVM code generator */
FILE *output;
typedef int llvm_index;

llvm_index llvm_value_index;

llvm_index llvm_make_value(int value) {
    fprintf(output, "%%%d = add i32 0, %d\n", ++llvm_value_index, value);
    return llvm_value_index;
}

llvm_index llvm_generate_op(char operator, llvm_index operand1, llvm_index operand2) {
    fprintf(output, "%%%d = ", ++llvm_value_index);
    switch(operator) {
        case '+': fprintf(output, "add"); break;
        case '-': fprintf(output, "sub"); break;
        case '*': fprintf(output, "mul"); break;
        case '/': fprintf(output, "sdiv");break;
    }
    fprintf(output," i32 %%%d, %%%d\n", operand1, operand2);
    return llvm_value_index;
}

void llvm_generate_result(llvm_index result) {
    fprintf(output, "ret i32 %%%d\n",result);
}

/* Recursive-descent parser */

typedef struct {   /* minimal structure of the AST */
    llvm_index index;
} Value;

Value expression(); // declare main recursive function

Value factor() {
    Value x;
    if (isdigit(token)) {
        x.index = llvm_make_value(token-'0');
        next_token();
    } else {
        expect_token('(');
        x = expression();
        expect_token(')');
    }
    return x;
}

Value term() {
    Value x = factor();
    while (token == '*' || token == '/') {
        char operator = token;
        next_token();
        Value y = factor();
        x.index = llvm_generate_op(operator, x.index, y.index);
    }
    return x;
}

Value expression() {
    Value x = term();
    while (token == '+' || token == '-') {
        char operator = token;
        next_token();
        Value y = term();
        x.index = llvm_generate_op(operator, x.index, y.index);
    }
    return x;
}

int main(int argc, char *argv[]) {
    if (argc != 2 || !(input = fopen(argv[1],"r"))) {
        fprintf(stderr, "Usage: %s <input-file>\n",argv[0]);
        exit(1);
    }
    output = stdout;
    next_token();
    Value x = expression();
    expect_token(LF);
    llvm_generate_result(x.index);
    return 0;
}
