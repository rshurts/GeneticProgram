//
//  BinaryTree.h
//  GeneticProgram
//
//  Created by Russell Shurts on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef BTREE_H
#define BTREE_H

#include <assert.h>

template <class btElementType>
class BinaryTree
{
public:
    BinaryTree();
    bool isEmpty() const;
    // Preconditions: None
    // Postconditions: None
    // Returns: true if and only if T is an empty tree
    btElementType getData() const; // getData is an accessor
    // Preconditions: !this->isEmpty()
    // Postconditions: None
    // Returns: the data associated with the root of the tree
    void insert(const btElementType & d);
    // Preconditions: None
    // Postconditions: this->getData() == d; !this->isEmpty()
    BinaryTree * left();
    // Preconditions: !this->isEmpty()
    // Postconditions: None
    // Returns: (a pointer to) the left child of T
    BinaryTree * right();
    // Preconditions: !this->isEmpty()
    // Postconditions: None
    // Returns: (a pointer to) the right child of T
    void makeLeft(BinaryTree * T1);
    // Preconditions: !this->isEmpty(); this->left()->isEmpty()
    // Postconditions: this->left() == T1
    void makeRight(BinaryTree * T1);
    // Preconditions: !this->isEmpty(); this->right()->isEmpty()
    // Postconditions: this->right() == T1
protected:
    bool nullTree;
    btElementType treeData;
    BinaryTree * leftTree;
    BinaryTree * rightTree;
};

template <class btElementType>
BinaryTree <btElementType>::BinaryTree()
{
    nullTree = true;
    leftTree = 0;
    rightTree = 0;
}// BinaryTree

template <class btElementType>
bool BinaryTree <btElementType>::isEmpty() const
{
    return nullTree;
}// isEmpty

template <class btElementType>
btElementType BinaryTree <btElementType>::getData() const
{
    assert(!isEmpty());
    return treeData;
}// getData

template <class btElementType>
void BinaryTree <btElementType>::insert(const btElementType & d)
{
    treeData = d;
    if (nullTree) 
    {
        nullTree = false;
        leftTree = new BinaryTree;
        rightTree = new BinaryTree;
    }// if
}// insert

template <class btElementType>
BinaryTree <btElementType> * BinaryTree <btElementType>::left()
{
    assert(!isEmpty());
    return leftTree;
}// left

template <class btElementType>
BinaryTree <btElementType> * BinaryTree <btElementType>::right()
{
    assert(!isEmpty());
    return rightTree;
}// right

template <class btElementType>
void BinaryTree <btElementType>::makeLeft(BinaryTree * T1)
{
    assert(!isEmpty());
    assert(left()->isEmpty());
    delete left();
    leftTree = T1;
}// makeLeft

template <class btElementType>
void BinaryTree <btElementType>::makeRight(BinaryTree * T1)
{
    assert(!isEmpty());
    assert(right()->isEmpty());
    delete right();
    rightTree = T1;
}// makeRight

#endif