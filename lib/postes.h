#pragma once

#include <string>

#include "liste.h"
#include "entreprise.h"

typedef struct poste
{
    int index ;
    char titre[128] ;
    char competence[5][128] ;
    int entreprise ;
} postes ;

typedef struct groupePostes
{
    node* poste ;
} groupePostes ;

// Créé un groupe de postes à partir d'un flux donné
groupePostes* g_openPostesCSV(FILE* db) ;

// Affiche tous les postes
void AfficherPostes(groupePostes* g) ;

//Affiche un poste donné
void AfficherPoste(groupePostes* g, int index, groupeEntreprises *gEntre);

// Affiche tous les postes pourvu par l'entreprise donné par son index
void AfficherPostesEntreprise(groupeEntreprises* gE, groupePostes* gP, int index) ;

// Ajoute un poste au fichier postes.csv et au groupe de postes
int AjoutPoste(groupePostes *gP, char titre[128], int index, char competence[5][128]) ;

// Retourne l'index du dernier poste du groupe de postes
int LastPoste(groupePostes* gP) ;

// Supprime un poste du groupe poste
groupePostes* SupprimerPoste(groupePostes* gP, int const index) ;


// Met à jour le fichier poste.csv à partir du groupe passé en paramètres
void g_ecrirePoste(groupePostes* gP) ;

// Retourne 1 si le poste fait partie du groupe et qu'il appartient à l'entreprise qui le demande, 0 sinon
int ExistePosteEntreprise(groupePostes* gP, int const indexP, int const indexE) ;

// Supprime tous les postes associées à la même entreprise
groupePostes* SupprimerEntreprise_postes(groupePostes* gP, int const indexE) ;
