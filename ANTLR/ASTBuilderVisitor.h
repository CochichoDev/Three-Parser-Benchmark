#pragma once

#include "code_generator.h"
#include "ANTLRGrammarBaseVisitor.h" // Adjust this according to your ANTLR generated files
#include "ANTLRGrammarParser.h"
#include <stack>


using namespace antlr4;

class ASTBuilderVisitor : public ANTLRGrammarBaseVisitor {
public:
    antlrcpp::Any visitExpression(ANTLRGrammarParser::ExpressionContext *ctx) override;
    antlrcpp::Any visitTerm(ANTLRGrammarParser::TermContext *ctx) override;
    antlrcpp::Any visitFactor(ANTLRGrammarParser::FactorContext *ctx) override;
};
