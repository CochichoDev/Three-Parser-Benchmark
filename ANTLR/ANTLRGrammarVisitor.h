
// Generated from ANTLRGrammar.g by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "ANTLRGrammarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ANTLRGrammarParser.
 */
class  ANTLRGrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ANTLRGrammarParser.
   */
    virtual std::any visitExpression(ANTLRGrammarParser::ExpressionContext *context) = 0;

    virtual std::any visitTerm(ANTLRGrammarParser::TermContext *context) = 0;

    virtual std::any visitFactor(ANTLRGrammarParser::FactorContext *context) = 0;

    virtual std::any visitDigit(ANTLRGrammarParser::DigitContext *context) = 0;


};

