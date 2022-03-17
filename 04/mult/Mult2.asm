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

// Loop version of mul that takes upwards of 400 tiktoks 

@0
D=A
@Ans
M=D

@mask
M=D+1

@R0
D=M
@TR0
M=D

(LOOP)
	@mask
	D=M
	@R1
	D=D&M
	
	@INCR
	D; JNE
	@TESTLOOP
	0;JMP

(INCR)
	@TR0
	D=M
	@Ans
	M=D+M

	@TESTLOOP
	0; JMP

(TESTLOOP)
	@mask
	D=M
	M=D+M
	@TR0
	D=M
	M=D+M
	
	@mask
	D=M

	@PRE_END
	D; JEQ
	@LOOP
	0; JMP

(PRE_END)
	@Ans
	D=M
	@R2
	M=D

(END)
	@END
	0; JMP

	













