#pragma once

#include "groupe.h"
#include "postes.h"
#include "entreprise.h"

#include <stdbool.h>
#include <stdio.h>

/*Crée un profil avec le premier indice disponible*/
void creer_profil(char *nom, char *prenom, char *courriel, int adresse, char competence[5][128], int *collegue, int entreprise, groupePersonnes *gEmployes);

/*Supprime le profil d'une personne à un indice donné*/
void supprimer_profil (int index, groupePersonnes *gEmployes);

/*modifie le code postal d'une personne à un indice donné*/
int modifier_adresse(int indice, groupePersonnes *gEmployes, int nouv_adresse);

/*modifie l'entreprise d'une personne à un indice donné*/
int modifier_entreprise(int indice, groupePersonnes *gEmployes, int nouv_entre);

/*ajoute une compétence donnée à une personne donnée*/
int ajouter_competence(int indice, groupePersonnes *gEmployes, char comp[128]);

/*Transition d'employé à chercheur d'emploi*/
int quitter_entreprise(int indice, groupePersonnes *gEmployes);

/*Ajout d'un collègue à une personne*/
int ajouter_collegue(int indice, groupePersonnes *gEmployes, int col);

/*La personne d'indice donné rejoint une entreprise donnée et tous les employes de cette entreprise deviennent ses collègues
Il devient aussi le collègue de tous les employés*/
int rejoindre_entreprise(int indice, groupePersonnes *gEmployes, int entre);

/*Suppression d'un collègue donné par une personne*/
int supprimer_collegue(int indice, groupePersonnes *gEmployes, int col);

/*Recherche d'un poste en fonction des competences*/
int recherche_poste_comp(int indice, groupePersonnes *gEmployes, groupePostes* gPostes, groupeEntreprises *gEntre);

/*Recherche d'un poste en fonction du code postal*/
int recherche_poste_postal(int indice, groupePersonnes *gEmployes, groupePostes *gPostes, groupeEntreprises *gEntre);

/*Recherche parmi les anciens collègues de la personne d'indice donné si ily en a qui travaille dans l'entreprise d'index donné*/
int recherche_col_par_entre(int indice, groupePersonnes *gEmployes, int index);

/*Recherche parmi les anciens collègues ceux qui ont une compétence donnée*/
int recherche_col_comp(int indice, groupePersonnes *gEmployes, char comp[128]);



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


















int printemployes(groupePersonnes* gPe) ;