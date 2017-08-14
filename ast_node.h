//
// Created by nalle on 8/1/2017.
//
#pragma once

#include <memory>
#include "ast_visitor.h"

class Parser;

/* with a visitor interface */
class ASTNode
{
public:
    //! TODO: after completing visitor, enable this code.
    //virtual void accept(std::weak_ptr<ASTVisitor> visitor) = 0;
    ASTNode(void) = default;
    virtual ~ ASTNode(void) = default;

    size_t getLine(void);
    size_t getColumn(void);

    friend class Parser;

protected:
    size_t mLine;
    size_t mColumn;
};

class ASTExp : public ASTNode
{
public:
    ASTExp(void) = default;
    virtual ~ ASTExp(void) = default;
};

class ASTOp : public ASTExp
{
public:
    ASTOp(void) = default;
    ASTOp(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTOp(void) = default;

protected:
    std::shared_ptr<ASTExp> mLeft;
    std::shared_ptr<ASTExp> mRight;
};

class ASTAdd : public ASTOp
{
public:
    ASTAdd(void) = default;
    ASTAdd(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTAdd(void) = default;
};

class ASTSub : public ASTOp
{
public:
    ASTSub(void) = default;
    ASTSub(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTSub(void) = default;
};

class ASTMul : public ASTOp
{
public:
    ASTMul(void) = default;
    ASTMul(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTMul(void) = default;
};

class ASTDiv : public ASTOp
{
public:
    ASTDiv(void) = default;
    ASTDiv(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTDiv(void) = default;
};

class ASTVar : public ASTExp
{
public:
    ASTVar(void) = default;
    ASTVar( const std::string &varName );
    ASTVar( std::string &&varName);
    virtual ~ ASTVar(void) = default;

private:
    std::string mVarName;
};

class ASTNum : public ASTExp
{
public:
    ASTNum(void) = default;
    ASTNum( const std::string &valueStr);
    ASTNum( std::string &&valueStr);
    virtual ~ ASTNum(void) = default;

protected:
    std::string mValueStr;
};


class ASTAssign: public ASTNode
{
public:
    ASTAssign(void) = default;
    ASTAssign( std::shared_ptr<ASTVar> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTAssign(void) = default;

protected:
    std::shared_ptr<ASTVar> mLeft;
    std::shared_ptr<ASTExp> mRight;
};
