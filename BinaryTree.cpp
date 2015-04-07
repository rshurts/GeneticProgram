//
//  BinaryTree.cpp
//  GeneticProgram
//
//  Created by Russell Shurts on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "BinaryTree.h"

// These definitions are included in the header to avoid unresolved extrenal symbol errors when using templates.
// Templates must be defined inline or out of line in the header file in C++.
// They are included here, commented out, for reference.
/*
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
 */