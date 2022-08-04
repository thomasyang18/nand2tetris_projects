#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "instructions/instr.hpp"
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
    unsigned int pos;
    std::vector<std::string> tokens;
    bool end;
};

#endif