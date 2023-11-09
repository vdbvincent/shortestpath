/**
 * @file pathfinder.cpp
 * @author vincent.vdb@gmail.com
 * @brief class that implements the A* shortest path algorithm
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "pathfinder.h"
#include <cassert>
#include <math.h>
#include <algorithm>

pathfinder::pathfinder(grapheclass * pg)
{
    assert(pg != nullptr);
    g = pg;
}

pathfinder::~pathfinder(void)
{

}

// Méthode permettant la recherche du plus cours chemin
int pathfinder::searchPath(void)
{
    debug_print("Démarrage de la recherche de chemin\n");

    // On démarre avec le premier noeud Start
    nodeclass * startnode = g->getStartNode();
    nodeclass * endnode = g->getFinnishNode();
    if (startnode == NULL)
    {
        debug_print("Start node null");
        return -1;
    }
    if (endnode == NULL)
    {
        debug_print("End node null");
        return -1;
    }
    startnode->setParent(NULL);
    // Ajout du premier noeud dans la liste fermée
    setNodeInClosedList(*startnode);

    nodeclass n = *startnode;

    // On cherche les noeuds candidants potentiels
    searchNextNode(n);

    // Tant qu'on a pas atteint le but ou que la liste de noeuds à explorer n'est pas vide
    while(n != *endnode && !liste_ouverte.empty())
    {
        // Recherche du meilleurs noeud candidat possible
        if (getBestNodeInOPenList(n))
        {
            // Le meilleur va dans la liste fermée et supprimé de la liste ouverte
            setNodeInClosedList(n);
            delNodeInOpenList(n);

            // On cherche les noeuds candidats potentiels à partir du meilleur précédent
            searchNextNode(n);
        }
        else
            debug_print("Aucun meilleur noeud trouvé\n");
    }

    // Si le noeud arrivé est trouvé
    if (n == *endnode)
    {
        debug_print("Arrivee trouvée ! : [%d:%d]\n", n.x, n.y);
        // Tracage du chemin trouvé sur la map
        retrace_path();
    }
    debug_print("Fin de la recherche\n\n");
    return 0;
}

// Méthode permettant de rechercher les noeuds candidants pour continuer le chemin
// Les candidants sont mis en liste ouverte 
void pathfinder::searchNextNode(nodeclass n)
{
    // On cherche dans les voisins
    for (int j = n.y-1; j <= n.y+1; j++)
    {
        for (int i = n.x-1; i <= n.x+1; i++)
        {
            debug_print("Evaluation du noeud [%d:%d]\n", i, j);
            if ((i < 0) || (j < 0) || (i > g->getMaxCols()) || (j > g->getMaxRows())) // En dehors de la map
            {
                debug_print("Noeud [%d:%d] en dehors de la map\n", i, j);
                continue;
            }

            // Noeud temperaire
            nodeclass nodetemp(*(*g)(i, j));
            
            // Mouvements interdits (diagonales)
            if ((nodetemp.x == n.x-1 && nodetemp.y == n.y-1)
            ||  (nodetemp.x == n.x+1 && nodetemp.y == n.y+1)
            ||  (nodetemp.x == n.x+1 && nodetemp.y == n.y-1)
            ||  (nodetemp.x == n.x-1 && nodetemp.y == n.y+1))
            {
                debug_print("Mouvement interdit [%d:%d]\n", nodetemp.x, nodetemp.y);
                continue;
            }

            // Noeud courant
            if (n == nodetemp)
            {
                debug_print("Noeud courant [%d:%d]\n", nodetemp.x, nodetemp.y);
                continue;
            }
            
            // Noeud infranchissable
            if (nodetemp.isWall())
            {
                debug_print("Noeud infranchissable [%d:%d]\n", nodetemp.x, nodetemp.y);
                continue;
            }

            // Si le noeud n'est pas présent dans la liste fermée, sinon on l'oublie
            if (!isNodeInList(liste_fermee, nodetemp))
            {
                // Calcul du cout
                nodetemp.setCoutH(distance(*(g->getFinnishNode()), nodetemp));
                debug_print("Calcul du cout H : %f\n", nodetemp.getCoutH());

                // Mise a jour du parent dans la map
                (*g)(nodetemp.x, nodetemp.y)->setParent((*g)(n.x, n.y));

                // Si le noeud est dans la liste ouverte
                if (isNodeInList(liste_ouverte, nodetemp))
                {
                    // Si cout moins faible que sa copie présente en liste, les échanger
                    if (nodetemp.getCoutH() < getNodeInList(liste_ouverte, nodetemp).getCoutH())
                    {
                        setExistingNodeInOpenList(nodetemp);
                    }
                }
                // sinon on l'ajoute
                else
                {
                    setNodeInOpenList(nodetemp);
                }
            }
            else
                debug_print("Noeud [%d:%d] deja present dans la liste fermée\n", nodetemp.x, nodetemp.y);
        }
    }
}

// recherche d'un noeud dans une liste de noeuds
bool pathfinder::isNodeInList(std::list<nodeclass> list, nodeclass node)
{
    std::list<nodeclass>::iterator it = list.begin();
    while (it != list.end())
    {
        if ((*it) == node)
            return true;
        else
            it++;
    }
    return false;
}

// Fonction retournant la distance euclidienne entre 2 points la map
double pathfinder::distance(nodeclass n1, nodeclass n2)
{
    return sqrt(pow(n1.x - n2.x, 2) + pow(n1.y - n2.y, 2));
}

// Fonction retournant un noeud d'une liste
nodeclass pathfinder::getNodeInList(std::list<nodeclass> list, nodeclass node)
{
    std::list<nodeclass>::iterator it = list.begin();
    while (it != list.end())
    {
        if ((*it) == node)
            return *it;
        else
            it++;
    }
    return *it;
}

// Méthodes permettant d'ajouter un noeud en liste
void pathfinder::setNodeInClosedList(nodeclass node)
{
    debug_print("Ajout du noeud [%d:%d] dans la liste fermee\n", node.x, node.y);
    liste_fermee.push_back(node);
}
void pathfinder::setNodeInOpenList(nodeclass node)
{
    debug_print("Ajout du noeud [%d:%d] dans la liste ouverte\n", node.x, node.y);
    liste_ouverte.push_back(node);
}

// Méthode permettant de mettre à jour un noeud dans la liste ouverte
void pathfinder::setExistingNodeInOpenList(nodeclass node)
{
    // Recherche de l'itérateur du noeud
    std::list<nodeclass>::iterator it = liste_ouverte.begin();
    while (it != liste_ouverte.end())
    {
        if ((*it) == node)
            break;
        else
            it++;
    }
    // Mise a jour du noeud dans la liste
    if (it != liste_ouverte.end())
    {
        (*it).setCoutH(node.getCoutH());
        (*it).setParent(node.getParent());
        debug_print("Mise à jour du noeud [%d:%d] de la liste ouverte\n", node.x, node.y);
    }
    else
        debug_print("ERROR node unknown in open list\n");
}

// Fonction retournant le noeud de la liste fermée ayant le cout le plus faible
bool pathfinder::getBestNodeInOPenList(nodeclass & n)
{
    if (! liste_ouverte.empty())
    {
        nodeclass tmp = *(liste_ouverte.begin());

        for (std::list<nodeclass>::iterator it = liste_ouverte.begin(); it != liste_ouverte.end(); it++)
        {
            if ((*it).getCoutH() < tmp.getCoutH())
            {
                tmp = *it;
                debug_print("Meileur noeud trouve [%d:%d]\n", tmp.x,tmp.y);
            }
        }
        n = tmp;
        return true;
    }

    return false;
}

// Fonction permettant de supprimer un noeud de la liste ouverte
bool pathfinder::delNodeInOpenList(nodeclass node)
{
    if (! liste_ouverte.empty())
    {
        std::list<nodeclass>::iterator it = liste_ouverte.begin();
        while (it != liste_ouverte.end())
        {
            if (*it == node)
            {
                it  = liste_ouverte.erase(it);
                debug_print("Suppression du noeud [%d:%d] de la liste ouverte\n", node.x, node.y);
                return true;
            }
            else
                it ++;
        }
        return false;
    }
    else
         return false;
}

// Retracage du chemin optimal depuis l'arrivée
void pathfinder::retrace_path(void)
{
    // Noeud arrivé
    nodeclass * child = g->getFinnishNode();
    child->setPath(true);
    while (child->getParent() != NULL)
    {
        nodeclass * parent = child->getParent();
        calculmoove(child, parent);
        
        child = child->getParent();
        child->setPath(true);
    }
}

// Calcul de la séquence de mouvements du chemin
void pathfinder::calculmoove(nodeclass * child, nodeclass * parent)
{
    int moove = -1;
    if (child->x == parent->x && child->y-1 == parent->y)
        moove = DOWN;
    else if (child->x == parent->x && child->y+1 == parent->y)
        moove = UP;
    else if (child->x-1 == parent->x && child->y == parent->y)
        moove = RIGHT;
    else if (child->x+1 == parent->x && child->y == parent->y)
        moove = LEFT;
    else
        moove = FORBIDDEN;

    mouvements.push_back(moove);
}

// Méthode affichant la séquence de mouvemements correspondant au chemin
void pathfinder::printMooves(void)
{
    printf("Sequece of movements correspondind to the shortest path :\n");
    
    while (!mouvements.empty())
    {
        int moove = mouvements.back();
        mouvements.pop_back();
        printf(" ");
        switch (moove)
        {
            case UP: printf("UP"); break;
            case DOWN: printf("DOWN"); break;
            case RIGHT: printf("RIGHT"); break;
            case LEFT: printf("LEFT"); break;
            default: printf("FORBIDDEN");
        }
        printf(" >");
    }
    
    printf(" FINNISH\n");
}