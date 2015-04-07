//
//  GeneticProgram.cpp
//  GeneticProgram
//
//  Created by Russell Shurts on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GeneticProgram.h"

static int MAX_HEIGHT = 15; //(2^(height+1) - 1) where MAX(Height) = 4;
static int OPERATOR_HEIGHT = 7; //(2^(height) - 1) where MAX(Height) = 4;
static int POPULATION_SIZE = 100;

void createTreePopulation(evalTreePtr population[][31], int startIndex)
{
    srand(1);
    int op;
    int tree, leaf;
    
    for (tree = startIndex; tree < POPULATION_SIZE; tree++)
    {
        for (leaf = 0; leaf < (MAX_HEIGHT); leaf++) 
        {
            population[tree][leaf] = new evalTree; // creates initial tree structure
            
            if (leaf < (OPERATOR_HEIGHT)) // create operator nodes
            {
                op = 1 + rand() % 4;
                switch (op)
                {
                    case 1:
                        population[tree][leaf]->insert(new evalNode(add));
                        break;
                    case 2:
                        population[tree][leaf]->insert(new evalNode(subtract));
                        break;
                    case 3:
                        population[tree][leaf]->insert(new evalNode(multiply));
                        break;
                    case 4:
                        population[tree][leaf]->insert(new evalNode(divide));
                        break;
                } //switch
            } //if
            else // create operand or variable nodes
            {
                op = rand() % 15;
                if (op < 10) // 0-9 operands
                {
                    population[tree][leaf]->insert(new evalNode(op));
                }
                else // variable
                {
                    population[tree][leaf]->insert(new evalNode(x));
                }
            }// else
        }// for (leaf)
    }// for (tree)
    
    for (tree = startIndex; tree < POPULATION_SIZE; tree++)
    {
        for (leaf = 0; leaf < (OPERATOR_HEIGHT); leaf++) 
        {
            population[tree][leaf]->makeLeft(population[tree][2*leaf+1]);
            population[tree][leaf]->makeRight(population[tree][2*leaf+2]);
        }// for (leaf)
    }// for (tree)
    
    return;
}

double findFitness(evalTreePtr t)
{
    double trainingDataY[10] = {128.5, 32.5, 8.5, 2.5, 0.5, 1, 5, 13, 41, 145};
    double trainingDataX[10] = {-16, -8, -4, -2, 0, 1, 3, 5, 9, 17};
    double eval = 0;
    double sumOfDifferences = 0;
    bool divByZero = false;
    
    for(int i=0; i<10; i++)
    {
        eval = evaluateTree(t, trainingDataX[i], &divByZero);
        //cout << "x: " << trainingDataX[i] << " y: " << eval << endl;
        sumOfDifferences = sumOfDifferences + fabs(trainingDataY[i] - eval);
    }// for
    
    if (divByZero)
    {
        sumOfDifferences = 999999999.999;
    }
    return sumOfDifferences;
}

