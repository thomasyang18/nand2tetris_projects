#ifndef _TOKENIZER_HPP_
#define _TOKENIZER_HPP_

#include <string>
#include <vector>
#include "tokens/token.hpp"

class JackTokenizer{
    size_t pos;
    std::vector<Token> tokens;
public:
    void advance(); 
    Token get_cur_token(); // Does not advance
    bool has_more_tokens();
    JackTokenizer(std::string _filename);
};

#endif