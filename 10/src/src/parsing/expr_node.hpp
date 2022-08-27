#ifndef _EXPR_NODE_HPP_
#define _EXPR_NODE_HPP_

#include <string>
#include <memory>
#include <vector>
#include "../tokenizer.hpp"

class Node
{   
    std::string type;
    Token tok;
public:
    std::vector<std::unique_ptr<Node>> children; 
    std::string print();
    std::string compile();
    Node(std::string _type);
    Node(Token _tok);
};

#endif