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
    void add_segment(std::shared_ptr<MemorySegment> ptr);
private:
    std::map<std::string, std::shared_ptr<MemorySegment>> name2seg;
    int temp_labels = 0;
    std::string new_temp_label();
};

#endif