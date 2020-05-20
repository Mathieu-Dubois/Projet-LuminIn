#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "bibliotheques.h"

/*==============================================================================================
 || FONCTION : g_open
  ==============================================================================================
 || But : Création d'un groupe de personnes à partir d'un flux donné
 ||
 || Paramètre :
 ||     db : pointeur sur une structure FILE
 ||
 || Retour :
 ||     Retourne un pointeur vers le groupe de personnes (ie : structure groupePersonnes)  
  ============================================================================================== */
groupePersonnes* g_open(FILE* db);

/*==============================================================================================
 || FONCTION : g_ecrire
  ==============================================================================================
 || But : Mettre à jour le fichier employes.csv à partir du groupe passé en paramètres
 ||     
 || Paramètre :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void g_ecrire(groupePersonnes* gPe);

/*==============================================================================================
 || FONCTION : g_size
  ==============================================================================================
 || But : Déterminer la taille d'un groupe de type : groupePersonnes
 ||
 || Paramètre :
 ||     g : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     Retourne la taille du groupe sous la forme d'un entier
  ============================================================================================== */
int g_size(groupePersonnes* g);

/*==============================================================================================
 || FONCTION : g_index
  ==============================================================================================
 || But : Accéder à une personne du groupe pour la manipuler
 ||
 || Paramètres :
 ||     g : pointeur sur un groupe de type groupeEntreprises
 ||     index : index de la personne que l'on cherche
 ||
 || Retour :
 ||     Si la personne existe : retourne cette personne (ie : un pointeur sur une variable de type personne)
 ||     Si la personne n'existe pas : retourne NULL
  ============================================================================================== */
personne* g_index(groupePersonnes* g, int const index);

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
 || FONCTION : ExisteCollegue
  ==============================================================================================
 || But : Déterminer si une personne fait partie du réseau de collègue d'une autre personne
 ||
 || Paramètres :
 ||     pe : pointeur sur une personne (celle dont on étudie le réseau)
 ||     indexCo : index du collègue
 ||
 || Retour :
 ||     0 : la personne ne fait pas partie du groupe
 ||     1 : la personne fait partie du groupe
  ============================================================================================== */
int ExisteCollegue(personne* pe, int const indexCo) ;

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

/*==============================================================================================
 || FONCTION : AfficherAmis
  ==============================================================================================
 || But : Afficher l'index, le nom et le prénom de tous les collègues d'une personne
 ||
 || Paramètre :
 ||     pe : pointeur sur une personne
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void AfficherAmis(personne* pe);

/*==============================================================================================
 || FONCTION : creer_profil
  ==============================================================================================
 || But : Ajouter une personne à un groupe de type groupePersonnes au premier indice disponible
 ||
 || Paramètres :
 ||     nom : chaine de caractères contenant le nom de la personne
 ||     prenom : chaine de caractères contenant le prenom de la personne
 ||     courriel : chaine de caractères contenant l'adresse mail de la personne
 ||     competence : tableau de contenant les compétences de la personne
 ||     collegue : tableau d'entier contenant les index des collègues de la personne
 ||     entreprise : entier contenant l'index de l'entreprise de la personne (ou -1 si chercheur)
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void creer_profil(char *nom, char *prenom, char *courriel, int adresse, char competence[MAX_COMPETENCES][128], int *collegue, int entreprise, groupePersonnes *gPe);

/*==============================================================================================
 || FONCTION : supprimer_profil
  ==============================================================================================
 || But : Supprimer une personne du groupe passé en paramètres et du fichier employes.csv
 ||     
 || Paramètres :
 ||     index : index de la personne que l'on doit supprimer
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void supprimer_profil (int index, groupePersonnes *gPe);

/*==============================================================================================
 || FONCTION : modifier_adresse
  ==============================================================================================
 || But : Modifier le code postal d'une personne
 ||     
 || Paramètres :
 ||     indice : index de la personne dont on veut modifier l'adresse
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     nouv_adresse : entier contenant le nouveau code postal
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si le nouveau code postal est identique à l'ancien
 ||     2 si l'on ne trouve pas la personne dans le groupe
  ============================================================================================== */
int modifier_adresse(int indice, groupePersonnes *gPe, int nouv_adresse);

/*==============================================================================================
 || FONCTION : modifier_mail
  ==============================================================================================
 || But : Modifier l'adresse mail d'une personne
 ||     
 || Paramètres :
 ||     indice : index de la personne dont on veut modifier l'adresse mail
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     new_mail : chaine de caractères contenant la nouvelle adresse mail
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si la nouvelle adresse mail est identique à l'ancienne
 ||     2 si l'on ne trouve pas la personne dans le groupe
  ============================================================================================== */
