#ifndef __PARSER_HEADER_
#define __PARSER_HEADER_

#include<iostream>
#include<fstream>

// This is the first pass through to get Labels 
void pass1(std::ifstream& input);

// Second pass through gets symbols, and builds the AST
void pass2(std::ifstream& input);

// Sends ASTnodes to file
void translate(std::ofstream& output);

#endif
