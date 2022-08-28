#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "expr_node.hpp"
#include "../tokenizer.hpp"
#include "expressions.hpp"
#include "program.hpp"
#include "statements.hpp"

// x is a std::unique_ptr<Node>, y is the result of a parsing funciton
// ex: PUSH_REC(x,parseClass())
#define PUSH_REC(y) res->children.push_back(y);
#define INIT(x) std::unique_ptr<Node> res(new Node(x));
 

extern std::unique_ptr<JackTokenizer> glob_tok;
void parse_error();

// Match token does a peek
// force_next_token throws an error if new token doesn't work, advances & pushes new token & returns true otherwise
// try_force_token does a peek, pushes new token & advances if it works & returns true, otherwise returns false

bool try_match_token(TokenType tokentype=none, std::string value="");
bool force_next_token(std::unique_ptr<Node> &node, TokenType tokentype=none, std::string value="");
bool try_force_token(std::unique_ptr<Node> &node, TokenType tokentype=none, std::string value="");


#endif