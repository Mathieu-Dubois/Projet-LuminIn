#pragma once

#include <string>

#include "liste.h"

typedef struct entreprise
{
    int index ;
    char nom[40] ;
    char code_postal[10];
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
int AjoutEntreprise(groupeEntreprises *groupeEntr, char nom[40], char code_postal[10], char courriel[128]) ;

// Retourne l'index de la dernière entreprise du groupe
int LastEntreprise(groupeEntreprises* g) ;

