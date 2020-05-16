#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "bibliotheques.h"

// Crée un groupe à partir d'un flux donné.
groupePersonnes* g_open(FILE* db);

//Ecris une table csv à partir d'un groupe donné
void g_ecrire(groupePersonnes* gPe);

// Retour la taille du groupe.
int g_size(groupePersonnes* g);

// Retourne la personne qui porte l'index donné.
personne* g_index(groupePersonnes* g, int const index);

// Enlève une personne du groupe.
// Tous les liens d'amitié vers cette personne supprimée doivent eux aussi être supprimés.
// 1. g = {[1,Alice,3;2] [2,Bob,3;1] [3,Charlie,1;2]}
// g_bestie(g, 2) => -1
// g_bestie(g, 3) => 1
// g_remove(g, 1) => {[2,Bob,3] [3,Charlie,2]}
// g_bestie(g, 2) => 3
// g_bestie(g, 3) => 2
//
// 2. g = {[1,Alice,3;2] [2,Bob,3;1] [3,Charlie,1;2;4] [4,Dave,3]}
// g_distance(g, 1, 4) => 1
// g_remove(g, 3) => {[1,Alice,2] [2,Bob,1] [4,Dave,]}
// g_distance(g, 1, 4) => -1
void g_remove(groupePersonnes* g, int const index);



// Réinitialise les fichiers csv à leur état initial
void ReinitialiserCSV() ;

// Fais une sauvegarde du journal pour ne pas le modifier quand on exécute le programme de test
void SauvegardeJournal() ;

// Restaure la sauvegarde du journal
void RestaurerJournal() ;




// // Détermine si deux personnes sont amies.
// // Retourne vrai si et seulement si la personne index_a compte la personne index_b parmi ses ami(e)s et que la personne index_b compte la personne index_a parmis ses ami(e)s.
// // g = {[1,Alice,3;2] [2,Bob,3;1] [3,Charlie,2]}
// // 1. g_friends(g, 1, 1) => false
// // 2. g_friends(g, 1, 2) => true
// // 3. g_friends(g, 1, 3) => false
// bool g_friends(groupePersonnes* g, int const index_a, int const index_b);

// // Détermine le(la) meilleur(e) ami(e) d'une personne.
// // Une personne a un(e) meilleur(e) ami(e) si le(le) premier(ère) ami(e) dans sa liste d'amis a cette même personne comme premier(ère) ami(e).
// // Retourne l'index de ce(tte) meilleur(e) ami(e) si il(elle) existe, sinon -1.
// // g = {[1,Alice,3;2] [2,Bob,3;1] [3,Charlie,1;2]}
// // 1. g_bestie(g, 1) => 3
// // 2. g_bestie(g, 2) => -1
// // 3. g_bestie(g, 3) => 1
// int g_bestie(groupePersonnes* g, int const index);

// // Détermine une amitié unidirectionelle.
// // Une personne a une amitié unidirectionnelle si elle compte dans sa liste d'amis une personne qui ne l'a pas dans sa liste d'amis.
// // Retourne vrai si et seulement si la personne index_a compte la personne index_b parmi ses ami(e)s et que la personne index_b ne compte pas la personne index_a parmis ses ami(e)s.
// // g = {[1,Alice,3;2] [2,Bob,3;1] [3,Charlie,2]}
// // 1. g_oneway(g, 1, 1) => false
// // 2. g_oneway(g, 1, 2) => false
// // 3. g_oneway(g, 1, 3) => true
// bool g_oneway(groupePersonnes* g, int const index_a, int const index_b);

// // Détermine s'il existe une chaîne d'amis entre la personne index_a et la personne index_b.
// // g = {[1,Alice,2] [2,Bob,1;4] [3,Charlie,2] [4,Dave,2;1]}
// // 1. g_linked(g, 1, 1) => false
// // 2. g_linked(g, 1, 2) => vrai
// // 3. g_linked(g, 1, 3) => faux
// // 4. g_linked(g, 3, 4) => vrai
// bool g_linked(groupePersonnes* g, int const index_a, int const index_b);

// // Détermine la longueur de la chaîne d'ami(e)s la plus courte entre deux personnes.
// // Retourne le longueur de la plus courte chaîne entre deux personnes si une chaîne existe, sinon -1.
// // g = {[1,Alice,3;2] [2,Bob,3;1;4] [3,Charlie,2] [4,Dave,2;1] [5,Eve,2;3;4]}
// // 1. g_distance(g, 1, 1) => -1
// // 2. g_distance(g, 1, 2) => 1
// // 3. g_distance(g, 1, 4) => 2
// // 4. g_distance(g, 4, 1) => 1
// // 5. g_distance(g, 1, 5) => -1
// int g_distance(groupePersonnes* g, int const index_a, int const index_b);


