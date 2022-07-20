#include "instr.hpp"
#include <stdexcept>


StackOperation::StackOperation(std::string _push, std::string _type, std::string _val){
    type = _type;
    if (_push != "push" and _push != "pop") throw std::invalid_argument("Second argument was not push or pop");
    else push = _push;
    val = atoi(_val.c_str());
}

std::vector<std::string> StackOperation::toString(){
    return {type, push, std::to_string(val)};    
}

BinaryOp::BinaryOp(std::string _opName){
    opName = _opName;
}

std::vector<std::string> BinaryOp::toString(){
    return {opName};
}

UnaryOp::UnaryOp(std::string _opName){
    opName = _opName;
}

std::vector<std::string> UnaryOp::toString(){
    return {opName};
}