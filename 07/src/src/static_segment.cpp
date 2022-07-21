#include "static_segment.hpp"


StaticSegment::StaticSegment(std::string _name, int _begin, int _end, std::string _file_name){
    name = _name; // location doesn't matter
    begin = _begin;
    end = _end;
    file_name = _file_name;
}

std::vector<std::string> StaticSegment::pop_value(int value) {
    // returns seg[Foo.value] in D
    std::vector<std::string> ret;
    ret.push_back("@" + file_name + "." + std::to_string(value));
    ret.push_back("D=A"); // probably could make it really simple for static, but for sake of implementation ease make it a little less efficient
    return ret;
} 
std::vector<std::string> StaticSegment::push_value(int value) {
    // assigns D to seg[Foo.value]
    std::vector<std::string> ret;
    ret.push_back("@" + file_name + "." + std::to_string(value));
    ret.push_back("D=M");
    return ret;
}
