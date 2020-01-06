//  Partie interface du module mset_longinr

//  Le module mset_longint permet de gérer un multi ensemble de long int

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef MSET_LONG_INT__H
#define MSET_LONG_INT__H

#include <stddef.h>

//contient l'ensemble de nombre de type long int
typedef struct mset_longint mset_longint;

//Création d'un ensemble vide
extern mset_longint *mset_longint_empty(void);

//Ajout d'un nombre num à l'ensemble msli
extern int mset_longint_put(mset_longint *msli, long int num);

//Affichage de la liste de nombre
extern void mset_longint_display(mset_longint *msli);

//Nettoyage de la liste de nombre
extern void mset_longint_dispose(mset_longint *msliptr);
#endif
