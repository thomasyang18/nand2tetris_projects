#ifndef _TOKENIZER_HPP_
#define _TOKENIZER_HPP_

#include <string>
#include <vector>
#include "tokens/token.hpp"

class JackTokenizer{
    std::vector<Token> tokens;
public:
    size_t pos = 0;
    void advance(); 
    Token get_cur_token(); // Does not advance
    Token get_ahead_token(); // because this is LL(2)
    bool has_more_tokens();
    JackTokenizer(std::string _filename = "");
};

#endif