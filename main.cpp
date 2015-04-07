//
//  main.cpp
//  GeneticProgram
//
//  Created by Russell Shurts on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BinaryTree.h"
#include "ExpressionTree.h"
#include "GeneticProgram.h"

using namespace std;

int main()
{
    
    int generationCounter = 1;
    double fitness[100];
    evalTreePtr population[100][31];
    
    createTreePopulation(population, 0);
    
    cout << "Generation, Tree Number, Fitness, Tree" << endl;
    do 
    {
        for (int tree = 0; tree < 100; tree++)
        {        
            fitness[tree] = findFitness(population[tree][0]);
        }
        
        sort(population, fitness, 0, 99);
        
        for (int tree = 0; tree < 100; tree++)
        {        
            cout << generationCounter << ", " << tree << ", " << fitness[tree] << ", "; 
            inOrderTraverse(population[tree][0]);
            cout << endl;
        }
        
        createNextGeneration(population, fitness, generationCounter);
        generationCounter++;
    } while (fitness[0] != 0);
    
    cout << generationCounter-1 << ", " << 0 << ", " << fitness[0] << ", "; 
    inOrderTraverse(population[0][0]);
    cout << endl;
    
    
    //cout << "Creation & Fitness calculation test:" << endl;
    //for (int tree = 0; tree < 100; tree++)
    //{
    //    inOrderTraverse(population[tree][0]);
    //    cout << endl;
    //    fitness[tree] = findFitness(population[tree][0]);
    //    cout << fitness[tree] << endl;
    //}
    
    //cout << "Mutation Test:" << endl;
    //inOrderTraverse(population[0][0]);
    //cout << endl;
    //mutateTree(population[0][1], generationCounter);
    //mutateTree(population[0][3], generationCounter);
    //mutateTree(population[0][7], generationCounter);
    //mutateTree(population[0][8], generationCounter);
    //inOrderTraverse(population[0][0]);
    //cout << endl;
    
    //cout << "Crossover Test:" << endl;
    //inOrderTraverse(population[0][0]);
    //cout << endl;
    //inOrderTraverse(population[1][0]);
    //cout << endl;
    //crossoverTrees(population[0][3], population[1][3]); // crossover starting from node 3
    //inOrderTraverse(population[0][0]);
    //cout << endl;
    //inOrderTraverse(population[1][0]);
    //cout << endl;
    
    //cout << "Copy Test:" << endl;
    //inOrderTraverse(population[0][0]);
    //cout << endl;
    //inOrderTraverse(population[1][0]);
    //cout << endl;
    //copyTree(population[0][0], population[1][0]);
    //inOrderTraverse(population[0][0]);
    //cout << endl;
    //inOrderTraverse(population[1][0]);
    //cout << endl;
    
    //cout << "Sort Test: " << endl;
    //for (int tree = 0; tree < 100; tree++)
    //{        
    //    fitness[tree] = findFitness(population[tree][0]);
    //    cout << generationCounter << ", " << fitness[tree] << ", "; 
    //    inOrderTraverse(population[tree][0]);
    //    cout << endl;
    //}
    //cout << "Sorted: " << endl;
    //sort(population, fitness, 0, 99);
    //for (int tree = 0; tree < 100; tree++)
    //{        
    //    cout << generationCounter << ", " << fitness[tree] << ", "; 
    //    inOrderTraverse(population[tree][0]);
    //    cout << endl;
    //}
    
    return 0;
}// main
