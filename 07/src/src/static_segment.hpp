#ifndef _STATIC_SEGMENT_HPP_
#define _STATIC_SEGMENT_HPP_

#include "memory_segment.hpp"

class StaticSegment : public MemorySegment
{
public:
    StaticSegment(std::string _name, int _location, int _begin, int _end);
    // Doesn't use location stuff; instead generates Foo.value
    virtual std::vector<std::string> pop_value(int value = -1) override; // returns seg[Foo.value] in D
    virtual std::vector<std::string> push_value(int value = -1) override; // assigns D to seg[Foo.value]
};


#endif