# shortestpath
It implements the A* algorithm

### Use
`./build/pathfinder`

### Out
``Démarrage de pathfinder.

Test de la map 0
**********
*S-------*
*--**----*
*----*---*
*-------**
**--------
*--------*
*-*--G---*
*--------*
**********
Résultat :
**********
*S-------*
*+-**----*
*++--*---*
*-++----**
**-++-----
*---++---*
*-*--G---*
*--------*
**********
Sequece of movements correspondind to the shortest path :
 DOWN > DOWN > RIGHT > DOWN > RIGHT > DOWN > RIGHT > DOWN > RIGHT > DOWN > FINNISH

Traitement de la map terminée.``

First the map is printing. Then the shortest path is printing in the map with the `+` symbol.
At the end, the program prints the sequence of movements corresponding to the shortest path.

## Environnement
Sofware developed on VSCodium for Linux.
GCC 9.4.0
