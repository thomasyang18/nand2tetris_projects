#include "instr.hpp"
#include <stdexcept>
#include "jump_instrs.hpp"
#include "stack_instrs.hpp"
#include "call_instr.hpp"
#include "func_instr.hpp"

// Factory class calls all subclass's factory classes and tries all of them

std::shared_ptr<Instr> Instr::try_create_factory(std::vector<std::string> &tokens, unsigned int &pos){
    std::shared_ptr<Instr> ret(nullptr);
    if (ret = StackOperation::try_create_factory(tokens, pos)) return ret;
    if (ret = BinaryOp::try_create_factory(tokens, pos)) return ret;
    if (ret = UnaryOp::try_create_factory(tokens, pos)) return ret;
    if (ret = LabelOp::try_create_factory(tokens, pos)) return ret;
    if (ret = GotoOp::try_create_factory(tokens, pos)) return ret;
    if (ret = IfGotoOp::try_create_factory(tokens, pos)) return ret;
    if (ret = CallOp::try_create_factory(tokens, pos)) return ret;
    if (ret = FuncOp::try_create_factory(tokens, pos)) return ret;
    if (ret = ReturnOp::try_create_factory(tokens, pos)) return ret;
    
    return ret;
}