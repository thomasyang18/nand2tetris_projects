# Grammar SPECIFICATION

program := (ins_list) EOF
  
ins_list := (insA) \n (ins_list) | (insC) \n (ins_list) | (comment) \n (ins_list)\eps
  
insA := @(variable) | @(number)

(variables cannot start with digits, numbers must contain only digits)

insC := (string)(delim)(string) | (string)(delim)(string)(delim)(string)

comment := //<string>
