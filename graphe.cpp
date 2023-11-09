/**
 * @file graphe.cpp
 * @author vincent.vdb@gmail.com
 * @brief class which represents a map containing a start node, a finnish node and obstacles
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
#include "graphe.h"
#include <stdio.h>
#include <string.h>

grapheclass::grapheclass(char map[])
{
    // Creation du graph
    graph.clear();
    int y = 0;
    int x = 0;
    for (int i = 0; i < strlen(map); i++)
    {
        if (map[i] == '\n')
        {
            y ++;
            x = 0;
            continue;
        }

        nodeclass * n;
        if (map[i] == 'S')
        {
            // Noeud start
            n = new nodeclass(x, y, true, false);
        }
        else if (map[i] == 'G')
        {
            // Goal
            n = new nodeclass(x, y, false, true);
        }
        else if (map[i] == '*')
        {
            // Obstable
            n = new nodeclass(x, y, false, false, true);
        }
        else
        {
            // Noeud libre
            n = new nodeclass(x, y);
        }

        if (n != NULL)
        {
            graph.push_back(n);
            nbNode ++;
        }
        else
        {
            perror("Graphe() - Creation graph");
        }
        x ++;
    }
    maxrows = y;
    debug_print("Max rows = %d\n", maxrows);
    maxcols = x - 1; // -1 pour compenser le manque du \n en fin de map sur les données d'entrée
    debug_print("Max cols = %d\n", maxcols);
}

grapheclass::~grapheclass(void)
{
    for (std::vector<nodeclass*>::iterator it = graph.begin(); it != graph.end(); it++)
    {
        if ((*it) != NULL)
        {
            delete (*it);
        }
    }
}

nodeclass * grapheclass::getStartNode(void)
{
    std::vector<nodeclass*>::iterator it = graph.begin();
    while (it != graph.end())
    {
        if ((*it)->isStart())
            break;
        it++;
    }
    if (it != graph.end())
    {
        return *it;
    }
    else
        return NULL;
}
nodeclass * grapheclass::getFinnishNode(void)
{
    std::vector<nodeclass*>::iterator it = graph.begin();
    while (it != graph.end())
    {
        if ((*it)->isFinnish())
            break;
        it++;
    }
    if (it != graph.end())
    {
        return *it;
    }
    else
        return NULL;
}

void grapheclass::print(void)
{
    int y = 0;
    for (std::vector<nodeclass*>::iterator it = graph.begin(); it != graph.end(); it++)
    {
        nodeclass * n = *it;
        if (n->y != y)
        {
            printf("\n");
            y = n->y;
        }
        if (n->isStart())
            printf("S");
        else if (n->isFinnish())
            printf("G");
        else if (n->isWall())
            printf("*");
        else if (n->isPath())
            printf("+");
        else
            printf("-");
    }
    printf("\n");
}

nodeclass * grapheclass::operator() (unsigned int x, unsigned int y)
{
    nodeclass * ret = NULL;
    std::vector<nodeclass *>::iterator it = graph.begin();
    while(it != graph.end() && ret == NULL)
    {
        if ((*it)->x == x && (*it)->y == y)
        {
            ret = *it;
        }
        it ++;
    }
    return ret;
}