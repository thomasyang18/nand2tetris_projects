#include "memory_segment.hpp"

MemorySegment::MemorySegment(){}

MemorySegment::MemorySegment(std::string _name, int _location, int _begin, int _end){
    name = _name;
    location = _location;
    begin = _begin;
    end = _end;
}


std::vector<std::string> MemorySegment::pop_value(int value){
    // returns seg[location+value] in D
    std::vector<std::string> ret;
    return ret;
}  

std::vector<std::string> MemorySegment::push_value(int value){
    // assigns D to seg[location+value]

    std::vector<std::string> ret;
    return ret;
}