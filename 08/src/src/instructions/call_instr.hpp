#ifndef _CALL_INSTR_HPP_
#define _CALL_INSTR_HPP_

#include "instr.hpp"

class CallOp : public Instr
{
public:
    std::string name;
    unsigned int n_args;
    virtual std::vector<std::string> toString() override; 
    static std::shared_ptr<CallOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

#endif