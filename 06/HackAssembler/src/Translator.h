#ifndef __TRANSLATOR_HEADER_
#define __TRANSLATOR_HEADER_

#include<string>
#include<iostream>
#include<fstream>

class ASTNode{
	public:
		ASTNode *next;
		virtual void printToFile(std::ofstream& output) = 0;
};

class InstructionA: public ASTNode{
	public:
		// methods to convert X into a 15 bit integer
		InstructionA(int x);
		InstructionA(std::string s);
		void printToFile(std::ofstream& output) override;
	private:
		int value; // label value
};

class InstructionC: public ASTNode{
	public:
		InstructionC(std::string s);
		void printToFile(std::ofstream& output) override;
	
	private:
		int jmp, dest, control;
};

void initCompareTable();

#endif
