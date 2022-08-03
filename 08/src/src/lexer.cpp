#include "lexer.hpp"

#include <sstream>

void Lexer::lex(std::ifstream& myfile)
{   
    std::string line;
    std::vector<std::string> ans;
    while (std::getline(myfile, line)){ 
        int cnt_slash = 0;
        std::string token;
        for (auto c: line){
            if (c == '/') cnt_slash++;
            else {
                cnt_slash = 0;
            }
            if (cnt_slash >= 2) {
                token = "";
                break;
            }
            if (isspace(c)){
                if (token.size() > 0) ans.push_back(token);
                token = "";
            }
            else token += c;
            
        }
        if (token.size() > 0) ans.push_back(token);
    }       
    this->tokens = ans;
}

Lexer::Lexer(){}