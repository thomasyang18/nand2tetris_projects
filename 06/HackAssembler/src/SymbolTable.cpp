#include "SymbolTable.h"

#include<map>
#include<string>
#include<iostream>
#include<fstream>

#define SYMBOL_CAP 16384

#define RESERVED_REGISTERS 16

std::map<std::string, int> symbolTable;

int symbolID = RESERVED_REGISTERS; // ROM can only have 32k size

// Initializes all default symbols and reserved registers
void initSymbolTable(){
	symbolTable["SCREEN"] = 16384;
	symbolTable["KBD"] = 24576;
	std::string arr[5] = {"SP", "LCL", "ARG", "THIS", "THAT"};
	for (int i = 0; i < 5; i++) symbolTable[arr[i]] = i;


	for (int i = 0; i < RESERVED_REGISTERS; i++){
		std::string key = "R" +std::to_string(i);
		symbolTable[key] = i;
	}	
}

void addGotoLabel(std::string input, int line){
	if (symbolTable.count(input)){
		// Actually a problem this time; can't have two goto labels
		std::cerr << "Cannot have two goto labels of the same name: " << input << " on line " << line << std::endl;
		exit(EXIT_FAILURE);
	}
	//std::cerr << "Mapping label " << input << " to " << line << std::endl;

	symbolTable[input] = line;

}

void addSymbol(std::string input){

	if (symbolID >= SYMBOL_CAP){
		std::cerr << "Exceeded Symbol Limit" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if (symbolTable.count(input)) return; // already have symbol

	//std::cerr << "Mapping " << input << " to " << symbolID << std::endl;
	symbolTable[input] = symbolID++;
}

int getSymbol(std::string input){
	if (symbolTable.find(input) != symbolTable.end()){
		return symbolTable[input];
	}
	std::cerr << "Did not find symbol: " << input << std::endl;
	exit(EXIT_FAILURE);
}

//debug methods

void printSymbolTable(){
	std::cout << "-------Symbol Table-------" << std::endl;
	for (auto entry: symbolTable){
		std::cout << entry.first << " " << entry.second << std::endl;
	}
	std::cout << "-------End of Symbol Table------" << std::endl;
}
