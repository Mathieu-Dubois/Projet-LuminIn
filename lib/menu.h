#pragma once

#include <string>

#include "entreprise.h"
#include "postes.h"
#include "groupe.h"

// Affiche le menu principal
int MenuPrincipal(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;

// Permet à l'utilisateur de choisir s'il veut se connecter au profil de son entreprise ou s'il veut créer le profil de son entreprise
int MenuEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;

// Permet à l'utilisateur de se connecter sur son profil entreprise
int SeConnecterEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;

// Permet à l'utilisateur de renseigner les informations de son entreprise (nom, code postal, adresse mail)
int CreerEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;

// Affiche le menu d'une entreprise une fois qu'elle s'est connectée
int ProfilEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int index) ;

// Demande la confirmation à l'utilisateur pour supprimer son profil entreprise
int ConfirmerSuppressionEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int index) ;

// Affiche le menu où l'entreprise voit tous ces poste à pourvoir
int ListeDesPostes(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne, int index) ;

// Permet à une entreprise de créer un poste à pourvoir
int CreerPoste(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int indexE) ;

// Permet à une entreprise de choisir le poste qu'elle veut supprimer
int ChoixPosteSupprime(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int indexE) ;

// Affiche le menu de recherche pour une entreprise
int MenuEntrepriseCherchePar(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int indexE) ;


int MenuChercheur(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;
int MenuEmploye(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;
int A_Implementer(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;

