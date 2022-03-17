// This verification program was created because
// the authors expected you to implement multiplication the naive way
// (a*b = a+a+a+a... b times) instead of implementing
// multiplication the correct way (the way one can verify this is by checking 
// the Mult.tst file, and seeing that the ticktoks scale with A and B inputs, (thus making the complexity O(N)),
// whereas multiplication should take O(log(N)), where N is 2^n, where n number of bits

// Thus, we create several large test cases such that a, b >= 0 and a*b <= 32k.
#include <stdio.h>
#include <stdlib.h>

#define TST_LOAD_STRING "load Mult.asm,\noutput-file MultGood.out,\n output-list RAM[2]\%D2.6.2;\n" 


int main(){
	FILE *tst = fopen("MultGood.tst", "w");
	FILE *cmp = fopen("MultGood.cmp", "w");
	
	fprintf(tst, TST_LOAD_STRING);
	srand(30);
	int num_tests = 1;
	int cap = 32000;
	int maxX = 1000;
	int ticks = 16*30+10;
	for (int i = 0; i < num_tests; i++){
		int x = rand()%maxX;
		int rem = cap/x;
		int y = rand()%rem;
		fprintf(tst, "set PC 0, \nset RAM[0] %i,\nset RAM[1] %i,\nrepeat %i {\nticktock;\n}\noutput;\n", x, y, ticks);
		fprintf(cmp, "%i\n", x*y);
	}
	
	fclose(tst);
	fclose(cmp);
}
