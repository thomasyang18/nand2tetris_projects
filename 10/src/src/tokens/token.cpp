#include "token.hpp"

Token::Token(std::string _value, TokenType _type){
    type = _type;
    value = _value;
}