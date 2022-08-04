#include "baseless_segment.hpp"

BaselessSegment::BaselessSegment(std::string _name, int _begin, int _end){
    name = _name;
    begin = _begin; // begin presumed to be base
    end = _end;
}

std::vector<std::string> BaselessSegment::pop_value(int value){ 
    // pop off D, the stack var, into seg[base+value]
    // however, not enough registers, so will pop the index into D, then pop into A, then swap with A later
    std::vector<std::string> ret;
    ret.push_back("@" + std::to_string(begin)); 
    ret.push_back("D=A");
    ret.push_back("@" + std::to_string(value));
    ret.push_back("D=D+A");
    return ret;
}  

std::vector<std::string> BaselessSegment::push_value(int value){
    // pushes seg[base+value] to stack, so store result in D
    std::vector<std::string> ret;
    ret.push_back("@" + std::to_string(begin)); 
    ret.push_back("D=A");
    ret.push_back("@" + std::to_string(value));
    ret.push_back("A=D+A");
    ret.push_back("D=M");

    return ret;
}