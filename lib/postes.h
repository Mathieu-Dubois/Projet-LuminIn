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

// Affiche tous les postes pourvu par l'entreprise donné par son index
void AfficherPostes(groupeEntreprises* gE, groupePostes* gP, int index) ;