//
// Created by nalle on 8/15/2017.
//

#include "PrintVisitor.h"
#include <iostream>

using std::cout;
using std::endl;

void PrintVisitor::printPos(std::shared_ptr<ASTNode> node)
{
    cout << "(" << node->getLine() << ", " << node->getColumn() << ")\n";
}

void PrintVisitor::visit(std::shared_ptr<ASTNode> node)
{
    cout << "astnode ";
    printPos(node);
}

void PrintVisitor::visit(std::shared_ptr<ASTExp> node)
{
    cout << "astExp ";
    printPos(node);
}

void PrintVisitor::visit(std::shared_ptr<ASTOp> node)
{
    cout << "astOp ";
    printPos(node);
}

void PrintVisitor::visit(std::shared_ptr<ASTAdd> node)
{
    cout << "astAdd ";
    printPos(node);
    cout << "left: \n";
    node->getLeft()->accept(*this);
    cout << "right: \n";
    node->getRight()->accept(*this);
}

void PrintVisitor::visit(std::shared_ptr<ASTSub> node)
{
    cout << "astSub ";
    printPos(node);
    cout << "left: \n";
    node->getLeft()->accept(*this);
    cout << "right: \n";
    node->getRight()->accept(*this);
}

void PrintVisitor::visit(std::shared_ptr<ASTMul> node)
{
    cout << "astMul ";
    printPos(node);
    cout << "left: \n";
    node->getLeft()->accept(*this);
    cout << "right: \n";
    node->getRight()->accept(*this);
}

void PrintVisitor::visit(std::shared_ptr<ASTDiv> node)
{
    cout << "astDiv ";
    printPos(node);
    cout << "left: \n";
    node->getLeft()->accept(*this);
    cout << "right: \n";
    node->getRight()->accept(*this);
}

void PrintVisitor::visit(std::shared_ptr<ASTVar> node)
{
    cout << "astVar ";
    printPos(node);
    cout << "var: " << node->getVarName() << "\n";
}

void PrintVisitor::visit(std::shared_ptr<ASTNum> node)
{
    cout << "astNum ";
    printPos(node);
    cout << "num str: " << node->getValueStr() << "\n";
}
void PrintVisitor::visit(std::shared_ptr<ASTAssign> node)
{
    cout << "astAssign";
    printPos(node);
    cout << "var: ";
    node->getLeft()->accept(*this);
    cout << "right: \n";
    node->getRight()->accept(*this);
}
