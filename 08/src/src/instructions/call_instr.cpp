#include "call_instr.hpp"

std::vector<std::string> CallOp::toString(){
    return {"call", name, std::to_string(n_args)};
}

std::shared_ptr<CallOp> CallOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    // must be 3, even if n_args = 0
    if (pos + 3 > tokens.size()) return nullptr;
    std::string _call = tokens[pos];
    std::string _name = tokens[pos+1];
    int _n_args = atoi(tokens[pos+2].c_str());
    if (_call != "call") return nullptr;
    if (_n_args < 0) return nullptr;
    pos+=3;
    std::shared_ptr<CallOp> ret(new CallOp());
    ret->n_args = (unsigned int)_n_args;
    ret->name = _name;

    return ret;
}