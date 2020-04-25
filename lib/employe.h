#pragma once

#include "groupe.h"
#include "postes.h"

#include <stdbool.h>
#include <stdio.h>

/*Crée un profil avec le premier indice disponible*/
void creer_profil(char *nom, char *prenom, char *courriel, int adresse, char competence[5][128], int *collegue, int entreprise, groupe *gEmployes);

/*Supprime le profil d'une personne à un indice donné*/
void supprimer_profil (int index, groupe *gEmployes);

/*modifie le code postal d'une personne à un indice donné*/
int modifier_adresse(int indice, groupe *gEmployes, int nouv_adresse);

/*modifie l'entreprise d'une personne à un indice donné*/
int modifier_entreprise(int indice, groupe *gEmployes, int nouv_entre);

/*ajoute une compétence donnée à une personne donnée*/
int ajouter_competence(int indice, groupe *gEmployes, char comp[128]);

/*Transition d'employé à chercheur d'emploi*/
int quitter_entreprise(int indice, groupe *gEmployes);

/*Ajout d'un collègue à une personne*/
int ajouter_collegue(int indice, groupe *gEmployes, int col);

/*La personne d'indice donné rejoint une entreprise donnée et tous les employes de cette entreprise deviennent ses collègues
Il devient aussi le collègue de tous les employés*/
int rejoindre_entreprise(int indice, groupe *gEmployes, int entre);

/*Suppression d'un collègue donné par une personne*/
int supprimer_collegue(int indice, groupe *gEmployes, int col);

/*Recherche d'un poste en fonction des competences*/
int recherche_poste_comp(int indice, groupe *gEmployes, groupePostes* gPostes);