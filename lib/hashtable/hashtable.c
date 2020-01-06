//  Implantation polymorphe pour la spécification TABLE du TDA Table(T, T') dans
//    le cas d'une table de hachage par chainage séparé

#include <stdlib.h>
#include <stdint.h>
#include "hashtable.h"

//  Le nombre de compartiments du tableau de hachage est une puissance de 2. Il
//    vaut initialement 2^HT__LBNSLOTS_MIN. Dès le taux de remplissage de la
//    table de hachage est strictement supérieur à
//    (double) HT__LDFACT_MAX_NUMER / HT__LDFACT_MAX_DENOM, le nombre de
//    compartiments est multiplié par 2

#define HT__LBNSLOTS_MIN      6
#define HT__LDFACT_MAX_NUMER  1
#define HT__LDFACT_MAX_DENOM  1

//  Les définitions précédentes vont pour un nombre de compartiments initial de
//    64 et un seuil maximum de 1.0 ; ces définitions peuvent être modifiées.
//    Les directives qui suivent s'assurent de leur cohérence ; ces directives
//    ne doivent pas être modifiées

#define HT__NSLOTS_MIN \
  (1ULL << HT__LBNSLOTS_MIN)
#define HT__NENTRIESMAX_MIN \
  (HT__NSLOTS_MIN / HT__LDFACT_MAX_DENOM * HT__LDFACT_MAX_NUMER)

#if HT__LBNSLOTS_MIN < 0                                                       \
  || HT__LDFACT_MAX_NUMER < 0                                                  \
  || HT__LDFACT_MAX_DENOM < 1                                                  \
  || HT__NSLOTS_MIN == 0 || HT__NSLOTS_MIN > SIZE_MAX / 2                      \
  || HT__NENTRIESMAX_MIN == 0 || HT__NSLOTS_MIN > SIZE_MAX
#error Bad choice of HT__ constants
#endif

//  struct hashtable, hashtable : gestion du chainage séparé par liste dynamique
//    simplement chainée. Le composant compar mémorise la fonction de
//    comparaison des clés, hashfun, leur fonction de hachage. Le tableau de
//    hachage est alloué dynamiquement ; son adresse et le logarithme binaire de
//    sa longueur, autrement dit : le nombre de compartiments, sont mémorisés
//    par les composants hasharray et lbnslots. Le composant nfreeentries
//    mémorise le nombre d'entrées libres, autrement dit : la différence, dans
//    la configuration courante de la table de hachage, entre le nombre
//    d'entrées maximales associées au seuil et le nombre d'entrées. Le champ
//    null a un double usage dès lors que la table de hachage a été
//    initialisée : 1) tant que le tableau de hachage n'a pas été alloué,
//    la valeur de hasharray est l'adresse du champ null ; 2) la fonction de
//    recherche locale hashtable__search est toujours définie car la valeur du
//    champ null est NULL

//  L'ajout d'une nouvelle entrée a lieu en queue de liste. L'ordre induit est
//    respecté lors de tout agrandissement du tableau de hachage

typedef struct cell cell;

struct cell {
  const void *keyptr;
  const void *valptr;
  cell *next;
};

struct hashtable {
  int (*compar)(const void *, const void *);
  size_t (*hashfun)(const void *);
  cell **hasharray;
  cell *null;
  size_t lbnslots;
  size_t nfreeentries;
};

#define HALF(n)       ((n) >> 1)
#define POW2(p)       ((size_t) 1 << (p))
#define MODPOW2(n, p) ((n) % POW2(p))

//  hashtable__is_blank : teste si le tableau de hachage de la table de hachage
//    associée à ht n'a pas été alloué
static int hashtable__is_blank(const hashtable *ht) {
  return ht->hasharray == &ht->null;
}

//  hashtable__search : recherche dans la table de hachage associé à ht une clé
//    égale à celle d'adresse keyptr au sens de compar. Renvoi l'adresse du
//    pointeur qui repère la cellule qui contient cette occurrence si elle
//    existe. Renvoi sinon l'adresse du pointeur qui marque la fin de la liste
//    sinon
static cell **hashtable__search(const hashtable *ht, const void *keyptr) {
  cell * const *pp = &ht->hasharray[MODPOW2(ht->hashfun(keyptr), ht->lbnslots)];
  while (*pp != NULL && ht->compar(keyptr, (*pp)->keyptr) != 0) {
    pp = &(*pp)->next;
  }
  return (cell **) pp;
}

//  hashtable__add_enlarge : initialise ou agrandit le tableau de hachage de la
//    table de hachage associée à ht. Il est supposé que la valeur de
//    nfreeentries est nulle. Renvoie une valeur non nulle en cas de dépassement
//    de capacité. Renvoie sinon zéro
static int hashtable__add_enlarge(hashtable *ht) {
  int b;
  size_t lbm;
  size_t m;
  size_t m_;
  if ((b = hashtable__is_blank(ht))) {
    lbm = HT__LBNSLOTS_MIN;
    m = POW2(lbm);
    m_ = 0;
    ht->hasharray = NULL;
  } else {
    lbm = ht->lbnslots + 1;
    m = POW2(lbm);
    m_ = HALF(m);
  }
  cell **a;
  if (m > SIZE_MAX / sizeof(cell *)
      || (HT__LDFACT_MAX_NUMER > sizeof(void *)
      && HT__LDFACT_MAX_NUMER > HT__LDFACT_MAX_DENOM
      && m > SIZE_MAX / HT__LDFACT_MAX_NUMER * HT__LDFACT_MAX_DENOM)
      || (a = realloc(ht->hasharray, m * sizeof(cell *))) == NULL) {
    if (b) {
      ht->hasharray = &ht->null;
    }
    return -1;
  }
  if (b) {
    for (size_t k = 0; k < m; ++k) {
      a[k] = NULL;
    }
  } else {
    for (size_t k = 0; k < m_; ++k) {
      cell **pp_ = &a[k];
      cell **pp = &a[k + m_];
      while (*pp_ != NULL) {
        if (MODPOW2(ht->hashfun((*pp_)->keyptr), lbm) < m_) {
          pp_ = &(*pp_)->next;
        } else {
          *pp = *pp_;
          *pp_ = (*pp_)->next;
          pp = &(*pp)->next;
        }
      }
      *pp = NULL;
    }
  }
  ht->hasharray = a;
  ht->lbnslots = lbm;
  ht->nfreeentries
    = m / HT__LDFACT_MAX_DENOM * HT__LDFACT_MAX_NUMER
      - m_ / HT__LDFACT_MAX_DENOM * HT__LDFACT_MAX_NUMER;
  return 0;
}

