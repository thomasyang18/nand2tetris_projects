#include "jump_instrs.hpp"

// Label Operation

std::shared_ptr<LabelOp> LabelOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    if (pos + 2 > tokens.size()) return nullptr;
    std::string type = tokens[pos];
    std::string _name = tokens[pos+1];
    if (type != "label") return nullptr;
    std::shared_ptr<LabelOp> ret(new LabelOp());
    ret->name = _name;
    pos+=2;
    return ret;
}

std::vector<std::string> LabelOp::toString(){
    return {"label", name};
}

// Goto Operation

std::shared_ptr<GotoOp> GotoOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    if (pos + 2 > tokens.size()) return nullptr;
    std::string type = tokens[pos];
    std::string _name = tokens[pos+1];
    if (type != "goto") return nullptr;
    std::shared_ptr<GotoOp> ret(new GotoOp());
    ret->name = _name;
    pos+=2;
    return ret;
}

std::vector<std::string> GotoOp::toString(){
    return {"goto", name};
}

// IfGoto Operation

std::shared_ptr<IfGotoOp> IfGotoOp::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    if (pos + 2 > tokens.size()) return nullptr;
    std::string type = tokens[pos];
    std::string _name = tokens[pos+1];
    if (type != "if-goto") return nullptr;
    std::shared_ptr<IfGotoOp> ret(new IfGotoOp());
    ret->name = _name;
    pos+=2;
    return ret;
}

std::vector<std::string> IfGotoOp::toString(){
    return {"if-goto", name};
}

