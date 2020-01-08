//  Partie interface du module set_longint

//  Le module set_longint permet de gérer un ensemble de long int

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef SET_LONG_INT__H
#define SET_LONG_INT__H

#include <stddef.h>

//  struct set_longint, set_longint : structure capable de gérer une structure
//    list dynamique
//  La structure de données ne stocke pas les objets mais des pointeurs vers ces
//    objets.
typedef struct set_longint set_longint;

//  mset_longtint_empty : créé une structure de données qui contient un pointeur
//    vers une structure list. Renvoie un pointeur vers l'objet en cas de succès
//    et NULL en cas d'échec.
extern set_longint *set_longint_empty(void);

//  set_longint_put : ajout d'un nombre num à la structure de donnée associée à
//    *msli. Renvoie 0 en cas de succès et -1 en cas d'échec
extern int set_longint_put(set_longint *msli, long int num);

//  set_longint_display : affichage de la liste de nombre
extern void set_longint_display(set_longint *msli);

//  set_longint_dispose : libère les ressources allouées à la structure de
//    données associée à *msliptr puis affecte à *msliptr la valeur NULL
extern void set_longint_dispose(set_longint *msliptr);
#endif