hashtable *hashtable_empty(int (*compar)(const void *, const void *),
    size_t (*hashfun)(const void *)) {
  hashtable *ht = malloc(sizeof(hashtable));
  if (ht == NULL) {
    return NULL;
  }
  ht->compar = compar;
  ht->hashfun = hashfun;
  ht->hasharray = &ht->null;
  ht->null = NULL;
  ht->lbnslots = 0;
  ht->nfreeentries = 0;
  return ht;
}

const void *hashtable_add(hashtable *ht, const void *keyptr,
    const void *valptr) {
  if (valptr == NULL) {
    return NULL;
  }
  cell **pp = hashtable__search(ht, keyptr);
  if (*pp != NULL) {
    (*pp)->valptr = valptr;
  } else {
    if (ht->nfreeentries == 0) {
      if (hashtable__add_enlarge(ht) != 0) {
        return NULL;
      }
      pp = hashtable__search(ht, keyptr);
    }
    cell *p = malloc(sizeof(cell));
    if (p == NULL) {
      return NULL;
    }
    p->keyptr = keyptr;
    p->valptr = valptr;
    p->next = *pp;
    *pp = p;
    ht->nfreeentries -= 1;
  }
  return valptr;
}

const void *hashtable_remove(hashtable *ht, const void *keyptr) {
  cell **pp = hashtable__search(ht, keyptr);
  if (*pp == NULL) {
    return NULL;
  }
  cell *t = *pp;
  const void *valptr = t->valptr;
  *pp = t->next;
  free(t);
  ht->nfreeentries += 1;
  return valptr;
}

const void *hashtable_search(const hashtable *ht, const void *keyptr) {
  cell **pp = hashtable__search(ht, keyptr);
  return *pp == NULL ? NULL : (*pp)->valptr;
}

void hashtable_dispose(hashtable **htptr) {
  if (*htptr == NULL) {
    return;
  }
  if (!hashtable__is_blank(*htptr)) {
    size_t m = POW2((*htptr)->lbnslots);
    for (size_t k = 0; k < m; ++k) {
      cell *p = (*htptr)->hasharray[k];
      while (p != NULL) {
        cell *t = p;
        p = p->next;
        free(t);
      }
    }
    free((*htptr)->hasharray);
  }
  free(*htptr);
  *htptr = NULL;
}

#ifdef HASHTABLE_CHECKUP

void hashtable_get_checkup(const hashtable *ht,
    struct hashtable_checkup *htcuptr) {
  size_t m = (hashtable__is_blank(ht) ? 0 : POW2(ht->lbnslots));
  size_t n = m / HT__LDFACT_MAX_DENOM * HT__LDFACT_MAX_NUMER - ht->nfreeentries;
  size_t g = 0;
  double s = 0.0;
  for (size_t k = 0; k < m; ++k) {
    size_t f = 0;
    const cell *p = ht->hasharray[k];
    while (p != NULL) {
      ++f;
      p = p->next;
    }
    if (f > g) {
      g = f;
    }
    s += (double) f * (double) (f + 1) / 2.0;
  }
  double r = (double) n / (double) m;
  *htcuptr = (struct hashtable_checkup) {
    .nslots = m,
    .nentries = n,
    .ldfactmax = (double) HT__LDFACT_MAX_NUMER / (double) HT__LDFACT_MAX_DENOM,
    .ldfactcurr = r,
    .maxlen = g,
    .postheo = (n == 0 ? 0.0 : 1.0 + (r - 1.0 / (double) m) / 2.0),
    .poscurr = s / (double) n,
  };
}

#define P_TITLE(textstream, name) \
  fprintf(textstream, "--- Info: %s\n", name)
#define P_VALUE(textstream, name, format, value) \
  fprintf(textstream, "%12s\t" format "\n", name, value)

int hashtable_display_checkup(const hashtable *ht, FILE *textstream) {
  struct hashtable_checkup htcu;
  hashtable_get_checkup(ht, &htcu);
  return 0 > P_TITLE(textstream, "Hashtable checkup")
         || 0 > P_VALUE(textstream, "n.slots", "%zu", htcu.nslots)
         || 0 > P_VALUE(textstream, "n.entries", "%zu", htcu.nentries)
         || 0 > P_VALUE(textstream, "ld.fact.max", "%lf", htcu.ldfactmax)
         || 0 > P_VALUE(textstream, "ld.fact.curr", "%lf", htcu.ldfactcurr)
         || 0 > P_VALUE(textstream, "max.len", "%zu", htcu.maxlen)
         || 0 > P_VALUE(textstream, "pos.theo", "%lf", htcu.postheo)
         || 0 > P_VALUE(textstream, "pos.curr", "%lf", htcu.poscurr);
}

#endif
