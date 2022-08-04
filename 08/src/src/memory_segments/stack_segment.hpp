#ifndef _STACK_SEGMENT_HPP_
#define _STACK_SEGMENT_HPP_

#include "memory_segment.hpp"

class StackSegment : public MemorySegment
{
public:
    StackSegment(std::string _name, int _location, int _begin, int _end);
    // no use for value when it comes to the stack
    virtual std::vector<std::string> pop_value(int value = -1) override; // subtracts ptr, returns seg[ptr] in D 
    virtual std::vector<std::string> push_value(int value = -1) override; // returns seg[ptr] in D, increments ptr afterwards as well
    int stack_ptr; // actually needs to keep track of the value of the stack
    int begin, end;
};

#endif