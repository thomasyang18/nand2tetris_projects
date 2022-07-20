#ifndef _RUNTIME_CONTEXT_HPP_
#define _RUNTIME_CONTEXT_HPP_

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include "instr.hpp"
#include "memory_segment.hpp"

class RuntimeContext
{
public:
    RuntimeContext();
    // Returns corresponding assembly instructions as well
    std::vector<std::string> do_instr(std::shared_ptr<Instr> instr);
private:
    void add_segment(MemorySegment segment);
    std::map<std::string, MemorySegment> name2seg;
};

#endif