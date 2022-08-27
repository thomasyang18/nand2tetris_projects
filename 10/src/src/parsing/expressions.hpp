#ifndef _EXPRESSIONS_HPP_
#define _EXPRESSIONS_HPP_

#include "parser.hpp"

std::unique_ptr<Node> parseExpression();
std::unique_ptr<Node> parseTerm();
std::unique_ptr<Node> parseSubroutineCall();
std::unique_ptr<Node> parseExpressionList();
std::unique_ptr<Node> parseOp();
std::unique_ptr<Node> parseUnaryOp();
std::unique_ptr<Node> parseKeywordConstant();



#endif