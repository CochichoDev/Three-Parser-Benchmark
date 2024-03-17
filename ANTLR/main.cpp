#include "ANTLRGrammarLexer.h"
#include "ANTLRGrammarParser.h"
#include "antlr4-runtime.h"
#include <fstream>
#include <iostream>
#include "code_generator.h"
#include "ASTBuilderVisitor.h"

extern FILE* yyin;

using namespace antlr4;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        exit(1);
    }


    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        fprintf(stderr, "Error: Couldn't open input file %s\n", argv[1]);
        exit(1);
    }

    ANTLRInputStream input(inputFile);
    ANTLRGrammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    ANTLRGrammarParser parser(&tokens);
    ANTLRGrammarParser::ExpressionContext *expressionContext = parser.expression();

    ASTBuilderVisitor astBuilder;
    ASTNodeEntry *root = std::any_cast<ASTNodeEntry*>(astBuilder.visit(expressionContext));
    if (root != nullptr) {
        generateLLVMCode(stdout, root);
        delete root; // Remember to free memory allocated for AST nodes
    }

    inputFile.close();

	return 0;
}
