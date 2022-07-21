#include "static_segment.hpp"


StaticSegment::StaticSegment(std::string _name, int _location, int _begin, int _end){
    name = _name; // location doesn't matter
    begin = _begin;
    end = _end;
}

std::vector<std::string> StaticSegment::pop_value(int value) {
    // returns seg[Foo.value] in D
    std::vector<std::string> ret;
    return ret;
} 
std::vector<std::string> StaticSegment::push_value(int value) {
    // assigns D to seg[Foo.value]
    std::vector<std::string> ret;
    return ret;
}