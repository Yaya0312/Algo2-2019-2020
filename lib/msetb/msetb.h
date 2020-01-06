//  Partie interface du module msetb

//  Le module msetb permet de gérer un multi ensemble borné

#ifndef MSETB__H
#define MSETB__H

#include <stdio.h>
#include <stdlib.h>

typedef struct msetb msetb;

//  msetb_empty : crée une structure de données correspondant initialement à
//    un multi ensemble borné vide. avec pour borne maximale max.
//    Renvoie NULL en cas de dépassement de capacité.
//    Renvoie un pointeur vers l'objet qui gère la structure de données sinon.
extern msetb *msetb_empty(int max);

//  msetb_put : ajoute num au multi ensemble associé à msb.
//   Renvoie une valeur non nulle en cas de dépassement de capacité.
//   Renvoie zéro sinon.
extern int msetb_put(msetb *msb, int num);

//  msetb_display : affiche le graphe d'appartenance du multi ensemble borné.
//    si l'entier est présent il est indiqué par une croix. Sinon rien n'est
//    affiché pour cet entier chaque entier est séparé par une tabulation.
extern void msetb_display(msetb *msb);

//  msetb_dispose : libère les ressources allouées à la structure de données
//    associée à *msbptr
extern void msetb_dispose(msetb **msbptr);

//  msetb_max : retourne la borne maximale du multi ensemble msbprt
extern int msetb_max(msetb *msbptr);

//TODO to remove
extern int msetb_debug(msetb *msb);
#endif
