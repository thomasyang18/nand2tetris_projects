#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "expr_node.hpp"
#include "../tokenizer.hpp"
#include "expressions.hpp"
#include "program.hpp"
#include "statements.hpp"

extern std::unique_ptr<JackTokenizer> glob_tok;
void parse_error();
bool try_match_token(TokenType tokentype=none, std::string value="");
std::unique_ptr<Node> force_next_token(TokenType tokentype=none, std::string value="");

#endif