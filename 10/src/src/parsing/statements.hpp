#ifndef _STATEMENTS_HPP_
#define _STATEMENTS_HPP_

#include "parser.hpp"

std::unique_ptr<Node> parseStatements();
std::unique_ptr<Node> parseStatement();
std::unique_ptr<Node> parseLetStatement();
std::unique_ptr<Node> parseIfStatement();
std::unique_ptr<Node> parseWhileStatement();
std::unique_ptr<Node> parseDoStatement();
std::unique_ptr<Node> parseReturnStatement();

#endif