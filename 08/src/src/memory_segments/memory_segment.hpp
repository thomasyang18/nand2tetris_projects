#ifndef _MEMORY_SEGMENT_HPP_
#define _MEMORY_SEGMENT_HPP_

#include <string>
#include <vector>

class MemorySegment
{
public:
    MemorySegment();
    MemorySegment(std::string _name, std::string hack_name);
    std::string name;
    std::string hack_name;
    virtual std::vector<std::string> pop_value(int value = -1);  // pop off D, the stack var, into seg[location+value] 
    virtual std::vector<std::string> push_value(int value = -1); // pushes seg[location+value] to stack, so store result in D 
};

#endif