//
// Created by nalle on 8/15/2017.
//

#pragma once

#include "ASTVisitor.h"
#include <stdlib.h>     // atof
#include <map>

class EvalVisitor : public ASTVisitor
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
    EvalVisitor(void) = default;
    virtual ~EvalVisitor(void) = default;

    std::string getResult(void);

private:
    /* calculate and save result to mTmpRes(double ver) and mResult(str for output) every time */
    std::string mResultStr;
    double mTmpRes;
    std::map<std::string, double> mVarMap;
};
