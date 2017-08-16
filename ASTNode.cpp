//
// Created by nalle on 8/1/2017.
//

#include "ASTNode.h"
#include "ASTVisitor.h"


void ASTNode::accept(ASTVisitor &visitor)
{
    visitor.visit(shared_from_this());
}

void ASTExp::accept(ASTVisitor &visitor)
{
    visitor.visit(shared_from_this());
}

size_t ASTNode::getLine()
{
    return mLine;
}

size_t ASTNode::getColumn()
{
    return mColumn;
}

ASTOp::ASTOp(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : mLeft(left)
    , mRight(right)
{
}

std::shared_ptr<ASTExp> ASTOp::getLeft(void)
{
    return mLeft;
}

std::shared_ptr<ASTExp> ASTOp::getRight(void)
{
    return mRight;
}

void ASTOp::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTOp>(shared_from_this()));
}

ASTVar::ASTVar(std::string &&varName)
    : mVarName(std::move(varName))
{
}

ASTVar::ASTVar(const std::string &varName)
    : mVarName(varName)
{
}

std::string ASTVar::getVarName(void)
{
    return mVarName;
}

void ASTVar::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTVar>(shared_from_this()));
}

ASTNum::ASTNum(std::string &&valueStr)
    : mValueStr(std::move(valueStr))
{
}

ASTNum::ASTNum(const std::string &valueStr)
    : mValueStr(valueStr)
{
}

std::string ASTNum::getValueStr(void)
{
    return mValueStr;
}

void ASTNum::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTNum>(shared_from_this()));
}

ASTAssign::ASTAssign(std::shared_ptr<ASTVar> left, std::shared_ptr<ASTExp> right)
    : mLeft(left)
    , mRight(right)
{
}

std::shared_ptr<ASTVar> ASTAssign::getLeft(void)
{
    return mLeft;
}

std::shared_ptr<ASTExp> ASTAssign::getRight(void)
{
    return mRight;
}

void ASTAssign::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTAssign>(shared_from_this()));
}

ASTAdd::ASTAdd(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : ASTOp(left, right)
{
}

void ASTAdd::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTAdd>(shared_from_this()));
}

ASTDiv::ASTDiv(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : ASTOp(left, right)
{

}

void ASTDiv::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTDiv>(shared_from_this()));
}

ASTMul::ASTMul(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
   : ASTOp(left, right)
{

}

void ASTMul::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTMul>(shared_from_this()));
}

ASTSub::ASTSub(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
   : ASTOp(left, right)
{

}

void ASTSub::accept(ASTVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<ASTSub>(shared_from_this()));
}

