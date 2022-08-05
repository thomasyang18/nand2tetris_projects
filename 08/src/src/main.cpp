#include "lexer.hpp"
#include "parser.hpp"
#include "runtime_context.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sys/stat.h>
#include <string>
#include <filesystem>

bool debug = false;

std::string fileize(std::string str){ // turns FILE.vm into FILE
    int ptr = (int)str.size()-1;
    for (; ptr >= 0; ptr--) if (str[ptr] == '/') break;
    int rn = ptr+1;
    int end = -1;
    for (++ptr; ptr < (int)str.size(); ptr++){
        if (str[ptr] == '.') end = ptr;
    }
    return str.substr(rn, end-rn);
}

std::string file_name_to_asm(std::string str){ // turns FILE.vm into FILE.asm
    int ptr = (int)str.size()-1;
    std::string suffix = "";
    for (; ptr >= 0; ptr--) if (str[ptr] == '.') break; else suffix += str[ptr];
    std::reverse(suffix.begin(), suffix.end());
    if (suffix != "vm") {
        return "";
        //throw std::invalid_argument("File " + str + " does not end in '.vm'");
    }
    return str.substr(0, ptr) + ".asm";
}

void parse_file(std::string file){
    std::string outfile = file_name_to_asm(file);
    if (outfile == "") return;

    if (file.find("Sys.vm") != std::string::npos) RuntimeContext::bootstrap();

    std::ifstream myfile;
    myfile.open(file);
    Lexer lex;
    lex.lex(myfile);

    Parser parser(lex);
    auto ans = parser.parse();
    std::string str = file;

    RuntimeContext ctxt(fileize(str), debug);     

    std::ofstream ofile;
    ofile.open(outfile);

    for (auto &instr: ans){
        for (auto &text: ctxt.do_instr(instr)){
            ofile << text << '\n';
        }
    }

    myfile.close();
    ofile.close();
}

void parse_dir(std::string dir){ // Parses only the .vm files in a directory
    for (const auto & entry: std::filesystem::directory_iterator(dir))
        parse_file(entry.path());
}

int main(int argc, char **argv ){
    // Compiles all files
    for (int i = 1; i < argc; i++){

        if (argv[i][0] == '-'){
            if (argv[i][1] == 'd') debug = true;
            continue;
        }

        struct stat s;
        if( stat(argv[i],&s) == 0 ) {
            if( s.st_mode & S_IFDIR ) {
                //it's a directory
                parse_dir(argv[i]);
            } else if( s.st_mode & S_IFREG ) {
                //it's a file
                parse_file(argv[i]);
            } else {
                //something else
            }
        } else {
            throw std::invalid_argument("Not a file or directory");
        }
    }
}
