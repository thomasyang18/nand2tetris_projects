#ifndef __AST_NODE_
#define __AST_NODE_

#include<string>
#include<iostream>
#include<fstream>

class ASTNode{
	public:
		// prints 0 + 15 bit integer to the stream
		void printToFile(std::ofstream);
	protected:
		ASTNode *next;
	
};

class InstructionA: public ASTNode{
	public:
		// methods to convert X into a 15 bit integer
		InstructionA(int x);
		InstructionA(std::string s);
	private:
		int value; // label value
};

class InstructionC: public ASTNode{
	public:
		InstructionC(std::string s);
	private:
		int jmp, dest, control;
};

#endif
