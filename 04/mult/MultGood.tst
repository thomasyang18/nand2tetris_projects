load Mult.asm,
output-file MultGood.out,
 output-list RAM[2]%D2.6.2;
set PC 0, 
set RAM[0] 533,
set RAM[1] 11,
repeat 490 {
ticktock;
}
output;
