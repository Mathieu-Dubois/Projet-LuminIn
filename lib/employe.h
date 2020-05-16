#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "bibliotheques.h"

/*Crée un profil avec le premier indice disponible*/
void creer_profil(char *nom, char *prenom, char *courriel, int adresse, char competence[MAX_COMPETENCES][128], int *collegue, int entreprise, groupePersonnes *gPe);

/*Supprime le profil d'une personne à un indice donné*/
void supprimer_profil (int index, groupePersonnes *gPe);

/*modifie le code postal d'une personne à un indice donné*/
int modifier_adresse(int indice, groupePersonnes *gPe, int nouv_adresse);

/*modifier adresse mail*/
int modifier_mail(int indice, groupePersonnes *gPe, char* new_mail);

/*modifie l'entreprise d'une personne à un indice donné*/
int modifier_entreprise(int indice, groupePersonnes *gPe, int nouv_entre);

/*ajoute une compétence donnée à une personne donnée*/
int ajouter_competence(int indice, groupePersonnes *gPe, char comp[128]);

/*Transition d'employé à chercheur d'emploi*/
int quitter_entreprise(int indice, groupePersonnes *gPe);

/*Ajout d'un collègue à une personne*/
int ajouter_collegue(int indice, groupePersonnes *gPe, int col);

/*La personne d'indice donné rejoint une entreprise donnée et tous les employes de cette entreprise deviennent ses collègues
Il devient aussi le collègue de tous les employés*/
int rejoindre_entreprise(int indice, groupePersonnes *gPe, int entre);

/*Suppression d'un collègue donné par une personne*/
int supprimer_collegue(int indice, groupePersonnes *gPe, int col);

/*==============================================================================================
 || FONCTION : AfficherPersonnes
  ==============================================================================================
 || But : Afficher l'index, le nom et le prénom de toutes les personnes d'un même groupe
 ||
 || Paramètre :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void AfficherPersonnes(groupePersonnes* gPe) ;

/*Affiche l'index, le nom et le prénom de toutes les personnes que cette personne a en ami*/
void AfficherAmis(groupePersonnes* gPe, int index);

/*==============================================================================================
 || FONCTION : ExistePersonne
  ==============================================================================================
 || But : Déterminer si une personne fait partie du groupe passé en paramètres
 ||
 || Paramètres :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     indexP : index de la personne que l'on cherche
 ||
 || Retour :
 ||     0 : la personne ne fait pas partie du groupe
 ||     1 : la personne fait partie du groupe
  ============================================================================================== */
int ExistePersonne(groupePersonnes *gPe, int const indexP) ;

/*==============================================================================================
 || FONCTION : LastPersonne
  ==============================================================================================
 || But : Déterminer l'index de la dernière personne d'un groupe de type groupePersonnes
 ||
 || Paramètre :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     Un entier correspondant à l'index de la dernière personne du groupe
  ============================================================================================== */
int LastPersonne(groupePersonnes* gPe) ;

/*==============================================================================================
 || FONCTION : PersonneRecherchePosteParCompetence
  ==============================================================================================
 || But : Afficher les informations de tous les postes à pourvoir ayant dans leur description
 || au moins une compétence du chercheur d'emploi
 ||     
 || Paramètres :
 ||     pe : pointeur sur une personne (celui qui fait la recherche)
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void PersonneRecherchePosteParCompetence(personne* pe, groupePostes* gP, groupeEntreprises* gE) ;

/*==============================================================================================
 || FONCTION : PersonneRecherchePosteParCompetenceEtCode
  ==============================================================================================
 || But : Afficher les informations de tous les postes à pourvoir ayant dans leur description
 || au moins une compétence du chercheur d'emploi ssi l'entreprise qui propose ce poste à le
 || même code postal
 ||     
 || Paramètres :
 ||     pe : pointeur sur une personne (celui qui fait la recherche)
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void PersonneRecherchePosteParCompetenceEtCode(personne* pe, groupePostes* gP, groupeEntreprises* gE) ;

/*==============================================================================================
 || FONCTION : PersonneRechercheCollegueParEntreprise
  ==============================================================================================
 || But : Afficher les informations de tous les collègues de son réseau qui travaillent
 || actuellement dans l'entreprise demandée
 ||     
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexPe : index de la personne faisant la recherche
 ||     indexE : index de l'entreprise recherchée  
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void PersonneRechercheCollegueParEntreprise(groupePersonnes* gPe, int indexPe, int indexE) ;

/*==============================================================================================
 || FONCTION : PersonneRechercheCollegueParCompetence
  ==============================================================================================
 || But : Afficher les informations de tous les collègues de son réseau qui travaillent dans une
 ||       entreprise proposant un poste avec une compétence en commum avec la personne qui fait
 ||       la recherche
 ||     
 || Paramètres :
 ||       pe : pointeur sur une personne (celui qui fait la recherche)
 ||       gE : pointeur sur un groupe de type groupeEntreprises
 ||       gP : pointeur sur un groupe de type groupePostes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void PersonneRechercheCollegueParCompetence(personne* pe, groupeEntreprises* gE, groupePostes* gP) ;


int printemployes(groupePersonnes* gPe) ;









// Cimetière ***********************************************************************************

// /*Recherche d'un poste en fonction des competences*/
// int recherche_poste_comp(int indice, groupePersonnes *gPe, groupePostes* gPostes, groupeEntreprises *gEntre);

// /*Recherche d'un poste en fonction du code postal*/
// int recherche_poste_postal(int indice, groupePersonnes *gPe, groupePostes *gPostes, groupeEntreprises *gEntre);

// /*Recherche parmi les anciens collègues de la personne d'indice donné si ily en a qui travaille dans l'entreprise d'index donné*/
// int recherche_col_par_entre(int indice, groupePersonnes *gPe, int index);

// /*Recherche parmi les anciens collègues ceux qui ont une compétence donnée*/
// int recherche_col_comp(int indice, groupePersonnes *gPe, char comp[128]);