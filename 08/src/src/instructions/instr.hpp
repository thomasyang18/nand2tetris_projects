#ifndef _INSTR_HPP_
#define _INSTR_HPP_

#include <string>
#include <vector>
#include <memory>

// Must implement a static 
class Instr
{
public:
    virtual std::vector<std::string> toString() = 0;
    static std::shared_ptr<Instr> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

#endif