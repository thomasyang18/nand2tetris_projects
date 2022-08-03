#include "stack_segment.hpp"
#include <stdexcept>

StackSegment::StackSegment(std::string _name, int _location, int _begin, int _end){
    name = _name;
    location = _location;
    begin = stack_ptr = _begin;
    end = _end;
}

std::vector<std::string> StackSegment::pop_value(int value) {
    if (value == -1){
        // subtracts ptr, returns seg[ptr] in D 
        std::vector<std::string> ret;
        ret.push_back("@" + std::to_string(location));
        ret.push_back("M=M-1");
        ret.push_back("A=M"); // following pointer; don't combine instrs
        ret.push_back("D=M");
        stack_ptr--;
        return ret;
    }
    else if (value == 1){
        // subtracts ptr, returns seg[ptr] in A. Used for a lot of things actually
        std::vector<std::string> ret;
        ret.push_back("@" + std::to_string(location));
        ret.push_back("M=M-1");
        ret.push_back("A=M"); // following pointer; don't combine instrs
        ret.push_back("A=M"); // saves to A
        stack_ptr--;
        return ret;
    }
    else throw std::invalid_argument("Stack pop value with unique code " + std::to_string(value) + " not implemented yet");
} 
std::vector<std::string> StackSegment::push_value(int value) {
    if (value == -1){
        // returns seg[ptr] in D, increments ptr afterwards as well
        std::vector<std::string> ret;
        ret.push_back("@" + std::to_string(location));
        ret.push_back("A=M"); // following pointer; don't combine instrs
        ret.push_back("M=D");
        ret.push_back("@" + std::to_string(location));
        ret.push_back("M=M+1");
        stack_ptr++;
        return ret;
    }
    else throw std::invalid_argument("Stack push value with unique code " + std::to_string(value) + " not implemented yet");
} 