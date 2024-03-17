all: ANTLR

ANTLR: main.cpp ANTLRGrammarLexer.cpp ANTLRGrammarParser.cpp code_generator.cpp ASTBuilderVisitor.cpp ANTLRGrammarBaseListener.cpp
	g++ -std=c++17 -o main main.cpp code_generator.cpp ANTLRGrammarLexer.cpp ANTLRGrammarParser.cpp ASTBuilderVisitor.cpp  ANTLRGrammarBaseListener.cpp -I/usr/include/antlr4-runtime -L/usr/include/antlr4-runtime -lantlr4-runtime

ANTLRGrammarLexer.cpp ANTLRGrammarParser.cpp: ANTLRGrammar.g
	antlr4 -Dlanguage=Cpp -visitor ANTLRGrammar.g

clean:
	rm ANTLRGrammarLexer* ANTLRGrammarParser* main ANTLRGrammarBase* ANTLRGrammar.interp ANTLRGrammar.tokens ANTLRGrammarListener*
