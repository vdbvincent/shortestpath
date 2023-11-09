/**
 * @file graphe.h
 * @author vincent.vdb@gmail.com
 * @brief class which represents a map containing a start node, a finnish node and obstacles
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __GRAPHECLASS_H_
#define __GRAPHECLASS_H_

#include "noeud.h"
#include "debug.h"
#include <vector>

class grapheclass
{
private:
    std::vector<nodeclass *> graph;  // Vecteur de noeuds
    unsigned int nbNode = 0;
    unsigned int maxcols = 0;
    unsigned int maxrows = 0;

public:
    grapheclass(char map[]);
    ~grapheclass(void);
    nodeclass * getStartNode(void);
    nodeclass * getFinnishNode(void);
    void print(void);

    nodeclass * operator() (unsigned int x, unsigned int y);

    // Getter
    unsigned int getMaxRows(void) { return maxrows; }
    unsigned int getMaxCols(void) { return maxcols; }
};

#endif