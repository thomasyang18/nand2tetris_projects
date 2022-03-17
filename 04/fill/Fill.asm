// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(START)
	@color
	M = 0

	@KBD
	D = M
	@SKIP
	D; JEQ
	
	@color
	M = -1

(SKIP)
// Fill in 1024 blocks the same color, so indices SCREEN to SCREEN+1023
	@8191
	D = A	
	@i
	M = D
(LOOP)
// Store SCREEN + i in a temporary variable
	@SCREEN
	D = A
	@i
	D = D+M
	@TEMP
	M = D

// D = color, @i, A = M, M = D
	@color
	D = M
	@TEMP
	A = M
	M = D

	@i
	M = M-1
	D = M	
	@LOOP
	D; JGE

	@START
	0; JMP
