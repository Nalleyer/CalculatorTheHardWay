//
// Created by nalle on 8/1/2017.
//

#include "ast_node.h"

ASTOp::ASTOp(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : mLeft(left)
    , mRight(right)
{
}

ASTAdd::ASTAdd(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right)
    : ASTOp(left, right)
{
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

