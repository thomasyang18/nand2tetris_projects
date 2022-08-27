#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <stdexcept>
#include <filesystem> // only an avaiable include on c++17
#include "tokenizer.hpp"
#include "parsing/parser.hpp"

int mode = 0;
// 1 is token validator mode
std::string prefix(std::string fullname){
    size_t lastindex = fullname.find_last_of("."); 
    std::string rawname = fullname.substr(0, lastindex);
    return rawname; 
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void parse_file(std::string file){
    if (!ends_with(file, ".jack")) return;
    
    JackTokenizer jt(file); 
    if (mode == 1){
        std::ofstream ofile(prefix(file) + "T.xml_mine");
        // Token mode
        ofile << "<tokens>" << std::endl;
        while (jt.has_more_tokens()){
            Token t = jt.get_cur_token();
            ofile << t.to_xml() << std::endl;   
            jt.advance();
        }
        ofile << "</tokens>" << std::endl;
        ofile.close();
        return;
    }

    glob_tok = jt;
    auto res = std::move(parseClass());
    
}

void parse_dir(std::string dir){ 
    for (const auto & entry: std::filesystem::directory_iterator(dir))
        parse_file(entry.path());
}


int main(int argc, char **argv){
    if (argc <= 1 || argc > 3) throw std::invalid_argument("Jack compiler takes up to 2 args - a file or directory, and a mode for test case stuff");
    if (argc == 3) mode = atoi(argv[2]);
    struct stat s;
    if( stat(argv[1],&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            parse_dir(argv[1]);
        }
        else if( s.st_mode & S_IFREG )
        {
            parse_file(argv[1]);
        }
        else throw std::invalid_argument("Jack compiler takes exactly 1 arg - a file or directory");
    }
    else throw std::invalid_argument("Jack compiler takes exactly 1 arg - a file or directory");
}