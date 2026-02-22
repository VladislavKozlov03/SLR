#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

struct Token {
    std::string type;
    std::string value;
    int line;
};

void add_token(const char *type);
const std::vector<Token>& get_tokens();
void clear_tokens();

int yylex();

#endif