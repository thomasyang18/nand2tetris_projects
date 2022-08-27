#include "program.hpp"
#include <iostream>

std::unique_ptr<Node> parseClass(){
    std::unique_ptr<Node> res(new Node("class"));

    res->children.push_back(force_next_token(keyword, "class"));
    
    res->children.push_back(parseClassName());

    res->children.push_back(force_next_token(symbol, "{"));

    while (try_match_token(keyword, "static") || try_match_token(keyword, "field")) res->children.push_back(parseClassVarDec());
    while (try_match_token(keyword, "constructor") || try_match_token(keyword, "function") || 
                        try_match_token(keyword, "method")) 
            res->children.push_back(parseSubroutineDec());

    res->children.push_back(force_next_token(symbol, "}"));

    return res;    
}