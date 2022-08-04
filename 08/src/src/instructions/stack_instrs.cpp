#include "stack_instrs.hpp"
#include <algorithm>
// Stack Operation

std::shared_ptr<StackOperation> StackOperation::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    if (pos + 3 > tokens.size()) return nullptr;
    std::string _push = tokens[pos];
    std::string _type = tokens[pos+1];
    std::string _val = tokens[pos+2];
    if (_push != "push" && _push != "pop") return nullptr;
    pos+=3;
    std::shared_ptr<StackOperation> ret(new StackOperation());
    ret->push = _push;
    ret->type = _type;
    ret->val = atoi(_val.c_str());
    return ret;  
}

std::vector<std::string> StackOperation::toString(){
    return {push, type, std::to_string(val)};    
}

// Binary op
std::vector<std::string> binKeywords = {"add", "sub", "eq", "gt", "lt", "and", "or"};

std::shared_ptr<BinaryOp> BinaryOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    if (pos + 1 > tokens.size()) return nullptr;
    std::string _opName = tokens[pos];
    if (std::find(binKeywords.begin(), binKeywords.end(), _opName) != std::end(binKeywords)) {
        pos++;
        std::shared_ptr<BinaryOp> ret(new BinaryOp());
        ret->opName = _opName;
        return ret;
    }
    return nullptr;
}

std::vector<std::string> BinaryOp::toString(){
    return {opName};
}

// Unary Op
std::vector<std::string> unaryKeywords = {"neg", "not"};

std::shared_ptr<UnaryOp> UnaryOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    if (pos + 1 > tokens.size()) return nullptr;
    std::string _opName = tokens[pos];
    if (std::find(unaryKeywords.begin(), unaryKeywords.end(), _opName) != std::end(unaryKeywords)) {
        pos++;
        std::shared_ptr<UnaryOp> ret(new UnaryOp());
        ret->opName = _opName;
        return ret;
    }
    return nullptr;
}


std::vector<std::string> UnaryOp::toString(){
    return {opName};
}
