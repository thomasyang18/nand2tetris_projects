#include "token.hpp"
#include <stdexcept>

Token::Token(std::string _value, TokenType _type){
    type = _type;
    value = _value;
}

std::string Token::to_xml(){
    switch (type){
        case none:
            throw std::invalid_argument("Token had no type");
        case keyword:
            return "<keyword> " + value + " </keyword>";
            break;
        case identifier:
            return "<identifier> " + value + " </identifier>";
            break;
        case integerConstant:
            return "<integerConstant> " + value + " </integerConstant>";
            break;
        case stringConstant:
            return "<stringConstant> " + value + " </stringConstant>";
            break;
        case symbol:
            std::string temp = value;
            if (temp == "<") temp = "&lt;";
            if (temp == ">") temp = "&gt;";
            if (temp == "&") temp = "&amp;";
            return "<symbol> " + temp + " </symbol>";
            break;
    }
    // impossible
    return "";
}