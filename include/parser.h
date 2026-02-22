#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "lexer.h"


enum TokenCode {
    token_id = 0,
    token_plus = 1,
    token_minus = 2,
    token_mul = 3,
    token_div = 4,
    token_lparen = 5,
    token_rparen = 6,
    token_eof = 7
};


enum NonTerminal {
    NonExpr = 0,
    NonTerm = 1,
    NonFact = 2
};


struct GrammarRule {
    std::string leftSide;   
    int rightSideLength;
    std::string rightSide;    
};

bool syntaxAnalysis(const std::vector<Token>& inputTokens);

int getTokenCode(const std::string& type);

#endif