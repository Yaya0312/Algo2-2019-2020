#ifndef LIDX__H
#define LIDX__H
#include "option.h"

//  struct lidx, lidx : structure permettant de stocker la table de hashage
//    hashtable contenant les mots du lexique en tant que key et une struct
//    ht_val en value, un holdall filenames contenant
//    tous les noms de fichier représentant un lexique et un holdall words
//    contenant tous les strings qui appartiennent au lexique mais qui n'était
//    pas dans un fichier, enfin, il y a aussi une struct options qui
//    permet de stocker les options qui seront appliqués au line indexer
//  La structure de données ne stocke pas les objets mais des pointeurs vers ces
//    objets.
typedef struct lidx lidx;

//  lidx_empty : créé une structure de données qui contient une hashtable vide,
//    ainsi que deux holdall vide. Renvoie un pointeur vers l'objet en cas de
//    succès, NULL en cas d'échec. options sera def
// ???????????????????????????????
extern lidx *lidx_empty();

//  lidx_add_file : ouvre le fichier donné dans path, ajoute le nom du fichier
//    dans le holdall correspondant se trouvant dans lid, puis ajoute chaques
//    mots dans la hashtable de lid. Renvoie 0 en cas de succès et -1 en cas
//    d'échec
extern int lidx_add_file(lidx *lid, char *path);

//  lidx_add_string : ajoute le ou les mots contenus dans dans string dans la
//    hashtable contenue dans lid. Renvoie 0 en cas de succès et -1 en cas
//    d'échec
extern int lidx_add_string(lidx *lid, const char **string);

//  lidx_add_stdin : mets à jour l'index des lignes à partir du fichier stream.
//    Renvoie 0 en cas de succès et -1 en cas d'échec
extern int lidx_add_stdin(lidx *lid, FILE *stream);

//  lidx_print : vérifie les options si il y en a et les appliques sur les mots,
//    puis affiche sur la sortie standard les résultats attendus par l'utilisa-
//    teur
extern void lidx_print(lidx *lid);

//  lidx_set_options : définie les options d'affichage pour les mots contenus
//    dans la hashtable de lid avec les options opts
extern void lidx_set_options(lidx *lid, options *opts);

//  lidx_dispose : libère les ressources allouées à la structure de données
//    associée à *lid puis affecte à *lid la valeur NULL
extern void lidx_dispose(lidx *lid);
#endif
