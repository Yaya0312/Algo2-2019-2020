#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef LIST__H
#define LIST__H

//  struct list, list : structure capable de gérer une liste dynamique
//    simplement chainée sur le type const void*
//  La structure de données ne stocke pas les objets mais des pointeurs vers ces
//    objets. 
typedef struct list list;

//  list_empty : crée un objet de type list. La liste est initialement vide.
//    Renvoie un pointeur vers l'objet en cas de succès, NULL en cas d'échec
extern list *list_empty();

//  list_is_empty : renvoie true ou false selon que la liste associée à l est
//    vide ou non
extern bool list_is_empty(const list *l);

//  list_insert_head : insère une copie de *xptr en queue de la liste associée à
//    l. Renvoie xptr en cas de succès et NULL en cas d'échec
extern const void *list_add(list *l, const void *xptr);

//  list_last_element : renvoie la ligne du dernier élément ajouté dans la liste
//    l. Renvoie NULL si la liste est vide
extern const void *list_last_element(const list *l);

//  list_display : affiche toutes les valeurs stockés par la liste l
extern void list_display(list *l);

//  list dispose :  si l ne vaut pas NULL, libère les ressources allouées à
//    l ainsi qu'à la liste associée puis affecte la valeur NULL à l
extern void list_dispose(list *l);

#endif
