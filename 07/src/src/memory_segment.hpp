#ifndef _MEMORY_SEGMENT_HPP_
#define _MEMORY_SEGMENT_HPP_

#include <string>
#include <vector>

class MemorySegment
{
public:
    MemorySegment();
    MemorySegment(std::string _name, int _location, int _begin, int _end);
    std::string name;
    virtual std::vector<std::string> pop_value(int value = -1); // returns seg[location+value] in D 
    virtual std::vector<std::string> push_value(int value = -1); // assigns D to seg[location+value]
    int location; // location on RAM for addressing
    int begin; // the value at RAM[location]
    int end; // technically don't need this but nice for future error checking
};

#endif