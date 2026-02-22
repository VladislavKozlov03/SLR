#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "tests.h"


extern FILE *yyin;

void printTable(const std::string& title, const std::vector<std::string>& stacks, 
                const std::vector<std::string>& inputs, const std::vector<std::string>& actions, 
                bool actualResult, bool expectedPass) 
{
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout <<  title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\n";
    std::cout << "+" << std::string(12, '-') << "+" << std::string(15, '-') << "+" << std::string(25, '-') << "+\n";
    std::cout << "| " << std::left << std::setw(10) << "STACK" << " | "
         << std::setw(13) << "INPUT" << " | "
         << "+" << std::string(12, '-') << "+" << std::string(15, '-') << "+" << std::string(25, '-') << "+\n";
    
    for (size_t i = 0; i < stacks.size(); i++) {
        std::cout << "| " << std::left << std::setw(10) << stacks[i] << " | "
             << std::setw(13) << inputs[i] << " | "
             << std::setw(23) << actions[i] << " |\n";
    }
    
    std::cout << "+" << std::string(12, '-') << "+" << std::string(15, '-') << "+" << std::string(25, '-') << "+\n";
    std::cout << "--- Результат: " << (actualResult ? "Успех" : "Ошибка") 
         << " (ожидался: " << (expectedPass ? "успех" : "ошибка") << ") ---\n";
}

int main() 
{
    std::cout << "\n" << std::string(60, '#') << std::endl;
    std::cout << "#          Запуск тестов         #" << std::endl;
    std::cout << std::string(60, '#') << std::endl;
    
    int passed = 0;
    
    for (const auto& test : TESTS)
    {
        std::string filename = "temp_test_input.txt";
        FILE *file = fopen(filename.c_str(), "w");
        fprintf(file, "%s", test.input.c_str());
        fclose(file);
        
        file = fopen(filename.c_str(), "r");
        yyin = file;
        
        clear_tokens();
        yylex();
        const std::vector<Token>& lexTokens = get_tokens();
        
        bool result = syntaxAnalysis(lexTokens);
        
        printTable(test.name, test.expectedStack, test.expectedInput, 
                   test.expectedAction, result, test.shouldPass);
        
        if (result == test.shouldPass)
        {
            std::cout << "Тест пройден\n";
            passed++;
        }
        else
        {
            std::cout << "Тетс не пройден\n";
        }
        
        fclose(file);
        remove(filename.c_str());
    }
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Пройдено: " << passed << "/" << TESTS.size() << std::endl;
    std::cout << "Не пройдено: " << (TESTS.size() - passed) << "/" << TESTS.size() << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return (passed == TESTS.size()) ? 0 : 1;
}