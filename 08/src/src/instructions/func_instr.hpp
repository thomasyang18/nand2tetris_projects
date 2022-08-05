#ifndef _FUNC_INSTR_HPP_
#define _FUNC_INSTR_HPP_

#include "instr.hpp"

class FuncOp : public Instr
{
public:
    std::string name;
    unsigned int n_vars;
    virtual std::vector<std::string> toString() override; 
    static std::shared_ptr<FuncOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

class ReturnOp : public Instr
{
public:
    virtual std::vector<std::string> toString() override; 
    static std::shared_ptr<ReturnOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

#endif