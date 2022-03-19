#include "Translator.h"
#include "SymbolTable.h"

#include<regex>
#include<map>

#define COMPARE_TABLE_FILE "compare_table.txt"


void InstructionA::printToFile(std::ofstream& input){

}

void InstructionC::printToFile(std::ofstream& input){

}

InstructionA::InstructionA(int x){
	value = x;	
}

InstructionA::InstructionA(std::string s){
	value = getSymbol(s);	
}

static std::string jmpArray[8] = {"null, JGT, JEQ, JGE, JLT, JNE, JLE, JMP"};

int getJump(std::string s){
	for (int i = 0; i < 8; i++) if (s == jmpArray[i]) return i;
	return 0;
}

static std::string destOptions[3] = {"M", "D", "A"};

int getDest(std::string s){
	int ans = 0;
	for (int i = 0; i < 3; i++){
		ans += (s.find(destOptions[3]) != std::string::npos) & (1<<i);
	}

	return ans;
}

std::map<std::string, int> compareTable;

void initCompareTable(){
	std::ifstream input(COMPARE_TABLE_FILE);
	
	std::string s, value;
	while (input >> s >> value){
		compareTable[s] = std::stoi(value, nullptr, 2);
	}
}

int getCmp(std::string s){
	int ans = 0;
	// If S uses M, then a =1
	ans += (s.find("M") != std::string::npos) & (1<<6);
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

	if (hasEq and hasBreak){
		// des = cmp; jmp
		std::string pt1 = s.substr(0,s.find("="));
		std::string pt2 = s.substr(s.find("="), s.find(";"));
		std::string pt3 = s.substr(s.find(";"));

		dest = getDest(pt1);
		control = getCmp(pt2);
		jmp = getJump(pt3);
	}
	else if (hasEq){
		//dest = cmp
		std::string pt1 = s.substr(0, s.find("="));
		std::string pt2 = s.substr(s.find("="));

		dest = getDest(pt1);
		control = getCmp(pt2);
	}
	else if (hasBreak){
		// cmp; jmp
		std::string pt1 = s.substr(0, s.find(";"));
		std::string pt2 = s.substr(s.find(";"));

		control = getCmp(pt1);
		jmp = getJump(pt2);
	}
	else{
		std::cerr << "Invalid InstructionC: " << s << std::endl;
		exit(EXIT_FAILURE);
	}	
}
