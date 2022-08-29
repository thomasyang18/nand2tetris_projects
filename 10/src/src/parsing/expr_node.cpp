#include "expr_node.hpp"
#include "parser.hpp"

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
        for (int i = 0 ; i <parse_depth; i++) res += "  ";

    if (tok.type == none){
        res = res + "<" + type + ">\n";
    }
    else {

        res += tok.to_xml();
        res += "\n";
    }
    parse_ofile << res;

    for (auto &x: children) x->print();

    res = "";
            for (int i = 0 ; i <parse_depth; i++) res += "  ";

    if (tok.type == none){
        res = res + "</" + type + ">\n";
    }
    else {

        res += tok.to_xml();
        res += "\n";
    }

    parse_ofile << res;

    parse_depth--;

    return res;
}