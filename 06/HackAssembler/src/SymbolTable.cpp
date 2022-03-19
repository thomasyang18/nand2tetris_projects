#include "SymbolTable.h"

#include<map>
#include<string>
#include<iostream>
#include<fstream>

#define RESERVED_SYMBOLS_FILE "reserved_symbols.txt"
#define SYMBOL_CAP 16384

#define RESERVED_REGISTERS 16

std::map<std::string, int> symbolTable;

int symbolID = RESERVED_REGISTERS; // ROM can only have 32k size

// Initializes all default symbols and reserved registers
void initSymbolTable(){
	std::ifstream file(RESERVED_SYMBOLS_FILE);
	std::string s;
	int pos;

	while (file >> s >> pos){
		symbolTable[s] = pos;
	}

	for (int i = 0; i < RESERVED_REGISTERS; i++){
		std::string key = "R" +std::to_string(i);
		symbolTable[key] = i;
	}	
}

void addGotoLabel(std::string input, int line){
	if (symbolTable.find(input) != symbolTable.end()){
		// Actually a problem this time; can't have two goto labels
		std::cerr << "Cannot have two goto labels of the same name: " << input << " on line " << line << std::endl;
		exit(EXIT_FAILURE);
	}
	symbolTable[input] = line;

}

void addSymbol(std::string input){
	if (symbolID >= SYMBOL_CAP){
		std::cerr << "Exceeded Symbol Limit" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (symbolTable.find(input) != symbolTable.end()) return; // already have symbol
	symbolTable[input] = symbolID++;
}

int getSymbol(std::string input){
	if (symbolTable.find(input) != symbolTable.end()){
		return symbolTable[input];
	}
	std::cerr << "Did not find symbol: " << input << std::endl;
	exit(EXIT_FAILURE);
}
