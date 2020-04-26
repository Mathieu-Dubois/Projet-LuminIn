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

//Le menu/formulaire pour créer un profil employés ou chercheur d'emploi
int MenuCreer_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//le menu pour une modification du profil
int MenuModifier_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//Le formulaire pour modifier son adresse
int MenuMod_Adresse(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//Le formulaire pour mettre à jour son entreprise 
int Menu_mod_entreprise(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

// Permet à une entreprise de créer un poste à pourvoir
int CreerPoste(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int indexE) ;

// Permet à une entreprise de choisir le poste qu'elle veut supprimer
int ChoixPosteSupprime(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int indexE) ;

// Affiche le menu de recherche pour une entreprise
int MenuEntrepriseCherchePar(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int indexE) ;

//Le menu/formulaire pour créer un profil employés ou chercheur d'emploi
int MenuCreer_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//le menu pour une modification du profil
int MenuModifier_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//Le formulaire pour modifier son adresse
int MenuMod_Adresse(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//Le formulaire pour mettre à jour son entreprise 
int Menu_mod_entreprise(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//Le formulaire pour ajouter une compétence
int Menuajouter_Competence(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

int MenuChercheur(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;
int MenuEmploye(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;
int A_Implementer(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;

