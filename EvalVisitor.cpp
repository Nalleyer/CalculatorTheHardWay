//
// Created by nalle on 8/15/2017.
//

#include "EvalVisitor.h"
#include <string>
#include <iostream>

using std::string;

string EvalVisitor::getResult()
{
    return mResultStr;
}

void EvalVisitor::visit(std::shared_ptr<ASTNode> node)
{
}

void EvalVisitor::visit(std::shared_ptr<ASTExp> node)
{
}

void EvalVisitor::visit(std::shared_ptr<ASTOp> node)
{
}

void EvalVisitor::visit(std::shared_ptr<ASTAdd> node)
{
    node->getRight()->accept(*this);
    auto right = mTmpRes;
    node->getLeft()->accept(*this);
    mTmpRes += right;
    mResultStr = std::to_string(mTmpRes);
}

void EvalVisitor::visit(std::shared_ptr<ASTSub> node)
{
    node->getRight()->accept(*this);
    auto right = mTmpRes;
    node->getLeft()->accept(*this);
    mTmpRes -= right;
    mResultStr = std::to_string(mTmpRes);
}

void EvalVisitor::visit(std::shared_ptr<ASTMul> node)
{
    node->getRight()->accept(*this);
    auto right = mTmpRes;
    node->getLeft()->accept(*this);
    mTmpRes *= right;
    mResultStr = std::to_string(mTmpRes);
}

void EvalVisitor::visit(std::shared_ptr<ASTDiv> node)
{
    node->getRight()->accept(*this);
    auto right = mTmpRes;
    node->getLeft()->accept(*this);
    mTmpRes /= right;
    mResultStr = std::to_string(mTmpRes);
}

void EvalVisitor::visit(std::shared_ptr<ASTVar> node)
{
    /* read value from var */
    if ( mVarMap.find(node->getVarName()) != mVarMap.end() )
    {
        mTmpRes = mVarMap.at(node->getVarName());
        mResultStr = std::to_string(mTmpRes);
    }
    else
    {
        std::cerr << "undefined variable " << node->getVarName() << "\n";
        exit(1);
    }
}

void EvalVisitor::visit(std::shared_ptr<ASTNum> node)
{
    mTmpRes = std::stof(node->getValueStr());
    mResultStr = std::to_string(mTmpRes);
}

void EvalVisitor::visit(std::shared_ptr<ASTAssign> node)
{
    node->getRight()->accept(*this);
    /* save variable value to map */
    mVarMap[node->getLeft()->getVarName()] = mTmpRes;
    /* assign does not need a printing */
    mResultStr = "";
}

