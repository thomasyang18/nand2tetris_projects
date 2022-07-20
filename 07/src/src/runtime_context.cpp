#include "runtime_context.hpp"
#include "constant_segment.hpp"
#include "static_segment.hpp"
#include "stack_segment.hpp"
#include <stdexcept>

RuntimeContext::RuntimeContext(){
    add_segment(StackSegment("stack", 0, 256, 2047));
    add_segment(MemorySegment("local", 0, 0,0));
    add_segment(MemorySegment("arg", 0, 0, 0));
    add_segment(MemorySegment("this", 0, 0, 0));
    add_segment(MemorySegment("that", 0, 0, 0));
    add_segment(ConstantSegment("constant", -1, -1,-1));
    add_segment(StaticSegment("static", 0, 16,255));
    add_segment(MemorySegment("pointer", 0, 0,0));
    add_segment(MemorySegment("temp", 0, 0,0));
}

void RuntimeContext::add_segment(MemorySegment segment){
    name2seg[segment.name] = segment;
}

std::string to_comment(std::shared_ptr<Instr> instr){
    std::string res = "//";
    for (auto x: instr->toString()) {
        res += " ";
        res += x;
    } 
    return res;
}

std::vector<std::string> RuntimeContext::do_instr(std::shared_ptr<Instr> instr){
    
    std::vector<std::string> ret;
    if (auto op = std::dynamic_pointer_cast<StackOperation>(instr)){

    }
    else if (auto op = std::dynamic_pointer_cast<BinaryOp>(instr)){

    }
    else if (auto op = std::dynamic_pointer_cast<UnaryOp>(instr)){
        
    }
    else{
        throw std::invalid_argument("Instruction not implemented");
    }
    
    return ret;
}

