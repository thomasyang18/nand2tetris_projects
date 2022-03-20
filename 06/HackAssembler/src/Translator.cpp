#include "Translator.h"
#include "SymbolTable.h"

#include<regex>
#include<map>
#include <bitset>
#include <string>
#include <sstream>



void InstructionA::printToFile(std::ofstream& output){
	std::bitset<16> result = value;
	output << result << '\n';
}

void InstructionC::printToFile(std::ofstream& output){
	std::bitset<16> result = (7<<13) + (control<<6) + (dest<<3) + jmp;
	output << result << '\n';
}

InstructionA::InstructionA(int x){
	value = x;
	//std::cerr << "This integer instruction has value " << value << std::endl;
}

InstructionA::InstructionA(std::string s){
	value = getSymbol(s);
	//std::cerr << "This string instruction has value " << value << std::endl;	
}

std::string jmpArray[8] = {"null", "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};

int getJump(std::string s){
	for (int i = 0; i < 8; i++) if (s == jmpArray[i]) return i;
	
	//std::cerr << jmpArray[7] << " " << s << std::endl;

	std::cerr << "Not a valid jump; assuming " << s << " is zero" << std::endl;
	
	return 0;
}

std::string destOptions[3] = {"M", "D", "A"};

int getDest(std::string s){
	int ans = 0;
	for (int i = 0; i < 3; i++){
		if(s.find(destOptions[i]) != std::string::npos) ans+= (1<<i);
	}

	return ans;
}

std::map<std::string, int> compareTable;

std::string compare_table_string =
"0 101010 "
"1 111111 " 
"-1 111010 " 
"D 001100 " 
"A 110000 " 
"!D 001101 " 
"!A 110001 " 
"-D 001111 " 
"-A 110011 " 

"D+1 011111 " 
"1+D 011111 " 

"A+1 110111 " 
"1+A 110111 " 

"D-1 001110 " 
"A-1 110010 " 

"D+A 000010 " 
"A+D 0000100 " 

"D-A 010011 "
"A-D 000111 "

"D&A 000000 "
"A&D 000000 "

"D|A 010101 "
"A|D 010101 ";

void initCompareTable(){
	std::istringstream input(compare_table_string);

	std::string s, value;
	
	while (input >> s >> value){
		compareTable[s] = std::stoi(value, nullptr, 2);
	}
}

int getCmp(std::string s){
	int ans = 0;
	// If S uses M, then a =1
	if (s.find("M") != std::string::npos) ans += (1<<6);
	std::regex reg("M");
	s = std::regex_replace(s, reg, "A");
	
	if (compareTable.find(s) == compareTable.end()){
		std::cerr << "Compare Token " << s << " unknown" << std::endl;
		exit(EXIT_FAILURE);
	}

	int lowerBits = compareTable[s];	

	return ans+lowerBits;
}


InstructionC::InstructionC(std::string s){
	// Parse it into dest = cmp; jump
	// Only a few types of statements really allowed:
	// dest = cmp statement 
	// dest = cmp; jmp statement
	// cmp; jmp statement
	
	//Any other interpretation is flawed and must return an error

	bool hasEq = s.find("=") != std::string::npos;
	bool hasBreak = s.find(";") != std::string::npos;
	jmp = dest = control = 0;

	//std::cerr << "Instruction " << s << ", " << hasEq << " " << hasBreak << std::endl;

	if (hasEq and hasBreak){
		// des = cmp; jmp
		std::string pt1 = s.substr(0,s.find("="));
		std::string pt2 = s.substr(s.find("=")+1, s.find(";"));
		std::string pt3 = s.substr(s.find(";")+1);

		dest = getDest(pt1);
		control = getCmp(pt2);
		jmp = getJump(pt3);
	}
	else if (hasEq){
		//dest = cmp
		std::string pt1 = s.substr(0, s.find("="));
		std::string pt2 = s.substr(s.find("=")+1);

		dest = getDest(pt1);
		control = getCmp(pt2);
	}
	else if (hasBreak){
		// cmp; jmp
		std::string pt1 = s.substr(0, s.find(";"));
		std::string pt2 = s.substr(s.find(";")+1);

		control = getCmp(pt1);
		jmp = getJump(pt2);
	}
	else{
		std::cerr << "Invalid InstructionC: " << s << std::endl;
		exit(EXIT_FAILURE);
	}	
}
