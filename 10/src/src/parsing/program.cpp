#include "program.hpp"
#include <iostream>

std::unique_ptr<Node> parseClass(){
    INIT("class")

    force_next_token(res,keyword, "class");
    
    PUSH_REC(parseClassName())

    force_next_token(res,symbol, "{");

    while (try_match_token(keyword, "static") || try_match_token(keyword, "field")) PUSH_REC(parseClassVarDec())
    while (try_match_token(keyword, "constructor") || try_match_token(keyword, "function") || 
                        try_match_token(keyword, "method")) 
            PUSH_REC(parseSubroutineDec())

    force_next_token(res,symbol, "}");
    return res;    
}

std::unique_ptr<Node> parseClassVarDec(){
    INIT("classVarDec")

    if (try_force_token(res, keyword, "static") || force_next_token(res, keyword, "field"));
    PUSH_REC(parseType())
    PUSH_REC(parseVarName())
    while (try_force_token(res, symbol, ",")) PUSH_REC(parseVarName())
    force_next_token(res, symbol, ";");
    return res;
}

std::unique_ptr<Node> parseType(){
    INIT("type")

    if (try_force_token(res, keyword, "int") || try_force_token(res, keyword, "char") || try_force_token(res, keyword, "boolean"));
    else PUSH_REC(parseClassName())

    return res;
}

std::unique_ptr<Node> parseSubroutineDec(){
    INIT("subroutineDec")

    if (try_force_token(res, keyword, "constructor") || try_force_token(res, keyword, "function") || force_next_token(res, keyword, "method"));
    
    if (try_force_token(res, keyword, "void"));
    else PUSH_REC(parseType())

    PUSH_REC(parseSubroutineName())
    force_next_token(res, symbol, "(");
    PUSH_REC(parseParameterList())
    force_next_token(res, symbol, ")");
    PUSH_REC(parseSubroutineBody())    

    return res;
}

std::unique_ptr<Node> parseParameterList(){
    INIT("parameterList")
    // first set of type
    bool works = try_force_token(res, keyword, "int") || try_force_token(res, keyword, "char") || try_force_token(res, keyword, "boolean");
    if (!works){
        // try match token
        if (try_match_token(identifier)) PUSH_REC(parseType())
        // No else here, because empty is legal
    }
    if (works){
        // also enforce varName
        if (try_match_token(identifier)) PUSH_REC(parseType())
        else parse_error();
    }
    if (works){
        while (try_force_token(res, symbol, ",")){
            bool works = try_force_token(res, keyword, "int") || try_force_token(res, keyword, "char") || try_force_token(res, keyword, "boolean");
            if (!works){
                // try match token
                if (try_match_token(identifier)) PUSH_REC(parseType())
                else parse_error(); 
                // Required to have something here
            }
            if (try_match_token(identifier)) PUSH_REC(parseType())
            else parse_error();
        }
    }

    return res;
}

std::unique_ptr<Node> parseSubroutineBody(){
    INIT("subroutineBody")
    force_next_token(res, symbol, "{");
    while (try_match_token(keyword, "var")) PUSH_REC(parseVarName());
    PUSH_REC(parseStatements())
    force_next_token(res, symbol, "}");
    
    return res;
}

std::unique_ptr<Node> parseVarDec(){
    INIT("varDec")
    force_next_token(res, keyword, "var");
    PUSH_REC(parseType())
    PUSH_REC(parseVarName())
    while (try_match_token(symbol, ",")){
        force_next_token(res,symbol, ",");
        PUSH_REC(parseType())
        PUSH_REC(parseVarName())
    }
    force_next_token(res, symbol, ";");
    return res;
}

std::unique_ptr<Node> parseClassName(){
    INIT("className")
    force_next_token(res, identifier);
    return res;
}


std::unique_ptr<Node> parseSubroutineName(){
    INIT("subroutineName")
    force_next_token(res, identifier);
    return res;
}


std::unique_ptr<Node> parseVarName(){
    INIT("varName")
    force_next_token(res, identifier);
    return res;
}