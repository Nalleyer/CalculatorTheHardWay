//
// Created by nalle on 8/1/2017.
//
#pragma once

#include <memory>
#include "ast_visitor.h"

/* with a visitor interface */
class ASTNode
{
public:
    virtual void accept(std::weak_ptr<ASTVisitor> visitor) = 0;
    ASTNode() = default;
    virtual ~ ASTNode() = default;
};

class ASTExp : public ASTNode
{
    ASTExp() = default;
    virtual ~ ASTExp() = default;
};

class ASTOp : public ASTExp
{
public:
    ASTOp() = default;
    ASTOp(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTOp() = default;

protected:
    std::shared_ptr<ASTExp> mLeft;
    std::shared_ptr<ASTExp> mRight;
};

class ASTAdd : public ASTOp
{
public:
    ASTAdd() = default;
    ASTAdd(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTAdd() = default;
};

class ASTSub : public ASTOp
{
public:
    ASTSub() = default;
    ASTSub(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTSub() = default;
};

class ASTMul : public ASTOp
{
public:
    ASTMul() = default;
    ASTMul(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTMul() = default;
};

class ASTDiv : public ASTOp
{
public:
    ASTDiv() = default;
    ASTDiv(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTDiv() = default;
};


