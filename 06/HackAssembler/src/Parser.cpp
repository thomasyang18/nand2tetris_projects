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

			addGotoLabel(label, line--); // subtracting line because the \n will include this line

			readingLabel = false;
			
			label = "";
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

// Grammar stuff

ASTNode *head;

void pass2(std::ifstream& input){
	//Build the AST tree according to grammar specification
	ASTNode *end = nullptr;
	head = end;
	ASTNode *prev = nullptr;
	std::string variable;
	
	// We assume that instructions have no spaces
	
	while (input >> variable){
		//std::cerr << "Just read " << variable << std::endl;
		if (variable.size() <= 1) continue;
		if (variable[0] == '/' and variable[1] == '/'){
			// Ignore until newline
			char cur;
			while (input.get(cur) and cur != '\n');
			continue;
		}
		
		if (variable[0] == '@') {
		//	std::cerr << "adding A instruction " << std::endl;
			variable = variable.substr(1);
			if (variable[0] >= '0' and variable[0] <='9'){
				end = new InstructionA(stoi(variable));
			}	
			else{
				
				addSymbol(variable);
				end = new InstructionA(variable);
			}
				
		}
		else if (variable[0] == '(') {
			// Just a label; we processed this
			//std::cerr << "Label here " << std::endl;
			continue;
		}
		else{
			// Assume it's a C instruction
		//	std::cerr << "adding C instruction " << std::endl;
			end = new InstructionC(variable);
		}
	

		if (!prev){
			head = end;
		}
		if (prev) prev->next = end;	
		prev = end;
		end=end->next;
			
		
	}
}

void translate(std::ofstream& output){
	while (head){
		head->printToFile(output);
		head = head->next;	
	}
}

