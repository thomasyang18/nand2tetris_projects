#ifndef _STACK_INSTRS_HPP_
#define _STACK_INSTRS_HPP_

#include "instr.hpp"

class StackOperation : public Instr
{
public:
    std::string type;
    std::string push; // if not push, then pop
    int val;
    std::vector<std::string> toString() override;
    static std::shared_ptr<StackOperation> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

class BinaryOp: public Instr
{
public :
    std::string opName;
    std::vector<std::string> toString() override;
    static std::shared_ptr<BinaryOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

class UnaryOp: public Instr
{
public :
    std::string opName;
    std::vector<std::string> toString() override;
    static std::shared_ptr<UnaryOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};


#endif