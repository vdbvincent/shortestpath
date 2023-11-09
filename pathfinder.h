/**
 * @file pathfinder.h
 * @author vincent.vdb@gmail.com
 * @brief class that implements the A* shortest path algorithm
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_
#include "graphe.h"
#include "debug.h"
#include <stdio.h>
#include <list>
#include <vector>

// Définition des mouvements
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
#define FORBIDDEN 5

class pathfinder
{
private:
    grapheclass * g; // Maps de nodes
    std::list<nodeclass> liste_ouverte;  // Liste de recherches de nodes candidats
    std::list<nodeclass> liste_fermee;   // Liste de nodes candidats
    std::vector<int> mouvements;

    bool isNodeInList(std::list<nodeclass> list, nodeclass node);
    nodeclass getNodeInList(std::list<nodeclass> list, nodeclass node);
    void setNodeInClosedList(nodeclass ode);
    void setNodeInOpenList(nodeclass node);
    bool delNodeInOpenList(nodeclass node);
    double distance(nodeclass n1, nodeclass n2);
    bool getBestNodeInOPenList(nodeclass &n);
    void setExistingNodeInOpenList(nodeclass node);

    void searchNextNode(nodeclass n);

    void retrace_path(void);
    void calculmoove(nodeclass * child, nodeclass * parent);

public:
    pathfinder(grapheclass * pg);
    ~pathfinder(void);

    int searchPath(void);
    void printMooves(void);
};

#endif