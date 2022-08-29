#include "expressions.hpp"
#include <iostream>

std::unique_ptr<Node> parseExpression(){
    INIT("expression")
    PUSH_REC(parseTerm())
    while (/* try force op*/
        try_force_token(res, symbol, "+") ||
        try_force_token(res, symbol, "-") ||
        try_force_token(res, symbol, "*") ||
        try_force_token(res, symbol, "/") ||
        try_force_token(res, symbol, "&") ||
        try_force_token(res, symbol, "|") ||
        try_force_token(res, symbol, "<") ||
        try_force_token(res, symbol, ">") ||
        try_force_token(res, symbol, "=") 
    ) PUSH_REC(parseTerm())
    
    return res;
}

std::unique_ptr<Node> parseTerm(){
    INIT("term")

   // std::cout << "Yo " << glob_tok->get_cur_token().value << "\n";

    if (try_force_token(res, integerConstant));
    else if (try_force_token(res, stringConstant));
    else if (try_match_token(keyword, "true") || 
    try_match_token(keyword, "false") || 
    try_match_token(keyword, "null") || 
    try_match_token(keyword, "this") 
    ) PUSH_REC(parseKeywordConstant())
    else if (try_match_token(identifier)){
        // grammar moment
        // imagine if i just used an actual parser gen
        
        // optional array indexing
        if (glob_tok->get_ahead_token().value == "["){
            PUSH_REC(parseVarName())
            force_next_token(res, symbol, "[");
            PUSH_REC(parseExpression())
            force_next_token(res, symbol, "]");
        }
        // subroutine call,  
        // this is LL(2)! 
        else if (glob_tok->get_ahead_token().value == "{"){
            PUSH_REC(parseSubroutineCall())
        }
        else if (glob_tok->get_ahead_token().value == "."){
            // another way to get in is call method of class
            PUSH_REC(parseSubroutineCall()) 
        }
        else {
            // just var name
            PUSH_REC(parseVarName())
        }
    }
    else if (try_force_token(res, symbol, "(")){
        PUSH_REC(parseExpression())
        force_next_token(res, symbol, ")");
    }
    else if (try_match_token(symbol, "-") || try_match_token(symbol, "~")){
        PUSH_REC(parseUnaryOp())
        PUSH_REC(parseTerm())
    }


    return res;
}

std::unique_ptr<Node> parseSubroutineCall(){
    INIT("subroutineCall")
    // LL(2)!
    if (glob_tok->get_ahead_token().value == "("){
        PUSH_REC(parseSubroutineName())
        force_next_token(res, symbol, "(");
        PUSH_REC(parseExpressionList())
        force_next_token(res, symbol, ")");
    } 
    else if (glob_tok->get_ahead_token().value == "."){
        
        // Deciding if it's a variable name or class name makes this not context free
        //(under the assumption that we actually care about the enclosing braces in the xml)
        // i don't know if we can get away with this if we didn't have to care

        if (class_names.count(glob_tok->get_cur_token().value)) {
            PUSH_REC(parseClassName())
        }
        else{
            PUSH_REC(parseVarName())
        }


        force_next_token(res, symbol, ".");
        PUSH_REC(parseSubroutineName())
        force_next_token(res, symbol, "(");
        PUSH_REC(parseExpressionList())
        force_next_token(res, symbol, ")");
    }
    else parse_error();
    return res;
}

std::unique_ptr<Node> parseExpressionList(){
    INIT("expressionList")
    // first set for term

    if (try_match_token(integerConstant) ||
    try_match_token(stringConstant) ||
    try_match_token(keyword, "true") || 
    try_match_token(keyword, "false") || 
    try_match_token(keyword, "null") || 
    try_match_token(keyword, "this") || 
    try_match_token(identifier) ||
    try_match_token(symbol, "(") || 
    try_match_token(symbol, "-") || try_match_token(symbol, "~")
    ) {
        PUSH_REC(parseExpression())
        while (try_force_token(res, symbol, ",")) PUSH_REC(parseExpression())
    }
    
    return res;
}

std::unique_ptr<Node> parseOp(){
    INIT("op")

        try_force_token(res, symbol, "+") ||
        try_force_token(res, symbol, "-") ||
        try_force_token(res, symbol, "*") ||
        try_force_token(res, symbol, "/") ||
        try_force_token(res, symbol, "&") ||
        try_force_token(res, symbol, "|") ||
        try_force_token(res, symbol, "<") ||
        try_force_token(res, symbol, ">") ||
        force_next_token(res, symbol, "=") ;


    return res;
}

std::unique_ptr<Node> parseUnaryOp(){
    INIT("unaryOp")

    try_force_token(res, symbol, "-") || 
    force_next_token(res, symbol, "~"); 
    
    return res;
}

std::unique_ptr<Node> parseKeywordConstant(){
    INIT("keywordConstant")

    try_force_token(res, keyword, "true") ||
    try_force_token(res, keyword, "false") ||
    try_force_token(res, keyword, "null") ||
    force_next_token(res, keyword, "this");
    
    return res;
}