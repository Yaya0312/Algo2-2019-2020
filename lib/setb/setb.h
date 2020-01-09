//  Partie interface du module setb

//  Le module setb permet de gérer un multi ensemble borné

#ifndef SETB__H
#define SETB__H

#include <stdio.h>
#include <stdlib.h>

typedef struct setb setb;

//  setb_empty : créé une structure de données correspondant initialement à
//    ensemble borné vide, il possède une borne maximale max de type int.
//    Renvoie NULL en cas de dépassement de capacité.
//    Renvoie un pointeur vers l'objet qui gère la structure de données sinon.
extern setb *setb_empty(int max);

//  setb_put : ajoute num au à l'ensemble associé à msb.
//   Renvoie une valeur non nulle en cas de dépassement de capacité.
//   Renvoie zéro sinon.
extern int setb_put(setb *msb, int num);

//  setb_display : affiche le graphe d'appartenance de l'ensemble borné.
//    Si l'entier est présent il est indiqué par une croix. Sinon rien n'est
//    affiché pour cet entier chaque entier est séparé par une tabulation.
extern void setb_display(setb *msb);

//  setb_dispose : libère les ressources allouées à la structure de données
//    associée à *msbptr
extern void setb_dispose(setb **msbptr);

//  setb_max : retourne la borne maximale de l'ensemble borné msbprt
extern int setb_max(setb *msbptr);

#endif
