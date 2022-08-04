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
        std::shared_ptr<Instr> instr = Instr::try_create_factory(tokens, pos);
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
