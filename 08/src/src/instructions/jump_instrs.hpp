#ifndef _LABEL_INSTR_HPP_
#define _LABEL_INSTR_HPP_

#include "instr.hpp"

class LabelOp : public Instr
{
public:
    std::string name;
    virtual std::vector<std::string> toString() override; 
    static std::shared_ptr<LabelOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

class GotoOp : public Instr
{
public:
    std::string name;
    virtual std::vector<std::string> toString() override;
    static std::shared_ptr<GotoOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

class IfGotoOp : public Instr
{
public:
    std::string name;
    virtual std::vector<std::string> toString() override;
    static std::shared_ptr<IfGotoOp> try_create_factory(std::vector<std::string> &tokens, unsigned int &pos);
};

#endif