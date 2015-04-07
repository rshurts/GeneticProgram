//
//  ExpressionTree.h
//  GeneticProgram
//
//  Created by Russell Shurts on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef ETREE_H
#define ETREE_H

#include <iostream>
using namespace std;

#include "BinaryTree.h"

enum evalNodeType {evalOperator, evalOperand, evalVariable};
enum evalOperatorType {add, subtract, multiply, divide};
enum evalVariableType {x};

class evalNode
{
public:
    evalNode(double d);
    evalNode(evalOperatorType op);
    evalNode(evalVariableType x);
    evalNodeType getType() const;
    // Preconditions: None
    // Postconditions: None
    // Returns: the type of the tree node {evalOperand, evalOperator}
    double getOperand() const;
    // Preconditions: nodeType == evalOperand
    // Postconditions: None
    // Returns: the value of the operand
    evalOperatorType getOperator() const;
    // Preconditions: nodeType == evalOperator
    // Postconditions: None
    // Returns: the type of the operator
    evalVariableType getVariable() const;
    // Preconditions: nodeType == evalVariable
    // Postconditions: None
    // Returns: the variable type (currently only x)
protected:
    evalNodeType nodeType;
    double nodeOperand;
    evalOperatorType nodeOperator;
    evalVariableType nodeVariable;
};

typedef evalNode * evalNodePtr;
typedef BinaryTree <evalNodePtr> evalTree;
typedef evalTree * evalTreePtr;

double evaluateTree(evalTreePtr t, double xVar, bool *divByZero);
void inOrderTraverse(evalTreePtr t);

#endif