#ifndef _EXPR_NODE_HPP_
#define _EXPR_NODE_HPP_

#include <string>
#include <memory>
#include <vector>

class Node
{   
    std::string type;
    std::vector<std::unique_ptr<Node>> children; 
public:
    std::string print();
    std::string compile();
    Node(std::string _type);
};

#include "parser.hpp"

#endif