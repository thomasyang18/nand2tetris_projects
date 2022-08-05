#include "runtime_context.hpp"
#include "memory_segments/constant_segment.hpp"
#include "memory_segments/static_segment.hpp"
#include "memory_segments/stack_segment.hpp"
#include "memory_segments/baseless_segment.hpp"

#include "instructions/stack_instrs.hpp"
#include "instructions/jump_instrs.hpp"
#include "instructions/call_instr.hpp"
#include "instructions/func_instr.hpp"
#include <stdexcept>
#include <fstream>

void RuntimeContext::bootstrap(){
    std::ofstream ofile;
    ofile.open("bootstrap.asm");
    ofile << "@256\n" << "D=A\n" << "@0\n" << "M=D\n";
    ofile << "@Sys.init\n" << "0;JMP\n";
    ofile.close();
}

RuntimeContext::RuntimeContext(){}

RuntimeContext::RuntimeContext(std::string _file_name, bool _debug){
    debug = _debug;
    file_name = _file_name;
    add_segment(std::shared_ptr<StackSegment>(new StackSegment("stack", 0, 256, 2047)));
    add_segment(std::shared_ptr<MemorySegment>(new MemorySegment("local", 1)));
    add_segment(std::shared_ptr<MemorySegment>(new MemorySegment("argument", 2)));
    add_segment(std::shared_ptr<MemorySegment>(new MemorySegment("this", 3)));
    add_segment(std::shared_ptr<MemorySegment>(new MemorySegment("that", 4)));
    add_segment(std::shared_ptr<ConstantSegment>(new ConstantSegment("constant")));
    add_segment(std::shared_ptr<StaticSegment>(new StaticSegment("static", 16,255, _file_name)));
    add_segment(std::shared_ptr<BaselessSegment>(new BaselessSegment("pointer", 3,4)));
    add_segment(std::shared_ptr<BaselessSegment>(new BaselessSegment("temp", 5,12)));
}


void RuntimeContext::add_segment(std::shared_ptr<MemorySegment> ptr){
    name2seg[ptr->name] = ptr;
}

std::string to_comment(std::shared_ptr<Instr> instr){
    std::string res = "//";
    for (auto x: instr->toString()) {
        res += " ";
        res += x;
    } 
    return res;
}

void push_all_back(std::vector<std::string> &here, std::vector<std::string> there){
    for (auto &instr: there) here.push_back(instr);
}

constexpr unsigned int hash(const char *s, int off = 0){                        
    return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];                           
} 

std::string RuntimeContext::new_temp_label(){
    return file_name + "_TEMP_LABEL_" + std::to_string(temp_labels++);
}

std::vector<std::string> swap_registers(){
    std::vector<std::string> ret;
    ret.push_back("D=A-D");
    ret.push_back("A=D-A");
    ret.push_back("D=D-A");
    ret.push_back("A=-A");
    return ret;
}

std::vector<std::string> push_label_into_D(std::string label){
    std::vector<std::string> ret;
    ret.push_back("@" + label);
    ret.push_back("D=A");
    return ret;
}

std::vector<std::string> push_constant_into_D(unsigned int constant){ 
    // does NOT dereference label
    std::vector<std::string> ret;
    ret.push_back("@" + std::to_string(constant));
    ret.push_back("D=A");
    return ret;
}

std::vector<std::string> push_dereferenced_label_into_D(std::string label){
    // takes base of various stack pointers
    std::vector<std::string> ret;
    ret.push_back("@" + label);
    ret.push_back("D=M");
    return ret;
}

