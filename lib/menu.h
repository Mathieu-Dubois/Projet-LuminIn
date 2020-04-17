#pragma once

#include <string>

#include "entreprise.h"

// Affiche le menu principal
int MenuPrincipal(groupeEntreprises *groupeEntr) ;

// Permet à l'utilisateur de choisir s'il veut se connecter au profil de son entreprise ou s'il veut créer le profil de son entreprise
int MenuEntreprise(groupeEntreprises *groupeEntr) ;

// Permet à l'utilisateur de se connecter sur son profil entreprise
int SeConnecterEntreprise(groupeEntreprises *groupeEntr) ;

// Permet à l'utilisateur de renseigner les informations de son entreprise (nom, code postal, adresse mail)
int CreerEntreprise(groupeEntreprises *groupeEntr) ;

// Affiche le menu d'une entreprise une fois qu'elle s'est connectée
int ProfilEntreprise(groupeEntreprises *groupeEntr, int index) ;

// Demande la confirmation à l'utilisateur pour supprimer son profil
int ConfirmerSuppressionEntreprise(groupeEntreprises *groupeEntr, int index) ;


int MenuChercheur(groupeEntreprises *groupeEntr) ;
int MenuEmploye(groupeEntreprises *groupeEntr) ;
int A_Implementer(groupeEntreprises *groupeEntr) ;

