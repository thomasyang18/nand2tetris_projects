// push constant 3
@3
D=A
@0
A=M
M=D
@0
M=M+1
// pop static 50
@static_block.50
D=A
@0
M=M-1
A=M
A=M
D=A-D
A=D-A
D=D-A
A=-A
M=D
