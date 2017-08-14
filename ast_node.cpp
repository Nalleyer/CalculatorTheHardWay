//
// Created by nalle on 8/1/2017.
//

#include "ast_node.h"

ASTOp::ASTOp(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : mLeft(left)
    , mRight(right)
{
}

size_t ASTNode::getLine()
{
    return mLine;
}

size_t ASTNode::getColumn()
{
    return mColumn;
}

ASTVar::ASTVar(std::string &&varName)
    : mVarName(std::move(varName))
{
}

ASTVar::ASTVar(const std::string &varName)
    : mVarName(varName)
{
}

ASTNum::ASTNum(std::string &&valueStr)
    : mValueStr(std::move(valueStr))
{
}

ASTNum::ASTNum(const std::string &valueStr)
    : mValueStr(valueStr)
{
}


ASTAssign::ASTAssign(std::shared_ptr<ASTVar> left, std::shared_ptr<ASTExp> right)
    : mLeft(left)
    , mRight(right)
{
}

ASTAdd::ASTAdd(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : ASTOp(left, right)
{
}

ASTDiv::ASTDiv(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : ASTOp(left, right)
{

}

ASTMul::ASTMul(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
   : ASTOp(left, right)
{

}

ASTSub::ASTSub(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
   : ASTOp(left, right)
{

}
