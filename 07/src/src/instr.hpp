#ifndef _INSTR_HPP_
#define _INSTR_HPP_

#include <string>
#include <vector>

class Instr
{
public:
    virtual std::vector<std::string> toString() = 0; 
};

class StackOperation : public Instr
{
public:
    std::string type;
    std::string push; // if not push, then pop
    int val;
    StackOperation(std::string _push, std::string _type, std::string _val);
    std::vector<std::string> toString() override;
};

class BinaryOp: public Instr
{
private:
    std::string opName;
public:
    BinaryOp(std::string _opName);
    std::vector<std::string> toString() override;
};

class UnaryOp: public Instr
{
private:
    std::string opName;
public:
    UnaryOp(std::string _opName);
    std::vector<std::string> toString() override;
};

#endif