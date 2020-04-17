#pragma once

#include <string>

#include "entreprise.h"

// Affiche le menu principal
int MenuPrincipal(groupeEntreprises *gEntreprise) ;

// Permet à l'utilisateur de choisir s'il veut se connecter au profil de son entreprise ou s'il veut créer le profil de son entreprise
int MenuEntreprise(groupeEntreprises *gEntreprise) ;

// Permet à l'utilisateur de se connecter sur son profil entreprise
int SeConnecterEntreprise(groupeEntreprises *gEntreprise) ;

// Permet à l'utilisateur de renseigner les informations de son entreprise (nom, code postal, adresse mail)
int CreerEntreprise(groupeEntreprises *gEntreprise) ;

// Affiche le menu d'une entreprise une fois qu'elle s'est connectée
int ProfilEntreprise(groupeEntreprises *gEntreprise, int index) ;

// Demande la confirmation à l'utilisateur pour supprimer son profil entreprise
int ConfirmerSuppressionEntreprise(groupeEntreprises *gEntreprise, int index) ;


int MenuChercheur(groupeEntreprises *gEntreprise) ;
int MenuEmploye(groupeEntreprises *gEntreprise) ;
int A_Implementer(groupeEntreprises *gEntreprise) ;

