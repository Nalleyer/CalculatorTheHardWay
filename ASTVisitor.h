//
// Created by nalle on 8/1/2017.
//

#pragma once

#include <memory>
#include "ASTNode.h"

class ASTVisitor
{
public:
    friend class ASTNode;
    friend class ASTExp;
    friend class ASTAssign;
    friend class ASTOp;
    friend class ASTAdd;
    friend class ASTSub;
    friend class ASTMul;
    friend class ASTDiv;
    friend class ASTVar;
    friend class ASTNum;

protected:
    virtual void visit(std::shared_ptr<ASTNode> node) = 0;
    virtual void visit(std::shared_ptr<ASTExp> node) = 0;
    virtual void visit(std::shared_ptr<ASTOp> node) = 0;
    virtual void visit(std::shared_ptr<ASTAdd> node) = 0;
    virtual void visit(std::shared_ptr<ASTSub> node) = 0;
    virtual void visit(std::shared_ptr<ASTMul> node) = 0;
    virtual void visit(std::shared_ptr<ASTDiv> node) = 0;
    virtual void visit(std::shared_ptr<ASTVar> node) = 0;
    virtual void visit(std::shared_ptr<ASTNum> node) = 0;
    virtual void visit(std::shared_ptr<ASTAssign> node) = 0;

public:
    ASTVisitor(void) = default;
    virtual ~ ASTVisitor(void) = default;
};
