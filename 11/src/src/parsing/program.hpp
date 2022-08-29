#ifndef _PROGRAM_STRUCTURE_HPP_
#define _PROGRAM_STRUCTURE_HPP_

#include "parser.hpp"

std::unique_ptr<Node> parseClass();
std::unique_ptr<Node> parseClassVarDec();
std::unique_ptr<Node> parseType();
std::unique_ptr<Node> parseSubroutineDec();
std::unique_ptr<Node> parseParameterList();
std::unique_ptr<Node> parseSubroutineBody();
std::unique_ptr<Node> parseVarDec();
std::unique_ptr<Node> parseClassName();
std::unique_ptr<Node> parseSubroutineName();
std::unique_ptr<Node> parseVarName();

#endif