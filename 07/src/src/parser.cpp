#include "parser.hpp"

#include <stdexcept>

Parser::Parser(Lexer lexer){
    this->tokens = lexer.tokens;
    pos = 0;
    end = false;
}


// Pointers, because don't want to deal with weird abstract class BS
std::vector<std::shared_ptr<Instr>> Parser::parse()
{
    if (end) throw std::invalid_argument("Tried parsing same file again");
    std::vector<std::shared_ptr<Instr>> ans;
    int line = 1;
    while (pos < tokens.size()){
        std::shared_ptr<Instr> instr(try_create_instr());
        if (instr){
            ans.push_back(instr);
        }
        else{
            throw std::invalid_argument("Failed creating instruction on line " + std::to_string(line) + "\n");
        }
        line++;
    }
    end = true;
    return ans;
}

constexpr unsigned int hash(const char *s, int off = 0){                        
    return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];                           
} 


std::shared_ptr<Instr> Parser::try_create_instr()
{
    std::shared_ptr<Instr> instr(nullptr);
    if (instr = try_create_operator()) return instr;
    if (instr = try_create_stack()) return instr;
    return instr;
}

std::shared_ptr<Instr> Parser::try_create_operator(){
    std::shared_ptr<Instr> instr(nullptr);
    if (pos + 1 > tokens.size()) return instr;
    switch (hash(tokens[pos].c_str())){
        case hash("neg"):
        case hash("not"):
        instr.reset(new UnaryOp(tokens[pos++])); 
        break;
        case hash("add"):
        case hash("sub"):
        case hash("eq"):
        case hash("gt"):
        case hash("lt"):
        case hash("and"):
        case hash("or"):
        instr.reset(new BinaryOp(tokens[pos++]));
        break;
    }
    return instr;
}

std::shared_ptr<Instr> Parser::try_create_stack(){
    std::shared_ptr<Instr> instr(nullptr);
    if (pos + 3 > tokens.size()) return instr;
    if (tokens[pos] != "push" && tokens[pos] != "pop") return instr;
    instr.reset(new StackOperation(tokens[pos], tokens[pos+1], tokens[pos+2]));
    pos+=3;
    return instr;  
}