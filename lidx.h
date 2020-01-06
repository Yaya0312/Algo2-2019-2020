#ifndef LIDX__H
#define LIDX__H
#include "option.h"

typedef struct lidx lidx;

//Création d'un line indexer vide
extern lidx *lidx_empty();

//  Ajoute chaque mots du fichier qui a pour chemin path au line indexer lid
//    retourne ??
extern int lidx_add_file(lidx *lid, char *path);

//Ajoute chaque mots de la chaine de caractéres en tant que lid si il n'est
//  pas déjà présent
extern int lidx_add_string(lidx *lid, const char **string);

// Mets à jour l'index des lignes à partir du fichier stream
extern int lidx_add_stdin(lidx *lid, FILE *stream);

//Affiche le lidx
extern void lidx_print(lidx *lid);

//Definie les options d'affichage du line indexer lid avec les options opts
extern void lidx_set_options(lidx *lid, settings *opts);

//Nettoyage du lidx lidx
extern void lidx_dispose(lidx *lid);
#endif
