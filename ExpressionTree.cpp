//
//  ExpressionTree.cpp
//  GeneticProgram
//
//  Created by Russell Shurts on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ExpressionTree.h"

evalNode::evalNode(double d)
{
    nodeType = evalOperand;
    nodeOperand = d;
}// evalNode operand

evalNode::evalNode(evalOperatorType op)
{
    nodeType = evalOperator;
    nodeOperator = op;
}// evalNode operator

evalNode::evalNode(evalVariableType x)
{
    nodeType = evalVariable;
    nodeVariable = x;
}

evalNodeType evalNode::getType() const
{
    return nodeType;
}// getType

double evalNode::getOperand() const
{
    assert(nodeType == evalOperand);
    return nodeOperand;
}//getOperand

evalOperatorType evalNode::getOperator() const
{
    assert(nodeType == evalOperator);
    return nodeOperator;
}// getOperator

evalVariableType evalNode::getVariable() const
{
    assert(nodeType == evalVariable);
    return nodeVariable;
}// getVariable

double evaluateTree(evalTreePtr t, double xVar, bool *divByZero)
{
    assert(!t->isEmpty());
    evalNodePtr rootNodePtr = t->getData();
    if (rootNodePtr->getType() == evalOperand)
    {
        return rootNodePtr->getOperand();
    }// if
    else if (rootNodePtr->getType() == evalVariable)
    {
        return xVar;
    }// else if
    else
    {
        double left(evaluateTree(t->left(), xVar, divByZero));
        double right(evaluateTree(t->right(), xVar, divByZero));
        switch (rootNodePtr->getOperator())
        {
            case add:
                return left+right;
            case subtract:
                return left-right;
            case multiply:
                return left*right;
            case divide:
                if (!right) 
                {
                    *divByZero = true; 
                    return 999999999.999; 
                } // What to do if there is a divide by 0. I'm open to ideas...
                else
                {
                    assert (right);
                    return left / right;
                }
        }// switch
    }// else
}// evaluateTree

void inOrderTraverse(evalTreePtr t)
{
    if (!t->isEmpty())
    {
        //traverse left child
        cout << "(";
        inOrderTraverse(t->left());
        //print node value
        evalNodePtr rootNodePtr = t->getData();
        if (rootNodePtr->getType() == evalOperand)
        {
            cout << rootNodePtr->getOperand();
        }// if
        else if (rootNodePtr->getType() == evalVariable)
        {
            switch (rootNodePtr->getVariable())
            {
                case x:
                    cout << "x";
                    break;
            }
        }// else if
        else
        {
            switch (rootNodePtr->getOperator())
            {
                case add:
                    cout << "+";
                    break;
                case subtract:
                    cout << "-";
                    break;
                case multiply:
                    cout << "*";
                    break;
                case divide:
                    cout << "/";
                    break;
            }// switch
        }// else
        //traverse right child
        inOrderTraverse(t->right());
        cout << ")";
    }
}// inOrderTraverse
