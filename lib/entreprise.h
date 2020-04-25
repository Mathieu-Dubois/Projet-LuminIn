#pragma once

#include <string>

#include "liste.h"

typedef struct entreprise
{
    int index ;
    char nom[40] ;
    int code_postal;
    char courriel[128] ;
} entreprise ;

typedef struct groupeEntreprises
{
    node* entreprise ;
} groupeEntreprises ;

// Créé un groupe d'entreprise à partir d'un flux donné
groupeEntreprises* g_openEntreprisesCSV(FILE* db) ;

// Retourne la taille du groupe d'etreprises
int gEntreprise_size(groupeEntreprises* g) ;

// Affiche l'index et le nom de toutes les entreprises
void AfficherEntreprises(groupeEntreprises* g) ;

// Ajoute une entreprise au fichier "entreprises.csv" et au groupe entreprise
int AjoutEntreprise(groupeEntreprises *groupeEntr, char nom[40], int code_postal, char courriel[128]) ;

// Retourne l'index de la dernière entreprise du groupe
int LastEntreprise(groupeEntreprises* g) ;

// Retourne 1 si l'entreprise fait partie du groupe, 0 sinon
int ExisteEntreprise(groupeEntreprises*g, int const index) ;

// Retourne l'entreprise correspondant à l'index passé en paramètres
entreprise* g_indexEntreprise(groupeEntreprises* g, int const index) ;

// Supprime l'entreprise passée en paramètre (du groupe et du csv) plus les poste à pourvoir de cette entreprise
groupeEntreprises* SupprimerEntreprise(groupeEntreprises* g, int const index) ;

// Met à jour le fichier entreprises.csv à partir du groupe passé en paramètres
void g_ecrireEntreprise(groupeEntreprises* g) ;


