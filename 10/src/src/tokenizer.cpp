#include "tokenizer.hpp"
#include <fstream>
#include <set>
#include <iostream>
#include <regex>
#include <cctype>


void JackTokenizer::advance(){
    pos++;
}

Token JackTokenizer::get_cur_token(){
    if (has_more_tokens()) return tokens[pos];
    Token empty("",none);
    return empty;
}

bool JackTokenizer::has_more_tokens(){
    return pos < tokens.size();
}

std::vector<std::string> keywords = {
    "class", "constructor", "function", "method", 
    "field", "static", "var", "int", 
    "char", "boolean", "void", "true",
    "false", "null", "this", "let",
    "do", "if", "else", "while", "return"
};

std::vector<std::string> symbols = {
    "{", "}", "(", ")", "[", "]", ".", ",", ";", "+", "-", "*",
    "/", "&", "|", "<", ">", "=", "~"
};

JackTokenizer::JackTokenizer(std::string _filename){
    std::ifstream input(_filename);
    // To handle default constructor case; a bit sketch but w/e
    if (!input.is_open()) return;
    tokens.clear();

    // Convert input to string for easy tokenizing
    input.seekg(0, std::ios::end);
    size_t size = input.tellg();
    std::string buffer(size, ' ');
    input.seekg(0);
    input.read(&buffer[0], size); 
    std::string temp = "";

    for (size_t i = 0; i < size;){
        // Handle comments, whitespace 
        if (isspace(buffer[i])) {i++; continue;}
        if (i + 1 < size and buffer[i] == '/' and buffer[i+1] == '/'){
            while (i < size and buffer[i] != '\n') i++;
            i++; // to skip the newline
            continue;
        }
        if (i + 1 < size and buffer[i] == '/' and buffer[i+1] == '*'){
            i+=2;
            while (i+1 < size and !(buffer[i] == '*' and buffer[i+1] == '/')) i++;
            i+=2; // If i == size-1, we reached EOF so fail loop check. 
            // Otherwise, we want to +=2 to skip past the */_
            continue;
        }

        // Handle tokens
        for (auto s: keywords) {
            if (i + s.size() > size) continue;
            auto subbuffer = buffer.substr(i, s.size());
            if (subbuffer.compare(s) == 0) {
                tokens.push_back(Token(s,keyword));
                i += s.size();
                goto end_token_loop;
            }
        }


        for (auto s: symbols) {
            if (i + s.size() > size) continue;
            auto subbuffer = buffer.substr(i, s.size());
            if (subbuffer.compare(s) == 0) {
                tokens.push_back(Token(s,symbol));
                i += s.size();
                goto end_token_loop;
            }
        }

        

        // This will handle negative numbers poorly, I'd imagine
        if (isdigit(buffer[i])){
            std::string num;
            while (i < size && isdigit(buffer[i])) num += buffer[i++];
            if (num.size() >= 7){
                throw std::invalid_argument("One of your numbers, " + num + ", is not the range 0,32767");
            }
            int number = stoi(num);
            if (number < 0 || number > 32767) {
                throw std::invalid_argument("One of your numbers, " + num + ", is not the range 0,32767");
            }
            tokens.push_back(Token(num,integerConstant));
            continue;
        }


        // handles strings without an escape code
        if (buffer[i] == '"'){
            std::string s = "";
            for (++i; i < size and buffer[i] != '"';) s += buffer[i++];
            i++;
            tokens.push_back(Token(s, stringConstant));
            continue;
        }


        // matches [a-zA-Z_][a-zA-Z_0-9]*
        if (isalpha(buffer[i]) or buffer[i] == '_'){
            temp.clear();
            temp = buffer[i++];
            while (i < size and 
            (isalpha(buffer[i]) or buffer[i] == '_' or isdigit(buffer[i]))
            ) temp += buffer[i++];

            tokens.push_back(Token(temp, identifier));

            continue;
        }


        throw std::invalid_argument("Tokenizer failed on char index " + std::to_string(i));

        end_token_loop:;
    }
    

    input.close();
}
