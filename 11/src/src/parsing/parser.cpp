#include "parser.hpp"
#include <stdexcept>

std::unique_ptr<JackTokenizer> glob_tok;
std::set<std::string> class_names;
std::ofstream parse_ofile;

void parse_error(std::string additional){
    Token tok = glob_tok->get_cur_token();
    std::string mandatory = "Parsing failed on token " + tok.to_xml() + ", token number " + std::to_string(glob_tok->pos);
    throw std::invalid_argument("\n" + additional + "\n" + mandatory);
}

bool try_match_token(TokenType tokentype, std::string value){
    auto tok = glob_tok->get_cur_token();
    bool cond1 = tok.type == tokentype || tokentype == none;
    bool cond2 = tok.value == value || value.empty();
    return cond1 && cond2;
}

bool force_next_token(std::unique_ptr<Node> &node, TokenType tokentype, std::string value){
    auto tok = glob_tok->get_cur_token();
    if (!try_match_token(tokentype, value)) {
        parse_error("I tried to parse tokentype " + std::to_string(tokentype) + " with value " + value);
    }
    glob_tok->advance();
    node->children.push_back(std::unique_ptr<Node>(new Node(tok)));
    return true;
}

bool try_force_token(std::unique_ptr<Node> &node, TokenType tokentype, std::string value){
    auto tok = glob_tok->get_cur_token();
    if (!try_match_token(tokentype, value)) return false;
    glob_tok->advance();
    node->children.push_back(std::unique_ptr<Node>(new Node(tok)));
    return true;
}
