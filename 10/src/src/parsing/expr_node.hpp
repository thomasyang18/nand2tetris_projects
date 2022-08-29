#ifndef _EXPR_NODE_HPP_
#define _EXPR_NODE_HPP_

#include <string>
#include <memory>
#include <vector>
#include "../tokenizer.hpp"

class Node
{   
public:
    std::string type;
    Token tok;
    std::vector<std::unique_ptr<Node>> children; 
    void print();
    void compile();
    Node(std::string _type);
    Node(Token _tok);
};

#endif