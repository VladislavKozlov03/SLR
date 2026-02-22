#include <iostream>
#include <stack>
#include <string>
#include "parser.h"


const int ACTION_TABLE[16][8] = {
    /* 0 */  { 5, -99, -99, -99, -99,  4, -99, -99},
    /* 1 */  {-99,  6,  7, -99, -99, -99, -99,  0},
    /* 2 */  {-3, -3, -3,  8,  9, -3, -3, -3},
    /* 3 */  {-6, -6, -6, -6, -6, -6, -6, -6},
    /* 4 */  { 5, -99, -99, -99, -99,  4, -99, -99},
    /* 5 */  {-7, -7, -7, -7, -7, -7, -7, -7},
    /* 6 */  { 5, -99, -99, -99, -99,  4, -99, -99},
    /* 7 */  { 5, -99, -99, -99, -99,  4, -99, -99},
    /* 8 */  { 5, -99, -99, -99, -99,  4, -99, -99},
    /* 9 */  { 5, -99, -99, -99, -99,  4, -99, -99},
    /* 10 */ {-99,  6,  7, -99, -99, -99, 15, -99},
    /* 11 */ {-99, -1, -1,  8,  9, -99, -1, -1}, 
    /* 12 */ {-99, -2, -2,  8,  9, -99, -2, -2},  
    /* 13 */ {-4, -4, -4, -4, -4, -4, -4, -4},
    /* 14 */ {-5, -5, -5, -5, -5, -5, -5, -5},
    /* 15 */ {-8, -8, -8, -8, -8, -8, -8, -8}
};

const int GOTO_TABLE[16][3] = {
    /* 0 */  { 1,  2,  3},
    /* 1 */  {-1, -1, -1},
    /* 2 */  {-1, -1, -1},
    /* 3 */  {-1, -1, -1},
    /* 4 */  {10,  2,  3},
    /* 5 */  {-1, -1, -1},
    /* 6 */  {-1, 11,  3},
    /* 7 */  {-1, 12,  3},
    /* 8 */  {-1, -1, 13},
    /* 9 */  {-1, -1, 14},
    /* 10 */ {-1, -1, -1},
    /* 11 */ {-1, -1, -1},
    /* 12 */ {-1, -1, -1},
    /* 13 */ {-1, -1, -1},
    /* 14 */ {-1, -1, -1},
    /* 15 */ {-1, -1, -1}
};

const GrammarRule RULES[] = {
    {"E'", 1, "E"},      // правило 0: Расширенная грамматика:
    {"E", 3, "E+T"},     // правило 1: E → E + T
    {"E", 3, "E-T"},     // правило 2: E → E - T
    {"E", 1, "T"},       // правило 3: E → T
    {"T", 3, "T*F"},     // правило 4: T → T * F
    {"T", 3, "T/F"},     // правило 5: T → T / F
    {"T", 1, "F"},       // правило 6: T → F
    {"F", 1, "id"},      // правило 7: F → id
    {"F", 3, "(E)"}      // правило 8: F → ( E )
};

int getTokenCode(const std::string& type)
{
    if (type == "id") return token_id;
    if (type == "add") return token_plus;
    if (type == "sub") return token_minus;
    if (type == "mul") return token_mul;
    if (type == "div") return token_div;
    if (type == "lparen") return token_lparen;
    if (type == "rparen") return token_rparen;
    return -1;
}

bool syntaxAnalysis(const std::vector<Token>& inputTokens) 
{
    std::stack<int> stateStack;
    stateStack.push(0);
    
    int currentPos = 0;
    int step = 0;
    
    std::cout << "\nСинтаксический анализ:\n";
    
    while (true) 
    {
        step++;
        int currentState = stateStack.top();
        
        int tokenCode;
        if (currentPos < inputTokens.size()) 
        {
            tokenCode = getTokenCode(inputTokens[currentPos].type);
        } 
        else 
        {
            tokenCode = token_eof;
        }
        
        if (tokenCode == -1) 
        {
            std::cout << "Erorr: неизвестный токен\n";
            return false;
        }
        
        int action = ACTION_TABLE[currentState][tokenCode];
        
        std::cout << "Шаг " << step << ": состояние=" << currentState;
        
        if (action > 0) 
        {
            std::cout << " SHIFT -> " << action << "\n";
            stateStack.push(action);
            currentPos++;
        }
        else if (action == 0) 
        {
            std::cout << " Accept\n";
            return true;
        }
        else if (action == -99) 
        {
            std::cout << " Erorr\n";
            return false;
        }
        else 
        { 
            int ruleNum = -action;
            std::cout << " REDUCE по правилу " << ruleNum << "\n";
            
            for (int i = 0; i < RULES[ruleNum].rightSideLength; i++) 
            {
                stateStack.pop();
            }
            
            int prevState = stateStack.top();
            NonTerminal nonterm;
            if (RULES[ruleNum].leftSide == "E") 
            {
                nonterm = NonExpr;
            }
            else if (RULES[ruleNum].leftSide == "T") 
            {
                nonterm = NonTerm;
            }
            else 
            {
                nonterm = NonFact;
            }
            int gotoState = GOTO_TABLE[prevState][nonterm];
            if (gotoState == -1) 
            {
                std::cout << "Erorr: нет GOTO состояния\n";
                return false;
            }
            
            stateStack.push(gotoState);
        }
    }
}