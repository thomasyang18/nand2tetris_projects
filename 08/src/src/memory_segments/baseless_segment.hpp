// A little weird to have the baseless segment inherit from memorysegment, but I think it makes more sense
// than other way around.

#ifndef _POINTER_SEGMENT_HPP_
#define _POINTER_SEGMENT_HPP_

#include "memory_segment.hpp"

class BaselessSegment : public MemorySegment
{
public:
    BaselessSegment(std::string _name, int _begin, int _end);
    virtual std::vector<std::string> pop_value(int value = -1) override; // pop off D, the stack var, into seg[base+value] 
    virtual std::vector<std::string> push_value(int value = -1) override; // pushes seg[base+value] to stack, so store result in D
    int begin, end;
};

#endif