#include "statements.hpp"

std::unique_ptr<Node> parseStatements(){
    INIT("statements")
    while (try_match_token(keyword, "let") || 
    try_match_token(keyword, "if") ||
    try_match_token(keyword, "while") || 
    try_match_token(keyword, "do") || 
    try_match_token(keyword, "return"))
    PUSH_REC(parseStatement());
    return res;
}

std::unique_ptr<Node> parseStatement(){
    INIT("statement")
    if (try_match_token(keyword, "let")) PUSH_REC(parseLetStatement())
    else if (try_match_token(keyword, "if")) PUSH_REC(parseIfStatement())
    else if (try_match_token(keyword, "while")) PUSH_REC(parseWhileStatement())
    else if (try_match_token(keyword, "do")) PUSH_REC(parseDoStatement())
    else if (try_match_token(keyword, "return")) PUSH_REC(parseReturnStatement())
    return res;
}

std::unique_ptr<Node> parseLetStatement(){
    INIT("letStatement")
    force_next_token(res, keyword, "let");
    PUSH_REC(parseVarName())
    if (try_match_token(keyword, "[")){
        force_next_token(res, symbol, "[");
        PUSH_REC(parseExpression())
        force_next_token(res, symbol, "]");
    }
    force_next_token(res, symbol, "=");
    PUSH_REC(parseExpression());
    force_next_token(res, symbol, ";");
    return res;
}

std::unique_ptr<Node> parseIfStatement(){
    INIT("ifStatement")

    force_next_token(res, keyword, "if");
    force_next_token(res, symbol, "(");
    PUSH_REC(parseExpression())
    force_next_token(res, symbol, ")");
    force_next_token(res, symbol, "{");
    PUSH_REC(parseStatements())
    force_next_token(res, symbol, "}");

    if (try_match_token(symbol, "else")){
        force_next_token(res, symbol, "else");
        force_next_token(res, symbol, "{");
        PUSH_REC(parseStatements())
        force_next_token(res, symbol, "}");
    }

    return res;
}

std::unique_ptr<Node> parseWhileStatement(){
    INIT("whileStatement")
    
    force_next_token(res, keyword, "while");
    force_next_token(res, symbol, "(");
    PUSH_REC(parseExpression())
    force_next_token(res, symbol, ")");
    force_next_token(res, symbol, "{");
    PUSH_REC(parseStatements())
    force_next_token(res, symbol, "}");

    return res;
}

std::unique_ptr<Node> parseDoStatement(){
    INIT("doStatement")
    force_next_token(res, keyword, "do");
    PUSH_REC(parseSubroutineCall())
    return res;
}

std::unique_ptr<Node> parseReturnStatement(){
    INIT("returnStatement")
    force_next_token(res, keyword, "return");
    
    // Should be using first set of term, but just check if there's semicolon or not. If there isn't semicolon, assume term.
    if (try_force_token(res, symbol, ";")); // stop
    else{
        PUSH_REC(parseExpression())
        force_next_token(res, symbol, ";");
    }
    
    return res;
}