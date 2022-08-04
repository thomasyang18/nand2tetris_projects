#ifndef _CONSTANT_SEGMENT_HPP_
#define _CONSTANT_SEGMENT_HPP_

#include "memory_segment.hpp"

class ConstantSegment : public MemorySegment
{
public:
    ConstantSegment(std::string _name);
    virtual std::vector<std::string> pop_value(int value = -1) override; // not implemented
    virtual std::vector<std::string> push_value(int value = -1) override; // just returns value in D
};


#endif