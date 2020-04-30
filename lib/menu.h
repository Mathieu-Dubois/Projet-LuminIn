#pragma once

#include <string>

#include "entreprise.h"
#include "postes.h"
#include "groupe.h"

/*==============================================================================================
 || FONCTION : MenuPrincipal
  ==============================================================================================
 || But : Affiche le menu principal permettant de s'identifier en tant qu'entreprise ou utisateur
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuPrincipal(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe) ;


/* ============================================================================================================
||
||                                  PARTIE ENTREPRISE
||
   ============================================================================================================ */

/*==============================================================================================
 || FONCTION : MenuEntreprise
  ==============================================================================================
 || But : Affiche le menu permettant à l'utilisateur de :
 ||       - se connecter sur le profil de son entreprise
 ||       - créer le profil de son entreprise 
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe) ;

/*==============================================================================================
 || FONCTION : MenuSeConnecterEntreprise
  ==============================================================================================
 || But : Affiche tous les index et nom des entreprises du groupe d'entreprise
 ||       et demande à l'utilisateur d'entrer le numéro de son entreprise
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuSeConnecterEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe) ;

/*==============================================================================================
 || FONCTION : MenuCreerEntreprise
  ==============================================================================================
 || But : Affiche le menu permettant à l'utilisateur de créer le profil de son entreprise
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuCreerEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe) ;

/*==============================================================================================
 || FONCTION : MenuProfilEntreprise
  ==============================================================================================
 || But : Affiche le menu avec toutes les fonctionnalités d'une entreprise connectée 
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     indexE : index de l'entreprise connectée
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuProfilEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE) ;

/*==============================================================================================
 || FONCTION : MenuConfirmerSuppressionEntreprise
  ==============================================================================================
 || But : Affiche le menu demandant confirmation à l'utilisateur avant de supprimer le profil 
 ||       de son entreprise
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     indexE : index de l'entreprise connectée (et donc à supprimer)
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuConfirmerSuppressionEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE) ;

/*==============================================================================================
 || FONCTION : MenuAfficherPostesDuneEntreprise
  ==============================================================================================
 || But : Affiche le menu où l'utilisateur peut voir tous les postes à pourvoir de son entreprise
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     indexE : index de l'entreprise connectée
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuAfficherPostesDuneEntreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexE) ;

/*==============================================================================================
 || FONCTION : MenuCreerPoste
  ==============================================================================================
 || But : Affiche le menu permettant à l'utilisateur de créer un poste à pourvoir
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     indexE : index de l'entreprise connectée
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuCreerPoste(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE) ;

/*==============================================================================================
 || FONCTION : MenuSupprimerPoste
  ==============================================================================================
 || But : Affiche tous les postes à pourvoir de l'entreprise connectée et demande à
 ||       l'utilisateur l'index du poste à supprimer
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     indexE : index de l'entreprise connectée
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuSupprimerPoste(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE) ;

/*==============================================================================================
 || FONCTION : MenuEntrepriseCherchePar
  ==============================================================================================
 || But : Affiche le menu permettant à une entreprise de chercher un chercheur d'emploi par 
 ||       compétence ou compétence et code postal
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     indexE : index de l'entreprise connectée
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuEntrepriseCherchePar(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE) ;







/* ============================================================================================================
||
||                                  PARTIE PERSONNE 
||
   ============================================================================================================ */


/*==============================================================================================
 || FONCTION : MenuCreer_Profil
  ==============================================================================================
 || But : Le menu/formulaire pour créer un profil employés ou chercheur d'emploi
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé 
  ============================================================================================== */
int MenuCreer_Profil(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe);

/*==============================================================================================
 || FONCTION : MenuModifier_Profil
  ==============================================================================================
 || But : le menu pour une modification du profil
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : Void
  ============================================================================================== */
void MenuModifier_Profil(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id);

/*==============================================================================================
 || FONCTION : MenuMod_Adresse
  ==============================================================================================
 || But : Le formulaire pour modifier son adresse
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int MenuMod_Adresse(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id);

/*==============================================================================================
 || FONCTION : Menu_mod_entreprise
  ==============================================================================================
 || But : Le formulaire pour mettre à jour son entreprise 
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menu_mod_entreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id);

/*==============================================================================================
 || FONCTION : Menuajouter_Competence
  ==============================================================================================
 || But : Le formulaire pour ajouter une compétence
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menuajouter_Competence(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id);

/*==============================================================================================
 || FONCTION : Menuquitter_entreprise
  ==============================================================================================
 || But : Le menu pour quitter son entreprise (passer en recherche d'emploi)
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menuquitter_entreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id) ;

/*==============================================================================================
 || FONCTION : printemployes
  ==============================================================================================
 || But : Print de la table employes
 ||
 || Paramètres :
 ||     gPe : pointeur sur un groupe de type groupe
  ============================================================================================== */
void printemployes (groupePersonnes *gPe);

/*==============================================================================================
 || FONCTION : Menusupprimer_profil
  ==============================================================================================
 || But : Le menu pour supprimer son profil
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menusupprimer_profil(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id);

/*==============================================================================================
 || FONCTION : Menuajouter_collegue
  ==============================================================================================
 || But : Le menu pour ajouter un collegue dans sa liste
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menuajouter_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id);

/*==============================================================================================
 || FONCTION : Menusupprimer_collegue
  ==============================================================================================
 || But : Le menu pour supprimer un collegue de sa liste
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menusupprimer_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id);

/*==============================================================================================
 || FONCTION : Menu_emploi
  ==============================================================================================
 || But : l'interface pour chercher un emploi
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menu_emploi(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id) ;

/*==============================================================================================
 || FONCTION : Menu_emploi_collegue
  ==============================================================================================
 || But : l'interface pour chercher un emploi à l'aide d'un collègue
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menu_emploi_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id) ;

/*==============================================================================================
 || FONCTION : Menuidentification
  ==============================================================================================
 || But : Menu pour s'identifier (Universel, pour employé comme chercheur d'emploi)
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int Menuidentification(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe);

/*==============================================================================================
 || FONCTION : CheckStatut
  ==============================================================================================
 || But : Vérifie si il s'agit d'un employé ou d'un chercheur d'emploi et sélectionne ainsi le menu adapté
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int CheckStatut(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe,int id);


/*==============================================================================================
 || FONCTION :  MenuChercheur
  ==============================================================================================
 || But : Menu principal pour les chercheur d'emploi
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int MenuChercheur(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int id) ;

/*==============================================================================================
 || FONCTION :  MenuEmploye
  ==============================================================================================
 || But : Menu principal pour les employe
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||     id : L'identifiant de l'utilisateur en cours
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int MenuEmploye(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int id) ;

/*==============================================================================================
 || FONCTION :  A_Implementer
  ==============================================================================================
 || But : Si une fonctionnalité présente dans le menu n'est pas encore implémentée
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     gPe : pointeur sur un groupe de type groupe
 ||
 || Retour : 
 ||          Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int A_Implementer(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe) ;

