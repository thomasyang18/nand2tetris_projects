#include "memory_segment.hpp"

MemorySegment::MemorySegment(){}

MemorySegment::MemorySegment(std::string _name, std::string _hack_name){
    name = _name;
    hack_name=_hack_name;
}

std::vector<std::string> MemorySegment::pop_value(int value){ 
    // pop off D, the stack var, into seg[location+value]
    // however, not enough registers, so will pop the index into D, then pop into A, then swap with A later
    std::vector<std::string> ret;
    ret.push_back("@" + hack_name); 
    ret.push_back("D=M");
    ret.push_back("@" + std::to_string(value));
    ret.push_back("D=D+A");
    return ret;
}  

std::vector<std::string> MemorySegment::push_value(int value){
    // pushes seg[location+value] to stack, so store result in D
    std::vector<std::string> ret;
    ret.push_back("@" + hack_name); 
    ret.push_back("D=M");
    ret.push_back("@" + std::to_string(value));
    ret.push_back("A=D+A");
    ret.push_back("D=M");

    return ret;
}