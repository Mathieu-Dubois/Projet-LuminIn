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
int MenuPrincipal(groupeEntreprises *gE, groupePostes *gP, groupe *gPe) ;


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
int MenuEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe) ;

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
int MenuSeConnecterEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe) ;

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
int MenuCreerEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe) ;

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
int MenuProfilEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE) ;

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
int MenuConfirmerSuppressionEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE) ;

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
int MenuAfficherPostesDuneEntreprise(groupeEntreprises* gE, groupePostes *gP, groupe *gPe, int indexE) ;

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
int MenuCreerPoste(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE) ;

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
int MenuSupprimerPoste(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE) ;

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
int MenuEntrepriseCherchePar(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE) ;







//Le menu/formulaire pour créer un profil employés ou chercheur d'emploi
int MenuCreer_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//le menu pour une modification du profil
int MenuModifier_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//Le formulaire pour modifier son adresse
int MenuMod_Adresse(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);

//Le formulaire pour mettre à jour son entreprise 
int Menu_mod_entreprise(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne);





int MenuChercheur(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;
int MenuEmploye(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;
int A_Implementer(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne) ;

