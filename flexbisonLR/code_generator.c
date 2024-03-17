#include <stdio.h>
#include <stdlib.h>
#include "code_generator.h"

llvm_index llvm_value_index;

// LLVM IR generation function for addition operation
llvm_index llvm_generate_add(FILE *output, llvm_index operand1, llvm_index operand2) {
    llvm_index result = ++llvm_value_index;
    fprintf(output, "%%%d = add i32 %%%d, %%%d\n", result, operand1, operand2);
    return result;
}

// LLVM IR generation function for subtraction operation
llvm_index llvm_generate_sub(FILE *output, llvm_index operand1, llvm_index operand2) {
    llvm_index result = ++llvm_value_index;
    fprintf(output, "%%%d = sub i32 %%%d, %%%d\n", result, operand1, operand2);
    return result;
}

llvm_index llvm_generate_mul(FILE *output, llvm_index operand1, llvm_index operand2) {
    llvm_index result = ++llvm_value_index;
    fprintf(output, "%%%d = mul i32 %%%d, %%%d\n", result, operand1, operand2);
    return result;
}

llvm_index llvm_generate_div(FILE *output, llvm_index operand1, llvm_index operand2) {
    llvm_index result = ++llvm_value_index;
    fprintf(output, "%%%d = sdiv i32 %%%d, %%%d\n", result, operand1, operand2);
    return result;
}

llvm_index llvm_make_value(FILE *output, int value) {
    fprintf(output, "%%%d = add i32 0, %d\n", ++llvm_value_index, value);
    return llvm_value_index;
}


void generateLLVMNodeCode(FILE *output, ASTNode *node) {
    if (node != NULL) {
        llvm_index leftIndex, rightIndex, resultIndex;

        // Generate LLVM IR code for left and right subtrees
        if (node->left != NULL) {
            generateLLVMNodeCode(output, node->left);
            leftIndex = llvm_value_index;
        }
        if (node->right != NULL) {
            generateLLVMNodeCode(output, node->right);
            rightIndex = llvm_value_index;
        }

        // Generate LLVM IR code for current node
        switch (node->op) {
            case '+':
                resultIndex = llvm_generate_add(output, leftIndex, rightIndex);
                break;
            case '-':
                resultIndex = llvm_generate_sub(output, leftIndex, rightIndex);
                break;
            case '*':
                resultIndex = llvm_generate_mul(output, leftIndex, rightIndex);
                break;
            case '/':
                resultIndex = llvm_generate_div(output, leftIndex, rightIndex);
                break;
            case '\0':
                resultIndex = llvm_make_value(output, node->num);
                break;
            // Add cases for other operations
            default:
                fprintf(stderr, "Unsupported operation: %c, Value: %d\n", node->op, node->num);
                exit(1);
        }

        // Store the result index in the current node
        node->num = resultIndex;
    }

}


void generateLLVMCode(FILE *output, ASTNode *node) {
    generateLLVMNodeCode(output, node);
    fprintf(output, "ret i32 %%%d\n", node->num);
}

struct sASTNode* createNode(char op, int num, struct sASTNode* left, struct sASTNode* right) {
    struct sASTNode* node = (struct sASTNode*)malloc(sizeof(struct sASTNode));
    node->op = op;
    node->num = num;
    node->left = left;
    node->right = right;

    return node;
}
