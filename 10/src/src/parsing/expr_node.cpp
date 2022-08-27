#include "expr_node.hpp"

Node::Node(std::string _type){
    type = _type;
}

std::string Node::print(){
    std::string res;
    for (int i = 0 ; i <parse_depth; i++) res += "\t";
    res = res + "<" + type + ">\n";

    for (auto &x: children) x->print();

    for (int i = 0 ; i <parse_depth; i++) res += "\t";
    res = res + "<" + type + ">\n";
}