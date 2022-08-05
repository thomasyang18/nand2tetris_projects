// push argument 1
@2
D=M
@1
A=D+A
D=M
@0
A=M
M=D
@0
M=M+1
// pop pointer 1
@3
D=A
@1
D=D+A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
// push constant 0
@0
D=A
@0
A=M
M=D
@0
M=M+1
// pop that 0
@4
D=M
@0
D=D+A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
// push constant 1
@1
D=A
@0
A=M
M=D
@0
M=M+1
// pop that 1
@4
D=M
@1
D=D+A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
// push argument 0
@2
D=M
@0
A=D+A
D=M
@0
A=M
M=D
@0
M=M+1
// push constant 2
@2
D=A
@0
A=M
M=D
@0
M=M+1
// sub
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
A=M
D=A-D
@0
A=M
M=D
@0
M=M+1
// pop argument 0
@2
D=M
@0
D=D+A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
// label MAIN_LOOP_START
(MAIN_LOOP_START)
// push argument 0
@2
D=M
@0
A=D+A
D=M
@0
A=M
M=D
@0
M=M+1
// if-goto COMPUTE_ELEMENT
@0
M=M-1
A=M
D=M
@COMPUTE_ELEMENT
D;JGT
// goto END_PROGRAM
@END_PROGRAM
0;JMP
// label COMPUTE_ELEMENT
(COMPUTE_ELEMENT)
// push that 0
@4
D=M
@0
A=D+A
D=M
@0
A=M
M=D
@0
M=M+1
// push that 1
@4
D=M
@1
A=D+A
D=M
@0
A=M
M=D
@0
M=M+1
// add
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
A=M
D=D+A
@0
A=M
M=D
@0
M=M+1
// pop that 2
@4
D=M
@2
D=D+A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
// push pointer 1
@3
D=A
@1
A=D+A
D=M
@0
A=M
M=D
@0
M=M+1
// push constant 1
@1
D=A
@0
A=M
M=D
@0
M=M+1
// add
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
A=M
D=D+A
@0
A=M
M=D
@0
M=M+1
// pop pointer 1
@3
D=A
@1
D=D+A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
// push argument 0
@2
D=M
@0
A=D+A
D=M
@0
A=M
M=D
@0
M=M+1
// push constant 1
@1
D=A
@0
A=M
M=D
@0
M=M+1
// sub
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
A=M
D=A-D
@0
A=M
M=D
@0
M=M+1
// pop argument 0
@2
D=M
@0
D=D+A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
// goto MAIN_LOOP_START
@MAIN_LOOP_START
0;JMP
// label END_PROGRAM
(END_PROGRAM)
