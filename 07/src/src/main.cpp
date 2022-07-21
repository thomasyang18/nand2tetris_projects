#include "lexer.hpp"
#include "parser.hpp"
#include "runtime_context.hpp"

#include <fstream>
#include <iostream>

std::string fileize(std::string str){
    int ptr = (int)str.size()-1;
    for (; ptr >= 0; ptr--) if (str[ptr] == '/') break;
    int rn = ptr+1;
    int end = -1;
    for (++ptr; ptr < (int)str.size(); ptr++){
        if (str[ptr] == '.') end = ptr;
    }
    return str.substr(rn, end-rn);
}



int main(int argc, char **argv ){
    // Compiles all files
    for (int i = 1; i < argc; i++){
        std::ifstream myfile;
        myfile.open(argv[i]);
        Lexer lex;
        lex.lex(myfile);

        Parser parser(lex);
        auto ans = parser.parse();
        std::string str = argv[i];

        RuntimeContext ctxt(fileize(str));     
        for (auto &instr: ans){
            for (auto &text: ctxt.do_instr(instr)){
                std::cout << text << std::endl;
            }
        }
    }
}