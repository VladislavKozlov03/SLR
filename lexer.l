%{
#include "lexer.h"
#include <iostream>


std::vector<Token> tokens;

void add_token(const char* type) 
{
    Token t;
    t.type = type;
    t.value = yytext;
    t.line = yylineno;
    tokens.push_back(t);
    std::cout << "<" << type << ", " << yytext << ">" << std::endl;
}

const std::vector<Token>& get_tokens() 
{ 
    return tokens; 
}

void clear_tokens() 
{ 
    tokens.clear(); 
}
%}

%option noyywrap
%option yylineno
%option outfile="lexer.c"

digit           [0-9]
letter          [a-zA-Z]
identifier      {letter}({letter}|{digit})*
integer         {digit}+
string          \"[^\"]*\"
whitespace      [ \t]+

%%

{whitespace}    { }
\n              { }

"if"            { add_token("if"); }
"else"          { add_token("else"); }
"while"         { add_token("while"); }
"return"        { add_token("return"); }
"int"           { add_token("int"); }
"float"         { add_token("float"); }
"void"          { add_token("void"); }

{identifier}    { add_token("id"); }
{integer}       { add_token("int_number"); }
{string}        { add_token("string"); }

"+="            { add_token("assign_add"); }
"-="            { add_token("assign_sub"); }
"*="            { add_token("assign_mul"); }
"/="            { add_token("assign_div"); }
"="             { add_token("assign"); }

"+"             { add_token("add"); }
"-"             { add_token("sub"); }
"*"             { add_token("mul"); }
"/"             { add_token("div"); }

"=="            { add_token("equal"); }
"!="            { add_token("not_equal"); }
"<"             { add_token("less"); }
">"             { add_token("greater"); }
"<="            { add_token("less_equal"); }
">="            { add_token("greater_equal"); }

";"             { add_token("semicolon"); }
","             { add_token("comma"); }
"("             { add_token("lparen"); }
")"             { add_token("rparen"); }
"{"             { add_token("lbrace"); }
"}"             { add_token("rbrace"); }

"//".*          { }

.               { std::cout << "Неизвестный символ: " << yytext[0] << std::endl; }

%%