void createNextGeneration(evalTreePtr population[][31], double fitness[], int seed)
{
    int leaf1, leaf2, leaf3, leaf4, leaf5;
    int seed1 = seed;
    int i;
    evalTreePtr newPopulation[100][31];
    
    //create tree structure for newPopulation
    createTreePopulation(newPopulation, 0);
    
    //copy the top 5 (0-4)
    for (i=0; i<5; i++)
    {
        // check for duplicates here?
        copyTree(population[i][0],newPopulation[i][0]);
    }
    //crossover the top 10 (5-14)
    for (i=0; i<10; i++)
    {
        copyTree(newPopulation[i][0], newPopulation[i+5][0]);
    }
    for (i=5; i<14; i++)
    {
        if (i%2 == 0)
        {
            seed1++;
            srand(seed1);
            leaf1 = 1 + rand() % (MAX_HEIGHT-1);
            crossoverTrees(newPopulation[i][leaf1], newPopulation[i+1][leaf1]);
        }
    }
    //mutate the top 20 three times (15-34)
    for (i=0; i<20; i++)
    {
        copyTree(population[i][0], newPopulation[i+15][0]);
        seed1++;
        srand(seed1);
        leaf1 = rand() % MAX_HEIGHT;
        //cout << "leaf1: " << leaf1 << endl;
        leaf2 = rand() % MAX_HEIGHT;
        //cout << "leaf2: " << leaf2 << endl;
        leaf3 = rand() % MAX_HEIGHT;
        //cout << "leaf3: " << leaf3 << endl;
        mutateTree(newPopulation[i+15][leaf1], (seed1+seed+1));
        mutateTree(newPopulation[i+15][leaf2], (seed1+seed+2));
        mutateTree(newPopulation[i+15][leaf3], (seed1+seed+3));
    }
    //mutate the top 20 five times (35-54)
    for (i=0; i<20; i++)
    {
        copyTree(population[i][0], newPopulation[i+35][0]);
        seed1++;
        srand(seed1);
        leaf1 = rand() % MAX_HEIGHT;
        //cout << "leaf1: " << leaf1 << endl;
        leaf2 = rand() % MAX_HEIGHT;
        //cout << "leaf2: " << leaf2 << endl;
        leaf3 = rand() % MAX_HEIGHT;
        //cout << "leaf3: " << leaf3 << endl;
        leaf4 = rand() % MAX_HEIGHT;
        //cout << "leaf3: " << leaf3 << endl;
        leaf5 = rand() % MAX_HEIGHT;
        //cout << "leaf3: " << leaf3 << endl;
        mutateTree(newPopulation[i+35][leaf1], (seed1+seed+4));
        mutateTree(newPopulation[i+35][leaf2], (seed1+seed+5));
        mutateTree(newPopulation[i+35][leaf3], (seed1+seed+6));
        mutateTree(newPopulation[i+35][leaf4], (seed1+seed+7));
        mutateTree(newPopulation[i+35][leaf5], (seed1+seed+8));
    }
    //mutate the top 21-30 five times (55-64)
    for (i=0; i<10; i++)
    {
        copyTree(population[i+20][0], newPopulation[i+55][0]);
        seed1++;
        srand(seed1);
        leaf1 = rand() % MAX_HEIGHT;
        //cout << "leaf1: " << leaf1 << endl;
        leaf2 = rand() % MAX_HEIGHT;
        //cout << "leaf2: " << leaf2 << endl;
        leaf3 = rand() % MAX_HEIGHT;
        //cout << "leaf3: " << leaf3 << endl;
        leaf4 = rand() % MAX_HEIGHT;
        //cout << "leaf3: " << leaf3 << endl;
        leaf5 = rand() % MAX_HEIGHT;
        //cout << "leaf3: " << leaf3 << endl;
        mutateTree(newPopulation[i+55][leaf1], (seed1+seed+9));
        mutateTree(newPopulation[i+55][leaf2], (seed1+seed+10));
        mutateTree(newPopulation[i+55][leaf3], (seed1+seed+11));
        mutateTree(newPopulation[i+55][leaf4], (seed1+seed+12));
        mutateTree(newPopulation[i+55][leaf5], (seed1+seed+13));
    }
    //create 35 new trees (65-99)
    createTreePopulation(newPopulation, 65);
    
    //move newPopulation back to population
    for (i=0; i<POPULATION_SIZE; i++)
    {
        copyTree(newPopulation[i][0], population[i][0]);
    }
    
    return;
}

void mutateTree(evalTreePtr t, int seed)
{
    srand(seed);
    int op;
    evalNodeType type;
    
    if (!t->isEmpty())
    {
        type = t->getData()->getType();
        if (type==evalOperator)
        {
            op = 1 + rand() % 4;
            //cout << "operator: " << op << endl;
            switch (op)
            {
                case 1:
                    if (t->getData()->getOperator() != add)
                        t->insert(new evalNode(add));
                    else
                        t->insert(new evalNode(divide));
                    break;
                case 2:
                    if (t->getData()->getOperator() != subtract)
                        t->insert(new evalNode(subtract));
                    else
                        t->insert(new evalNode(multiply));
                    break;
                case 3:
                    if (t->getData()->getOperator() != multiply)
                        t->insert(new evalNode(multiply));
                    else
                        t->insert(new evalNode(subtract));
                    break;
                case 4:
                    if (t->getData()->getOperator() != divide)
                        t->insert(new evalNode(divide));
                    else
                        t->insert(new evalNode(add));
                    break;
            } //switch
        }// if evalOperator
        else
        {
            op = rand() % 15;
            //cout << "operand: " << op << endl;
            if (op < 10) // 0-9 operands
            {
                t->insert(new evalNode(op));
            }
            else // variable
            {
                t->insert(new evalNode(x));
            }
        }// else evalOperand or evalVariable
    }// if !isEmpty
    return;
}

