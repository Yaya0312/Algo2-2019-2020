//  Partie interface du module mset_longinr

//  Le module mset_longint permet de gérer un multi ensemble de long int

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef MSET_LONG_INT__H
#define MSET_LONG_INT__H

#include <stddef.h>

//  struct mset_longint, mset_longint : structure capable de gérer une structure
//    list dynamique
//  La structure de données ne stocke pas les objets mais des pointeurs vers ces
//    objets. 
typedef struct mset_longint mset_longint;

//  mset_longtint_empty : créé une structure de données qui contient un pointeur
//    vers une structure list. Renvoie un pointeur vers l'objet en cas de succès
//    et NULL en cas d'échec.
extern mset_longint *mset_longint_empty(void);

//  mset_longint_put : ajout d'un nombre num à la structure de donnée associée à
//    *msli. Renvoie 0 en cas de succès et -1 en cas d'échec
extern int mset_longint_put(mset_longint *msli, long int num);

//  mset_longint_display : affichage de la liste de nombre
extern void mset_longint_display(mset_longint *msli);

//  mset_longint_dispose : libère les ressources allouées à la structure de 
//    données associée à *msliptr puis affecte à *msliptr la valeur NULL
extern void mset_longint_dispose(mset_longint *msliptr);
#endif
