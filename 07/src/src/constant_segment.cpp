#include "constant_segment.hpp"
#include <stdexcept>

ConstantSegment::ConstantSegment(std::string _name, int _location, int _begin, int _end){
    name = _name; // nothing else matters
}

std::vector<std::string> ConstantSegment::pop_value(int value){
    throw std::invalid_argument("Cannot pop value to Constant Segment");
} 


std::vector<std::string> ConstantSegment::push_value(int value) {
    // just returns value in D
    std::vector<std::string> res;
    res.push_back("@" + std::to_string(value));
    res.push_back("D=A");
    return res;
}