#pragma once

#define MAX_AMIS 99                                                 //  5
#define MAX_COMPETENCES 5                                           //  5
#define TAILLE_GPE_MAX 100                                          //  20

#include "liste.h"
#include <regex>

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


#include "postes.h"
#include "entreprise.h"
#include "menu.h"
#include "personne.h"
#include "maintenance.h"
#include "journal.h"

// Définitions des ER nécessaires à la saisie sécurisée

// regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
// regex patternNom {"[a-zA-Z]{1}[a-zA-Zéèêëïîôöàâäç'_ ]{0,39}"} ; // Un nom d'entreprise ne doit pas avoir de chiffres et ne peut pas commencer par un caractère spécial
// regex patternCodePostal {"[1-9]{1}[0-9]{4}"} ; // Un code postal doit contenir 5 chiffres et ne doit pas commencer par 0
// regex patternMail {"[\\w\\._%+-]{1,30}@[\\w_]{2,20}\\.[A-Za-z]{2,3}"} ;

// Prénom d'une personne Jean-Jacques ok Jean Jacques pas ok