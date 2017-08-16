//
// Created by nalle on 8/15/2017.
//

#pragma once

#include "ASTVisitor.h"

class PrintVisitor : public ASTVisitor
{
protected:
    virtual void visit(std::shared_ptr<ASTNode> node) override;
    virtual void visit(std::shared_ptr<ASTExp> node) override;
    virtual void visit(std::shared_ptr<ASTOp> node) override;
    virtual void visit(std::shared_ptr<ASTAdd> node) override;
    virtual void visit(std::shared_ptr<ASTSub> node) override;
    virtual void visit(std::shared_ptr<ASTMul> node) override;
    virtual void visit(std::shared_ptr<ASTDiv> node) override;
    virtual void visit(std::shared_ptr<ASTVar> node) override;
    virtual void visit(std::shared_ptr<ASTNum> node) override;
    virtual void visit(std::shared_ptr<ASTAssign> node) override;

public:
    PrintVisitor(void) = default;
    virtual ~PrintVisitor(void) = default;

private:
    void printPos(std::shared_ptr<ASTNode> node);
};

