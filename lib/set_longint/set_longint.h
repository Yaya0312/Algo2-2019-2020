//  Partie interface du module set_longint

//  Le module set_longint permet de gérer un ensemble de long int

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef SET_LONG_INT__H
#define SET_LONG_INT__H

#include <stddef.h>

//  struct set_longint, set_longint : structure capable de gérer une liste
//    dynamique simplement chainée sur le type long int
typedef struct set_longint set_longint;

//  mset_longtint_empty : création d'un ensemble est initialement vide.
//    Renvoie un pointeur vers l'objet en cas de succès, NULL en cas d'échec
extern set_longint *set_longint_empty(void);

//  set_longint_put : insère une copie de *num dans l'ensemble associée à
//    sli. Renvoie xptr en cas de succès et NULL en cas d'échec
extern const long int *set_longint_put(set_longint *sli, const long int *num);

//  set_longint_display : affichage de la liste de nombre
extern void set_longint_display(set_longint *sli);

//  set_longint_dispose : si sliptr ne vaut pas NULL, libère les ressources
//    allouées à sliptr ainsi qu'à la liste associée puis affecte la valeur NULL
//    à sliptr
extern void set_longint_dispose(set_longint *sliptr);
#endif
