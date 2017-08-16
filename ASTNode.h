//
// Created by nalle on 8/1/2017.
//
#pragma once

#include <memory>

class Parser;
class ASTVisitor;

/* with a visitor interface */
class ASTNode : public std::enable_shared_from_this<ASTNode>
{
public:
    virtual void accept(ASTVisitor &visitor);
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
    virtual void accept(ASTVisitor &visitor) override;
    ASTExp(void) = default;
    virtual ~ ASTExp(void) = default;
};

class ASTOp : public ASTExp
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTOp(void) = default;
    ASTOp(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTOp(void) = default;

    std::shared_ptr<ASTExp> getLeft(void);
    std::shared_ptr<ASTExp> getRight(void);

protected:
    std::shared_ptr<ASTExp> mLeft;
    std::shared_ptr<ASTExp> mRight;
};

class ASTAdd : public ASTOp
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTAdd(void) = default;
    ASTAdd(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTAdd(void) = default;
};

class ASTSub : public ASTOp
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTSub(void) = default;
    ASTSub(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTSub(void) = default;
};

class ASTMul : public ASTOp
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTMul(void) = default;
    ASTMul(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTMul(void) = default;
};

class ASTDiv : public ASTOp
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTDiv(void) = default;
    ASTDiv(std::shared_ptr<ASTExp> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTDiv(void) = default;
};

class ASTVar : public ASTExp
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTVar(void) = default;
    ASTVar( const std::string &varName );
    ASTVar( std::string &&varName);
    virtual ~ ASTVar(void) = default;

    std::string getVarName(void);

private:
    std::string mVarName;
};

class ASTNum : public ASTExp
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTNum(void) = default;
    ASTNum( const std::string &valueStr);
    ASTNum( std::string &&valueStr);
    virtual ~ ASTNum(void) = default;

    std::string getValueStr(void);

protected:
    std::string mValueStr;
};


class ASTAssign: public ASTNode
{
public:
    virtual void accept(ASTVisitor &visitor) override;
    ASTAssign(void) = default;
    ASTAssign( std::shared_ptr<ASTVar> left, std::shared_ptr<ASTExp> right);
    virtual ~ ASTAssign(void) = default;

    std::shared_ptr<ASTVar> getLeft(void);
    std::shared_ptr<ASTExp> getRight(void);

protected:
    std::shared_ptr<ASTVar> mLeft;
    std::shared_ptr<ASTExp> mRight;
};
