// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

// Probably shouldn't modify the inputs

// Iteratively:
// Ans = 0, TR0 = R0
// For 0 <= i <= 15:
// 	Temp = TR0 if R1[i] == 1, else Temp = 0
//	Ans += temp
// 	TR0 = TR0 + TR0
// R2 = Ans

// PseudoCode:
// Ans = 0, TR0 = R0
// Mask = 1
// LOOP:
// 	If (r1 & mask > 0) goto INCR
//	TESTLOOP	
// 
// INCR:
// Ans = Ans + TR0
// goto TESTLOOP
// 
// TESTLOOP: 
// mask = mask+mask
// TR0 = TR0 + TR0
// If mask == 0 goto END
// goto LOOP
//
// END:
// goto END 

// Bad practice to mess with R0, R1, and R2 (maybe not R2, since return is always in EAX) directly in memory. 
// 10 from initialization, 4 from end
// is it possible to do this with only 11 instructions per loop?
// right now i have 24 instructions per loop 
// 

// shit code to see if it passes test cases


@R2
M=0

@i
M=0

(LOOP)
	@R1
	M=M-1
	D=M+1

	@END
	D; JEQ	

	@R0
	D=M
	@R2
	M=D+M
	
	@LOOP
	0; JMP
	
(END)
	@END
	0; JMP

	












