//
// Created by nalle on 8/11/2017.
//

#pragma once

#include "ast_node.h"
#include "lexer.h"
#include <memory>
#include <vector>

class Parser
{
    using P_AST = std::shared_ptr<ASTNode>;
    using P_Exp = std::shared_ptr<ASTExp>;
    using P_Var = std::shared_ptr<ASTVar>;
    using P_Num = std::shared_ptr<ASTNum>;

    using Prog = std::vector<P_AST>;
    using TokenList = std::vector<Token>;
public:
    Parser() = default;
    ~ Parser() = default;
    void parse( TokenList const &tokenList );
    Parser::Prog getProg(void);

private:
    Parser::Prog mResult;

    void nextToken(TokenList const &tokenList, size_t &i);
    Token unsafePeekNext(TokenList const &tokenList, size_t &i);

    P_AST getLine(TokenList const &tokenList, size_t &i);

    P_AST getAssign(TokenList const &tokenList, size_t &i);

    P_Exp getExp(TokenList const &tokenList, size_t &i);

    P_Exp getTerm(TokenList const &tokenList, size_t &i);
    P_Exp getFactor(TokenList const &tokenList, size_t &i);

    P_Num getNum(TokenList const &tokenList, size_t &i);
    P_Var getVar(TokenList const &tokenList, size_t &i);

    Token getOpAddOrSub(TokenList const &tokenList, size_t &i);
    Token getOpMulOrDiv(TokenList const &tokenList, size_t &i);

    void error(std::string const &info);
};


