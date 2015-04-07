//
//  GeneticProgram.h
//  GeneticProgram
//
//  Created by Russell Shurts on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef GPROG_H
#define GPROG_H

#include <cstdlib>
#include <string>
#include <cmath>
#include <time.h>

#include "BinaryTree.h"
#include "ExpressionTree.h"

void createTreePopulation(evalTreePtr population[][31], int startIndex);
double findFitness(evalTreePtr t);
void createNextGeneration(evalTreePtr population[][31], double fitness[], int seed);
void mutateTree(evalTreePtr t, int seed);
void crossoverTrees(evalTreePtr t1, evalTreePtr t2);
void copyTree(evalTreePtr t2, evalTreePtr t1);
void sort(evalTreePtr population[][31], double fitness[], int first, int last);
int partition(evalTreePtr population[][31], double fitness[], int first, int last);
void swap (double fitness[], int a, int b);

#endif