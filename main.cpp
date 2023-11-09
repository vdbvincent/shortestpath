/**
 * @file main.cpp
 * @author vincent.vdb@gmail.com
 * @brief Pathfinder is a program that calculates the shortest path between a
 *        starting point and an ending point on a map. It implements the A* algorithm
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <unistd.h>
#include "graphe.h"
#include "pathfinder.h"

// Définition de la macro TEST permettant de tester plusieurs combinaisons
// TEST = 1 -> Recherche du chemin sur la map donnée en énnoncé
// TEST = 5 -> Recherche du chemin pour chaque map
#define TEST 1

int main(int, char**){
    std::cout << "Démarrage de pathfinder.\n";


    // Utilisation d'un tableau de char * afin de tester différentes combinaisons.
    char * maps[5];

    char mapok[] = "**********\n\
*S-------*\n\
*--**----*\n\
*----*---*\n\
*-------**\n\
**--------\n\
*--------*\n\
*-*--G---*\n\
*--------*\n\
**********";
    maps[0] = mapok;

    char mapbig[] = "*****************\n\
***--S---**-----*\n\
********--***---*\n\
********-********\n\
*----*---********\n\
*--*---**********\n\
*------*--****--*\n\
*---***-G--****-*\n\
*-----*-----*****\n\
*****---********";
    maps[1] = mapbig;

    char mapempty[] = "";
    maps[2] = mapempty;

    char mapnostart[] = "**********\n\
**-------*\n\
*--**----*\n\
*----*---*\n\
*-------**\n\
**--------\n\
*--------*\n\
*-*--G---*\n\
*--------*\n\
**********";
    maps[3] = mapnostart;

    char mapnoend[] = "**********\n\
*S-------*\n\
*--**----*\n\
*----*---*\n\
*-------**\n\
**--------\n\
*--------*\n\
*-*--*---*\n\
*--------*\n\
**********";
    maps[4] = mapnoend;


    // Calcul du chemin pour les différentes combinaisons
    for (int i = 0; i < TEST; i++)
    {
        std::cout << "\nTest de la map " << i << "\n", i;

        grapheclass * g = new grapheclass(maps[i]);
        if (g == nullptr)
        {
            perror("Alloc graphe");
            return -1;
        }
        g->print();
        
        pathfinder * f = new pathfinder(g);
        if (f == nullptr)
        {
            perror("Alloc pahtfinder");
            return -1;
        }
        f->searchPath();
        
        std::cout << "Résultat :\n";
        g->print();
        f->printMooves();
        
        if (g != nullptr)
            delete g;
        if (f != nullptr)
            delete f;
        std::cout << "\nTraitement de la map terminée.\n";
    }
    
}
