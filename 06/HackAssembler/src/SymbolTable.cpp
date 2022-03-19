#include "SymbolTable.h"

#include<map>
#include<string>
#include<iostream>
#include<fstream>

#define RESERVED_SYMBOLS_FILE "reserved_symbols.txt"
#define SYMBOL_CAP 16384

#define RESERVED_REGISTERS 16

std::map<std::string, int> symbolTable;

int symbolID = RESERVED_REGISTERS; // will place them in an iterative order

void initSymbolTable(){
	std::ifstream file(RESERVED_SYMBOLS_FILE);
	std::string s;
	int pos;

	while (file >> s >> pos){
		symbolTable[s] = pos;
	}

	for (int i = 0; i < 16; i++){
		std::string key = "R" +std::to_string(i);
		symbolTable[key] = i;
	}	
}

void addLabel(std::string input){
	if (symbolID >= SYMBOL_CAP){
		std::cerr << "Exceeded Symbol Limit" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (symbolTable.find(input) != symbolTable.end()) return; // already have symbol
	symbolTable[input] = symbolID++;
}

int getLabel(std::string input){
	if (symbolTable.find(input) != symbolTable.end()){
		return symbolTable[input];
	}
	std::cerr << "Did not find symbol: " << input << std::endl;
	exit(EXIT_FAILURE);
}
