/**
 * @file noeud.h
 * @author vincent.vdb@gmail.com
 * @brief class which represents a node contained in the map
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __NODECLASS_H_
#define __NODECLASS_H_

class nodeclass
{
private:
    
    nodeclass *parent;

    double coutH; // distance euclidienne entre le point et l'arrivée

    bool start;   // Représente le noeud de départ
    bool finnish; // Représente le noeud d'arrivée
    bool wall;    // Représente un obstable
    bool path;    // Représente le chemin

public:
    // Coordonnées du noeud
    unsigned int x;
    unsigned int y;

    nodeclass(unsigned int px, unsigned int py, bool start = false, bool finnish = false, bool wall = false);
    nodeclass(const nodeclass & n);
    ~nodeclass(void);

    // Getter
    bool isStart(void) { return start; }
    bool isFinnish(void) { return finnish; }
    bool isWall(void) { return wall ;}
   
    double  getCoutH(void) { return coutH; }
    void setCoutH(double v) { coutH = v; }

    void setParent(nodeclass * node) { parent = node; }
    nodeclass * getParent(void) { return parent; }
    void setPath(bool value) { path = value ; }
    bool isPath(void) { return path; }

    // Surcharges d'opérateurs
    bool estEgal(nodeclass const& b) const;
    nodeclass& operator= (const nodeclass& n);
};

bool operator==(nodeclass const& a, nodeclass const& b);
bool operator!=(nodeclass const& a, nodeclass const& b);

#endif