#include "jump_instrs.hpp"

// Label Operation

LabelOp::LabelOp(std::string _name){
    name = _name;
}

std::vector<std::string> LabelOp::toString(){
    return {name};
}

// Goto Operation

GotoOp::GotoOp(std::string _name){
    name = _name;
}

std::vector<std::string> GotoOp::toString(){
    return {name};
}

// IfGoto Operation

IfGotoOp::IfGotoOp(std::string _name){
    name = _name;
}

std::vector<std::string> IfGotoOp::toString(){
    return {name};
}

