#pragma once

#define MAX_AMIS 99                                                 //  5
#define MAX_COMPETENCES 5                                           //  5
#define TAILLE_GPE_MAX 100                                          //  20

#include "liste.h"

// Structure d'une entreprise et d'un groupe d'entreprises
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

// Structure d'une personne et d'un groupe de personnes
typedef struct personne
{
    int index;
    char nom[128];
    char prenom[128];
    char courriel[128];
    int adresse;
    char competence[MAX_COMPETENCES][128];
    struct personne *amis[MAX_AMIS];
    int entreprise;
} personne;

typedef struct groupePersonnes
{
    node* personnes;
} groupePersonnes;

// Structure d'un poste et d'un groupe de postes
typedef struct poste
{
    int index ;
    char titre[128] ;
    char competence[MAX_COMPETENCES][128] ;
    int entreprise ;
} postes ;

typedef struct groupePostes
{
    node* poste ;
} groupePostes ;


#include "maintenance.h"
#include "postes.h"
#include "entreprise.h"
#include "menu.h"
#include "personne.h"
#include "journal.h"