#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <string>

enum TokenType{
    keyword,
    symbol,
    integerConstant,
    stringConstant,
    identifier,
    none
};

class Token
{
public:
    std::string value;
    TokenType type;
    Token(std::string _value, TokenType type);
};

#endif