std::vector<std::string> RuntimeContext::do_instr(std::shared_ptr<Instr> instr){
    
    std::vector<std::string> ret;
    if (debug) ret.push_back(to_comment(instr));
    
    if (auto op = std::dynamic_pointer_cast<StackOperation>(instr)){
        if (!name2seg.count(op->type)) throw std::invalid_argument("Unknown memory segment name: " + op->type);
        
        if (op->push == "push"){
            push_all_back(ret, name2seg[op->type]->push_value(op->val));
            push_all_back(ret, name2seg["stack"]->push_value());
        }
        else if (op->push == "pop"){
            push_all_back(ret, name2seg[op->type]->pop_value(op->val));
            push_all_back(ret, name2seg["stack"]->pop_value(1));
            push_all_back(ret, swap_registers());
            ret.push_back("M=D");
        }
        else throw std::invalid_argument("Stack instruction not implemented");
    } else if (auto op = std::dynamic_pointer_cast<BinaryOp>(instr)){
        push_all_back(ret, name2seg["stack"]->pop_value()); // puts y in place
        // do a fancy instruction that saves to A register
        push_all_back(ret, name2seg["stack"]->pop_value(1));
        switch(hash(op->opName.c_str())){
            case hash("add"):
            ret.push_back("D=D+A");
            break;
            case hash("sub"):
            ret.push_back("D=A-D");
            break;
            // 0 is false, -1 is true
            case hash("eq"):
            case hash("gt"):
            case hash("lt"):
            {
                ret.push_back("D=A-D");
                std::string new_label = new_temp_label();
                std::string new_label_2 = new_temp_label();
                ret.push_back("@" + new_label);
                switch(hash(op->opName.c_str())){
                    // if it's true, i wanna jump
                    case hash("eq"):
                    ret.push_back("D=D;JEQ");
                    break;
                    case hash("gt"):
                    ret.push_back("D=D;JGT");
                    break;
                    case hash("lt"):
                    ret.push_back("D=D;JLT");
                    break;
                }
                ret.push_back("@" + new_label_2);
                ret.push_back("D=0;JMP"); // will make it false
                ret.push_back("(" + new_label +")");
                ret.push_back("D=-1"); // will make it true
                ret.push_back("(" + new_label_2 + ")");
            }
            break;
            case hash("and"):
            ret.push_back("D=D&A");
            break;
            case hash("or"):
            ret.push_back("D=D|A");
            break;
            
            default:
            throw std::invalid_argument("Binary Op not implemented");
        }
        push_all_back(ret, name2seg["stack"]->push_value());
    } else if (auto op = std::dynamic_pointer_cast<UnaryOp>(instr)){
        push_all_back(ret, name2seg["stack"]->pop_value());
        switch(hash(op->opName.c_str())){
            case hash("neg"):
            ret.push_back("D=-D");
            break;
            case hash("not"):
            ret.push_back("D=!D");
            break;
            default:
            throw std::invalid_argument("Unary Op not implemented");
        }
        push_all_back(ret, name2seg["stack"]->push_value());
    } else if (auto op = std::dynamic_pointer_cast<LabelOp>(instr)){
        ret.push_back("(" + op->name + ")");
    } else if (auto op = std::dynamic_pointer_cast<GotoOp>(instr)){
        ret.push_back("@" + op->name);
        ret.push_back("0;JMP");
    } else if (auto op = std::dynamic_pointer_cast<IfGotoOp>(instr)){
        // IfGoto is implemented as if the top argument on stack (after popping) 
        push_all_back(ret, name2seg["stack"]->pop_value());
        ret.push_back("@" + op->name);
        ret.push_back("D;JGT");
    } else if (auto op = std::dynamic_pointer_cast<CallOp>(instr)){
        std::string temp_label = new_temp_label();
        push_all_back(ret, push_label_into_D(temp_label));
        push_all_back(ret, name2seg["stack"]->push_value());

        push_all_back(ret, push_dereferenced_label_into_D("LCL"));
        push_all_back(ret, name2seg["stack"]->push_value());

        push_all_back(ret, push_dereferenced_label_into_D("ARG"));
        push_all_back(ret, name2seg["stack"]->push_value());

        push_all_back(ret, push_dereferenced_label_into_D("THIS"));
        push_all_back(ret, name2seg["stack"]->push_value());

        push_all_back(ret, push_dereferenced_label_into_D("THAT"));
        push_all_back(ret, name2seg["stack"]->push_value());

        push_all_back(ret, push_dereferenced_label_into_D("SP"));
        ret.push_back("@LCL");
        ret.push_back("M=D");

        ret.push_back("@ARG");
        ret.push_back("M=D");
        push_all_back(ret, push_constant_into_D(5));
        ret.push_back("@ARG");
        ret.push_back("M=M-D");
        push_all_back(ret, push_constant_into_D(op->n_args));
        ret.push_back("@ARG");
        ret.push_back("M=M-D");
        ret.push_back("@" + op->name);
        ret.push_back("0;JMP");
        ret.push_back("("+temp_label+")");
    } else if (auto op = std::dynamic_pointer_cast<FuncOp>(instr)){
        ret.push_back("(" + op->name+")");
        push_all_back(ret, push_constant_into_D(0)); // D is never changed when stack pushes so this is fine
        for (unsigned int times = 0; times < op->n_vars; times++){
            push_all_back(ret, name2seg["stack"]->push_value());
        }
    } else if (auto op = std::dynamic_pointer_cast<ReturnOp>(instr)){
        // Pop stack into arg[0]. Reused code but w/e
        push_all_back(ret, name2seg["stack"]->pop_value());
        ret.push_back("@ARG");
        ret.push_back("A=M");
        ret.push_back("M=D");
        // Store ARG from before
        push_all_back(ret, push_dereferenced_label_into_D("ARG"));
        ret.push_back("@R14");
        ret.push_back("M=D");
        // SP = LCL
        push_all_back(ret, push_dereferenced_label_into_D("SP"));
        ret.push_back("@SP"); 
        ret.push_back("M=D");
        //pop until return address
        push_all_back(ret, name2seg["stack"]->pop_value());
        ret.push_back("@THAT");
        ret.push_back("M=D");

        push_all_back(ret, name2seg["stack"]->pop_value());
        ret.push_back("@THIS");
        ret.push_back("M=D");
        
        push_all_back(ret, name2seg["stack"]->pop_value());
        ret.push_back("@ARG");
        ret.push_back("M=D");
        
        push_all_back(ret, name2seg["stack"]->pop_value());
        ret.push_back("@LCL");
        ret.push_back("M=D");
        //pop return address into temp
        push_all_back(ret, name2seg["stack"]->pop_value());
        ret.push_back("@R15");
        ret.push_back("M=D");
        //sp = r14 (arg from before) +1
        push_all_back(ret, push_dereferenced_label_into_D("R14"));
        ret.push_back("@SP");
        ret.push_back("M=D+1");
        //goto temp
        ret.push_back("@R15");
        ret.push_back("A=M;JMP");
    }
    
    else throw std::invalid_argument("Instruction not implemented");
    
    return ret;
}

