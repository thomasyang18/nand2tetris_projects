#include "instr.hpp"
#include "stack_instrs.hpp"
#include <stdexcept>

// Factory class calls all subclass's factory classes and tries all of them

std::shared_ptr<Instr> Instr::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    std::shared_ptr<Instr> ret(nullptr);
    if (ret = StackOperation::try_create_factory(tokens, pos)) return ret;
    if (ret = BinaryOp::try_create_factory(tokens, pos)) return ret;
    if (ret = UnaryOp::try_create_factory(tokens, pos)) return ret;
    return ret;
}