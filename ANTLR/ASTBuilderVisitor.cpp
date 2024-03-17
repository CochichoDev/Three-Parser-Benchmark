#include "ANTLRGrammarLexer.h"
#include "ANTLRGrammarParser.h"
#include "code_generator.h"
#include "ANTLRGrammarBaseVisitor.h"
#include "ASTBuilderVisitor.h"


#include "ASTBuilderVisitor.h"
#include <iostream>

antlrcpp::Any ASTBuilderVisitor::visitExpression(ANTLRGrammarParser::ExpressionContext *ctx) {
    auto leftTerm = std::any_cast<ASTNodeEntry*>(visit(ctx->term(0))); // Visit the left term
    for (size_t i = 1; i < ctx->term().size(); ++i) {
        auto op = ctx->children.at(2 * i - 1)->getText(); // Get the operator
        auto rightTerm = std::any_cast<ASTNodeEntry*>(visit(ctx->term(i))); // Visit the right term

        // Create a binary operator node
        ASTNodeEntry *newNode = createNode(op[0], 0, leftTerm, rightTerm);

        leftTerm = newNode; // Update the left term
    }
    return leftTerm; // Return the root node of the expression
}

antlrcpp::Any ASTBuilderVisitor::visitTerm(ANTLRGrammarParser::TermContext *ctx) {
    auto leftFactor = std::any_cast<ASTNodeEntry*>(visit(ctx->factor(0))); // Visit the left term
    for (size_t i = 1; i < ctx->factor().size(); ++i) {
        auto op = ctx->children.at(2 * i - 1)->getText(); // Get the operator
        auto rightFactor = std::any_cast<ASTNodeEntry*>(visit(ctx->factor(i))); // Visit the right term

        // Create a binary operator node
        ASTNodeEntry* newNode = createNode(op[0], 0, leftFactor, rightFactor);

        leftFactor = newNode; // Update the left factor
    }
    return leftFactor; // Return the root node of the term
}

antlrcpp::Any ASTBuilderVisitor::visitFactor(ANTLRGrammarParser::FactorContext *ctx) {
    if (ctx->digit() != nullptr) {
        int value = std::stoi(ctx->digit()->getText()); // Get the value of the digit
        return createNode('\0', value, NULL, NULL); // Return a number node
    } else { // Case of nested expression
        return visit(ctx->expression()); // Visit the nested expression
    }
}
