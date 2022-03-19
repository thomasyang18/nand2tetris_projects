#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"
#include "SymbolTable.h"
#include "Translator.h"

#include <regex>

void init(){
	initSymbolTable();
	initCompareTable();
}

int main(int argc, char **argv){
	init();
	if (argc < 2){
		std::cerr << "Error: Did not declare file name" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string asmFile = argv[1];

	std::ifstream input(asmFile);
	std::regex reg(".asm");
	
	std::string hackFile = std::regex_replace(asmFile, reg, ".hack");
	
	std::ofstream output(hackFile);

	pass1(input);

	input.clear();
	input.seekg(0);

	pass2(input);

	translate(output);
	
	input.close();
	output.close();

	exit(EXIT_SUCCESS);


}