int modifier_mail(int indice, groupePersonnes *gPe, char* new_mail);

/*==============================================================================================
 || FONCTION : modifier_entreprise
  ==============================================================================================
 || But : Modifier l'entreprise d'une personne
 ||     
 || Paramètres :
 ||     indice : index de la personne dont on veut modifier l'entreprise
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     nouv_entre : entier contenant l'index de la nouvelle entreprise
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si la nouvelle entreprise est identique à l'ancienne
 ||     2 si l'on ne trouve pas la personne dans le groupe
  ============================================================================================== */
int modifier_entreprise(int indice, groupePersonnes *gPe, int nouv_entre);

/*==============================================================================================
 || FONCTION : ajouter_competence
  ==============================================================================================
 || But : Ajouter une compétence au profil de la personne
 ||     
 || Paramètres :
 ||     indice : index de la personne dont on veut ajouter une compétence
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     comp : chaine de caractère contenant la nouvelle compétence
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si la personne possède déjà cette compétence
 ||     2 si la personne a déjà le nombre maximum de compétences
 ||     3 si l'on ne trouve pas la personne dans le groupe
  ============================================================================================== */
int ajouter_competence(int indice, groupePersonnes *gPe, char comp[128]);

/*==============================================================================================
 || FONCTION : quitter_entreprise
  ==============================================================================================
 || But : Faire la transition d'employé à chercheur d'emploi
 ||     
 || Paramètres :
 ||     indice : index de la personne qui quitte son entreprise
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si la personne est déjà chercheur d'emploi
 ||     2 si l'on ne trouve pas la personne dans le groupe
  ============================================================================================== */
int quitter_entreprise(int indice, groupePersonnes *gPe);

/*==============================================================================================
 || FONCTION : ajouter_collegue
  ==============================================================================================
 || But : Ajouter un collègue au réseau de la personne
 ||     
 || Paramètres :
 ||     indice : index de la personne dont on veut ajouter un collègue
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     col : entier contenant l'index de la nouvelle personne
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si la personne possède déjà ce collègue dans son réseau
 ||     3 si l'on ne trouve pas la personne dans le groupe
 ||     4 si la personne a déjà le nombre de collègues maximum
 ||     5 si la personne veut s'ajouter elle même en collègue
  ============================================================================================== */
int ajouter_collegue(int indice, groupePersonnes *gPe, int col);

/*==============================================================================================
 || FONCTION : supprimer_collegue
  ==============================================================================================
 || But : Supprimer un collègue du réseau de la personne
 ||     
 || Paramètres :
 ||     indice : index de la personne dont on veut supprimer un collègue
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     col : entier contenant l'index de la  personne à supprimer
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si la personne ne possède pas ce collègue dans son réseau
 ||     3 si l'on ne trouve pas la personne dans le groupe
  ============================================================================================== */
int supprimer_collegue(int indice, groupePersonnes *gPe, int col);

/*==============================================================================================
 || FONCTION : g_remove
  ==============================================================================================
 || But : Enlève une personne du groupe et efface son index du réseau de tous ses collègues
 ||     
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePersonnes
 ||     index : entier contenant l'index de la personne à supprimer du groupe
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void g_remove(groupePersonnes* g, int const index);

/*==============================================================================================
 || FONCTION : AfficherNonCollegues
  ==============================================================================================
 || But : Afficher l'index, le nom et le prénom de touyes les personnes qui ne font pas partie
 ||       du réseau de la personne
 ||
 || Paramètre :
 ||     pe : pointeur sur une personne
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||
 || Retour :
 ||     0 si tout s'est bien passé
 ||     1 si il y a aucune personne à afficher
  ============================================================================================== */
int AfficherNonCollegues(personne* pe, groupePersonnes* gPe) ;

/*==============================================================================================
 || FONCTION : ColleguesAutomatiques
  ==============================================================================================
 || But : Quand une personne rejoint une entreprise, ajouter l'index de la personne au réseau de
 ||       collègues de tous les employés de l'entreprise.
 ||       Ajoute également l'index de tous les employés de l'entreprise au réseau de la personne
 ||       si ils n'en faisaitent pas déjà partie
 ||
 || Paramètre :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     pe : pointeur sur une personne
 ||     indexE : index de l'entreprise qu'a rejoint la personne
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void ColleguesAutomatiques(groupePersonnes* gPe, personne* pe, int indexE) ;


