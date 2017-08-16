//
// Created by nalle on 8/11/2017.
//

#include <iostream>
#include "Parser.h"

using std::cerr;

Parser::Prog Parser::getProg(void)
{
    return mResult;
}

void Parser::parse(std::vector<Token> const &tokenList)
{
    /* avoid multiple \n at first */
    size_t i = 0;
    for ( ; i < tokenList.size(); i ++)
    {
        if ( tokenList[i].mTokenType != TokenType::ENDL )
        {
            break;
        }
    }
    /* parse */
    while ( i < tokenList.size() )
    {
        mResult.emplace_back(getLine(tokenList, i));
        if ( i >= tokenList.size() )
        {
            return;
        }
        else
        {
            /* handle empty lines after a line */
            for ( ; i < tokenList.size(); i ++)
            {
                if ( tokenList[i].mTokenType != TokenType::ENDL )
                {
                    break;
                }
            }
        }
    }
}

Parser::P_AST Parser::getLine(const Parser::TokenList &tokenList, size_t &i)
{
    /* peek the 2th token
     * if it's '=', parse as assign
     * otherwise parse as exp
     */
    bool isAssign = false;
    if ( i + 1 < tokenList.size() && tokenList[i+1].mTokenType == TokenType::ASSIGN)
    {
        isAssign = true;
    }

    if ( isAssign )
    {
        return getAssign(tokenList, i);
    }
    else
    {
        return getExp(tokenList, i);
    }
}

Parser::P_AST Parser::getAssign(const Parser::TokenList &tokenList, size_t &i)
{
    auto astVar = getVar(tokenList, i);
    if ( tokenList[i].mTokenType == TokenType::ASSIGN )
    {
        nextToken(tokenList, i);
        auto astExp = getExp(tokenList, i);

        auto astAssign = std::make_shared<ASTAssign>(astVar, astExp);
        astAssign -> mLine = astVar -> mLine;
        astAssign -> mColumn = astVar -> mColumn;
        return astAssign;
    }
    else
    {
        error("expected '='");
    }
}

Parser::P_Exp Parser::getExp(const Parser::TokenList &tokenList, size_t &i)
{
    auto astTerm = getTerm(tokenList, i);
    /* end of term */
    if (        tokenList[i].mTokenType == TokenType::ENDL
            or tokenList[i].mTokenType == TokenType::RIGHT_PAR)
    {
        return astTerm;
    }
    if ( i+1 < tokenList.size() )
    {
        auto opToken = tokenList[i];
        if (        opToken.mTokenType == TokenType::ADD
                or  opToken.mTokenType == TokenType::SUB)
        {
            /* exp -> term +/- term */
            nextToken(tokenList, i);
            auto rightASTExp = getExp(tokenList, i);
            if ( opToken.mTokenType == TokenType::ADD)
            {
                auto astExp = std::make_shared<ASTAdd>(std::static_pointer_cast<ASTExp>(astTerm),
                                                       rightASTExp );
                astExp -> mLine = astTerm -> mLine;
                astExp -> mColumn = astTerm -> mColumn;
                return astExp;
            }
            else
            {
                auto astExp = std::make_shared<ASTSub>(std::static_pointer_cast<ASTExp>(astTerm),
                                                       rightASTExp );
                astExp -> mLine = astTerm -> mLine;
                astExp -> mColumn = astTerm -> mColumn;
                return astExp;
            }
        }
        else
        {
            /* exp -> term */
            return astTerm;
        }
    }
    else
    {
        error("reached the end of token list before finishing parsing");
    }
}

Parser::P_Exp Parser::getTerm(const Parser::TokenList &tokenList, size_t &i)
{
    auto astFactor = getFactor(tokenList, i);
    auto opToken = tokenList[i];
    if (        opToken.mTokenType == TokenType::MUL
                or  opToken.mTokenType == TokenType::DIV)
    {
        /* term -> factor muldiv factor */
        nextToken(tokenList, i);
        auto rightAstTerm = getTerm(tokenList, i);
        if ( opToken.mTokenType == TokenType::MUL)
        {
            auto astTerm = std::make_shared<ASTMul>(astFactor, rightAstTerm);
            astTerm -> mLine = astFactor -> mLine;
            astTerm -> mColumn = astFactor -> mColumn;
            return astTerm;
        }
        else
        {
            auto astTerm = std::make_shared<ASTDiv>(astFactor, rightAstTerm);
            astTerm -> mLine = astFactor -> mLine;
            astTerm -> mColumn = astFactor -> mColumn;
            return astTerm;
        }
    }
    else
    {
        return astFactor;
    }
}

Parser::P_Exp Parser::getFactor(const Parser::TokenList &tokenList, size_t &i)
{
    auto token  = tokenList[i];
    if ( token.mTokenType == TokenType::LEFT_PAR )
    {
        nextToken(tokenList, i);
        auto expNode = getExp(tokenList, i);
        if (tokenList[i].mTokenType == TokenType::RIGHT_PAR )
        {
            nextToken(tokenList, i);
            return expNode;
        }
        else
        {
            error("expected RIGHT_PAR !");
        }
    }
    else if ( token.mTokenType == TokenType::VAR )
    {
        return std::static_pointer_cast<ASTExp>(getVar(tokenList, i));
    }
    else if ( token.mTokenType == TokenType::NUMBER )
    {
        return std::static_pointer_cast<ASTExp>(getNum(tokenList, i));
    }
    else
    {
        error("expected VAR | NUMBER | (EXP) ");
    }
}

Token Parser::getOpAddOrSub(const Parser::TokenList &tokenList, size_t &i)
{
    auto token = tokenList[i];
    if ( token.mTokenType == TokenType::ADD || token.mTokenType == TokenType::SUB )
    {
        nextToken(tokenList, i);
        return tokenList[i];
    }
    else
    {
        error("expected ADD or SUB !");
    }
}

Token Parser::getOpMulOrDiv(const Parser::TokenList &tokenList, size_t &i)
{
    auto token = tokenList[i];
    if ( token.mTokenType == TokenType::MUL || token.mTokenType == TokenType::DIV )
    {
        nextToken(tokenList, i);
        return tokenList[i];
    }
    else
    {
        error("expected MUL or DIV !");
    }
}

Parser::P_Num Parser::getNum(TokenList const &tokenList, size_t &i)
{
    auto token = tokenList[i];
    if ( token.mTokenType == TokenType::NUMBER )
    {
        auto astNum = std::make_shared<ASTNum>(token.mValue);
        astNum -> mLine = token.mLine;
        astNum -> mColumn = token.mColumn;
        nextToken(tokenList, i);
        return astNum;
    }
    else
    {
        return nullptr;
    }
}

Parser::P_Var Parser::getVar(TokenList const &tokenList, size_t &i)
{
    auto token = tokenList[i];
    if ( token.mTokenType == TokenType::VAR)
    {
        auto astVar = std::make_shared<ASTVar>(token.mValue);
        astVar -> mLine = token.mLine;
        astVar -> mColumn = token.mColumn;
        nextToken(tokenList, i);
        return astVar;
    }
    else
    {
        error("expected VAR");
    }
}

void Parser::error(std::string const &info)
{
    cerr << info;
    exit(1);
}

void Parser::nextToken(const Parser::TokenList &tokenList, size_t &i)
{
    ++ i;
    if ( i == tokenList.size() )
    {
        error("reached the end of token list before finishing parsing");
    }
}

Token Parser::unsafePeekNext(const Parser::TokenList &tokenList, size_t &i)
{
    return tokenList[i+1];
}

