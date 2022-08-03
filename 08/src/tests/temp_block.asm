// push constant 8
@8
D=A
@0
A=M
M=D
@0
M=M+1
// pop temp 3
@5
D=A
@3
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
