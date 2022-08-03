#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "instr.hpp"
#include "lexer.hpp"
#include <vector>
#include <string>
#include <memory>

class Parser
{

public:
    std::vector<std::shared_ptr<Instr>> parse();
    Parser (Lexer lexer);

private:
    long unsigned int pos;
    std::vector<std::string> tokens;
    bool end;
    std::shared_ptr<Instr> try_create_instr();
    std::shared_ptr<Instr> try_create_operator();
    std::shared_ptr<Instr> try_create_stack();
};

#endif