/**
 * @file noeud.cpp
 * @author vincent.vdb@gmail.com
 * @brief class which represents a node contained in the map
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "noeud.h"

nodeclass::nodeclass(unsigned int px, unsigned int py, bool pstart, bool pfinnish, bool pwall)
    : x(px)
    , y(py)
    , start(pstart)
    , finnish(pfinnish)
    , wall(pwall)
    , path(false)
{
}
nodeclass::nodeclass(const nodeclass & n)
    : x(n.x)
    , y(n.y)
    , start(n.start)
    , finnish(n.finnish)
    , wall(n.wall)
    , path(n.path)
    , coutH(n.coutH)
{
}

nodeclass::~nodeclass(void)
{

}
bool nodeclass::estEgal(nodeclass const& b) const
{
    if (x == b.x && y == b.y)
        return true;
    else
        return false;
}
bool operator==(nodeclass const& a, nodeclass const& b)
{
    return a.estEgal(b);
}
bool operator!=(nodeclass const& a, nodeclass const& b)
{
    return !a.estEgal(b);
}

nodeclass& nodeclass::operator=(const nodeclass& n)
{
    x = n.x;
    y = n.y;
    coutH = n.coutH;
    start = n.start;
    finnish = n.finnish;
    wall = n.wall;
    path = n.path;
    return *this;
}