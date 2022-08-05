#include "func_instr.hpp"
#include <iostream>

std::vector<std::string> FuncOp::toString(){
    return {"function", name, std::to_string(n_vars)};
}

std::shared_ptr<FuncOp> FuncOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    // must be 3, even if n_vars = 0
    if (pos + 3 > tokens.size()) return nullptr;
    std::string _function = tokens[pos];
    std::string _name = tokens[pos+1];
    int _n_vars = atoi(tokens[pos+2].c_str());

    if (_function != "function") return nullptr;
    if (_n_vars < 0) return nullptr;
    pos+=3;
    std::shared_ptr<FuncOp> ret(new FuncOp());
    ret->n_vars = (unsigned int)_n_vars;
    ret->name = _name;

    return ret;
}

std::vector<std::string> ReturnOp::toString(){
    return {"return"};
}

std::shared_ptr<ReturnOp> ReturnOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    if (pos + 1 > tokens.size()) return nullptr;
    std::string _return = tokens[pos];
    if (_return == "return"){
        pos++;
        return std::shared_ptr<ReturnOp>(new ReturnOp());
    }
    return nullptr;
}