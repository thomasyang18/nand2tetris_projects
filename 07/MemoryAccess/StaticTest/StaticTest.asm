// push constant 111
@111
D=A
@0
A=M
M=D
@0
M=M+1
// push constant 333
@333
D=A
@0
A=M
M=D
@0
M=M+1
// push constant 888
@888
D=A
@0
A=M
M=D
@0
M=M+1
// pop static 8
@StaticTest.8
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
// pop static 3
@StaticTest.3
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
// pop static 1
@StaticTest.1
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
// push static 3
@StaticTest.3
D=M
@0
A=M
M=D
@0
M=M+1
// push static 1
@StaticTest.1
D=M
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
// push static 8
@StaticTest.8
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