void crossoverTrees(evalTreePtr t1, evalTreePtr t2)
{
    if (!t1->isEmpty() || !t2->isEmpty())
    {
        evalTreePtr temp = new evalTree;
        evalNodePtr type1;
        evalNodePtr type2;
        
        crossoverTrees(t1->left(), t2->left());
        
        type1 = t1->getData();
        type2 = t2->getData();
        
        switch (type1->getType())
        {
            case evalOperator:
                temp->insert(new evalNode(t1->getData()->getOperator()));
                switch (type2->getType())
            {
                case evalOperator:
                    t1->insert(new evalNode(t2->getData()->getOperator()));
                    break;
                case evalOperand:
                    t1->insert(new evalNode(t2->getData()->getOperand()));
                    break;
                case evalVariable:
                    t1->insert(new evalNode(t2->getData()->getVariable()));
                    break;
            }// switch type 2
                t2->insert(new evalNode(temp->getData()->getOperator()));
                break;
            case evalOperand:
                temp->insert(new evalNode(t1->getData()->getOperand()));
                switch (type2->getType())
            {
                case evalOperator:
                    t1->insert(new evalNode(t2->getData()->getOperator()));
                    break;
                case evalOperand:
                    t1->insert(new evalNode(t2->getData()->getOperand()));
                    break;
                case evalVariable:
                    t1->insert(new evalNode(t2->getData()->getVariable()));
                    break;
            }// switch type 2            
                t2->insert(new evalNode(temp->getData()->getOperand()));
                break;
            case evalVariable:
                temp->insert(new evalNode(t1->getData()->getVariable()));
                switch (type2->getType())
            {
                case evalOperator:
                    t1->insert(new evalNode(t2->getData()->getOperator()));
                    break;
                case evalOperand:
                    t1->insert(new evalNode(t2->getData()->getOperand()));
                    break;
                case evalVariable:
                    t1->insert(new evalNode(t2->getData()->getVariable()));
                    break;
            }// switch type 2
                t2->insert(new evalNode(temp->getData()->getVariable()));
                break;
        }// switch type1
        
        crossoverTrees(t1->right(), t2->right());
    }
    return;
}

void copyTree(evalTreePtr t2, evalTreePtr t1)
{
    if (!t1->isEmpty()  || !t2->isEmpty())
    {
        evalNodePtr type1;
        evalNodePtr type2;
        
        copyTree(t2->left(), t1->left());
        
        type1 = t1->getData();
        type2 = t2->getData();
        
        switch (type1->getType())
        {
            case evalOperator:
                switch (type2->getType())
            {
                case evalOperator:
                    t1->insert(new evalNode(t2->getData()->getOperator()));
                    break;
                case evalOperand:
                    t1->insert(new evalNode(t2->getData()->getOperand()));
                    break;
                case evalVariable:
                    t1->insert(new evalNode(t2->getData()->getVariable()));
                    break;
            }// switch type 2
                break;
            case evalOperand:
                switch (type2->getType())
            {
                case evalOperator:
                    t1->insert(new evalNode(t2->getData()->getOperator()));
                    break;
                case evalOperand:
                    t1->insert(new evalNode(t2->getData()->getOperand()));
                    break;
                case evalVariable:
                    t1->insert(new evalNode(t2->getData()->getVariable()));
                    break;
            }// switch type 2            
                break;
            case evalVariable:
                switch (type2->getType())
            {
                case evalOperator:
                    t1->insert(new evalNode(t2->getData()->getOperator()));
                    break;
                case evalOperand:
                    t1->insert(new evalNode(t2->getData()->getOperand()));
                    break;
                case evalVariable:
                    t1->insert(new evalNode(t2->getData()->getVariable()));
                    break;
            }// switch type 2
                break;
        }// switch type1
        
        copyTree(t2->right(), t1->right());
    }
    return;
}

void sort(evalTreePtr population[][31], double fitness[], int first, int last)
{
    int split;
    
    if (first>=last)
        return;
    
    split = partition(population, fitness, first, last);
    sort(population, fitness, first, split-1);
    sort(population, fitness, split+1, last);
    return;
}

int partition(evalTreePtr population[][31], double fitness[], int first, int last)
{
    int ls = first;
    int i;
    
    for (i = first+1; i <= last; i++)
    {
        if (fitness[first] > fitness[i])
        {
            ls++;
            swap(fitness, ls, i);
            crossoverTrees(population[ls][0], population[i][0]);
        }
    }
    
    swap(fitness, first, ls);
    crossoverTrees(population[first][0], population[ls][0]);
    
    return ls;
}

void swap (double fitness[], int a, int b)
{
    double temp;
    
    temp = fitness[a];
    fitness[a] = fitness[b];
    fitness[b] = temp;
    
    return;
}