#ifndef _LABEL_INSTR_HPP_
#define _LABEL_INSTR_HPP_

#include "instr.hpp"

class LabelOp : public Instr
{
public:
    std::string name;
    LabelOp(std::string _name);
    virtual std::vector<std::string> toString() override; 
};

class GotoOp : public Instr
{
public:
    std::string name;
    GotoOp(std::string _name);
    virtual std::vector<std::string> toString() override;
};

class IfGotoOp : public Instr
{
public:
    std::string name;
    IfGotoOp(std::string _name);
    virtual std::vector<std::string> toString() override;
};

#endif