#ifndef _LEXER_HPP_
#define _LEXER_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Lexer
{
public:
    std::vector<std::string> tokens;
    Lexer();
    void lex(std::ifstream& myfile);
};

#endif