#include "Parser.h"
#include "Translator.h"
#include "SymbolTable.h"
#include<set>

#define ERR(X) std::cerr << (X) << std::endl, exit(EXIT_FAILURE);

std::set<char> whitespace = {'/', ' ', '\t', '\r', '\n', '\v', '\f'}; // For the sake of this, '/' is whitespace

void pass1(std::ifstream& input){
	// Every newline means a new line number, unless the previous character was also newline then exit
	char ch;
	char prev = '\0';
	bool readingLabel = false; //iff we hit a '(' character
	std::string label;
	int line = 0;
	bool ignore = false;
	bool characters = false;

	while (input.get(ch)){
	
		if (ch == '\n'){
			ignore = false;
			if (readingLabel) ERR("Stopped reading label mid-way");
			if (characters) line++;
			characters = false;
			goto end;
		}
		if (ignore) goto end;

		characters |= whitespace.find(ch) == whitespace.end();

		if (ch == '('){
			if (readingLabel) ERR("Already reading label");
			readingLabel = true;
		}
		else if (ch == ')'){
			if (!readingLabel) ERR("Unmatched closing parentheses");
				
			if (label.size() == 0) ERR("Label is null");
				
			if (label[0] >= '0' and label[0] <= '9') ERR("Labels cannot start with numbers");

			addGotoLabel(label, line);

			readingLabel = false;
		}
		 
		else if (ch == prev and ch == '/'){
			// Comment; ignore everything until newline
			ignore = true;
		}
		else if (readingLabel) label += ch;

		end:
	//	std::cout << ch << " " << ignore << " " << readingLabel << " " << std::endl;
		prev = ch;
	}	
}

void pass2(std::ifstream& input){
	
}

void translate(std::ofstream& output){
	
}

