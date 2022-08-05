#include "stack_segment.hpp"
#include <stdexcept>

StackSegment::StackSegment(std::string _name, int _begin, int _end){
    name = _name;
    begin = _begin;
    end = _end;
}

std::vector<std::string> StackSegment::pop_value(int value) {
    if (value == -1){
        // subtracts ptr, returns seg[ptr] in D 
        std::vector<std::string> ret;
        ret.push_back("@SP");
        ret.push_back("M=M-1");
        ret.push_back("A=M"); // following pointer; don't combine instrs
        ret.push_back("D=M");
        return ret;
    }
    else if (value == 1){
        // subtracts ptr, returns seg[ptr] in A. Used for a lot of things actually
        std::vector<std::string> ret;
        ret.push_back("@SP");
        ret.push_back("M=M-1");
        ret.push_back("A=M"); // following pointer; don't combine instrs
        ret.push_back("A=M"); // saves to A
        return ret;
    }
    else throw std::invalid_argument("Stack pop value with unique code " + std::to_string(value) + " not implemented yet");
} 
std::vector<std::string> StackSegment::push_value(int value) {
    if (value == -1){
        // returns seg[ptr] in D, increments ptr afterwards as well
        std::vector<std::string> ret;
        ret.push_back("@SP");
        ret.push_back("A=M"); // following pointer; don't combine instrs
        ret.push_back("M=D");
        ret.push_back("@SP");
        ret.push_back("M=M+1");
        return ret;
    }
    else throw std::invalid_argument("Stack push value with unique code " + std::to_string(value) + " not implemented yet");
} 