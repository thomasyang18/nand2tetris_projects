#include "lexer.hpp"
#include "parser.hpp"
#include "runtime_context.hpp"

#include <fstream>
#include <iostream>


int main(int argc, char **argv ){
    // Compiles all files
    for (int i = 1; i < argc; i++){
        std::ifstream myfile;
        myfile.open(argv[i]);
        Lexer lex;
        lex.lex(myfile);

        Parser parser(lex);
        auto ans = parser.parse();

        RuntimeContext ctxt;        
        for (auto &instr: ans){
            ctxt.do_instr(instr);
        }
    }
}