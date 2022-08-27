#include "parser.hpp"
#include <stdexcept>

std::unique_ptr<JackTokenizer> glob_tok;

void parse_error(){
    Token tok = glob_tok->get_cur_token();
    throw std::invalid_argument("Parsing failed on token " + tok.to_xml() + ", token number " + std::to_string(glob_tok->pos));
}

bool try_match_token(TokenType tokentype, std::string value){
    auto tok = glob_tok->get_cur_token();
    bool cond1 = tok.type == tokentype || tokentype == none;
    bool cond2 = tok.value == value || value.empty();
    return cond1 && cond2;
}

std::unique_ptr<Node> force_next_token(TokenType tokentype, std::string value){
    auto tok = glob_tok->get_cur_token();
    if (!try_match_token(tokentype, value)) parse_error();
    glob_tok->advance();
    return std::unique_ptr<Node>(new Node(tok));    
}