#include "expr_node.hpp"

Node::Node(std::string _type){
    type = _type;
    tok = Token{"",none};
}

Node::Node(Token _tok){
    tok = _tok;
    type = "";
}

int parse_depth = -1;

std::string Node::print(){
    parse_depth++;
    std::string res;

    if (tok.type == none){
        for (int i = 0 ; i <parse_depth; i++) res += "\t";
        res = res + "<" + type + ">\n";
    }
    else {
                for (int i = 0 ; i <parse_depth; i++) res += "\t";

        res += tok.to_xml();
        res += "\n";
    }

    for (auto &x: children) x->print();

    if (tok.type == none){
        for (int i = 0 ; i <parse_depth; i++) res += "\t";
        res = res + "<" + type + ">\n";
    }
    else {
                for (int i = 0 ; i <parse_depth; i++) res += "\t";

        res += tok.to_xml();
        res += "\n";
    }


    parse_depth--;

    return res;
}