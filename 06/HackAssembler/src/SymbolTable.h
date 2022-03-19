#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H

#include<string>

void initSymbolTable();

void addGotoLabel(std::string input, int line);

void addSymbol(std::string input);
int getSymbol(std::string input);

// debug method
void printSymbolTable();

#endif
