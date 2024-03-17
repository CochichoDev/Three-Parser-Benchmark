#pragma once
#include <stdio.h>

typedef int llvm_index;

typedef struct sASTNode {
    char op;        // Operator: '+', '-', '*', '/'
    int num;        // Number: Used for leaf nodes (NUMBER terminal)
    struct sASTNode* left;
    struct sASTNode* right;
} ASTNodeEntry;

llvm_index llvm_make_value(FILE *output, int value);
llvm_index llvm_generate_op(FILE *output, char op, llvm_index operand1, llvm_index operand2);
void llvm_generate_result(FILE *output, llvm_index result);
void generateLLVMCode(FILE *output, ASTNodeEntry *node);

struct sASTNode* createNode(char op, int num, struct sASTNode* left, struct sASTNode* right);
