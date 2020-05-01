#pragma once

#include "entreprise.h"
#include "postes.h"

/*==============================================================================================
 || FONCTION : AfficherDate
  ==============================================================================================
 || But : Récupérer la date et l'heure de l'OS (fonction trouvée sur internet)
 ||
 || Paramètre :
 ||     Aucun
 ||
 || Retour :
 ||     Un string contenant la date au format : jj-mm-aa hh-mm-ss
  ============================================================================================== */
string AfficherDate() ;

/*==============================================================================================
 || FONCTION : journal_OuvertureApplication
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant la date et l'heure de l'ouverture
 ||       de l'application
 ||
 || Paramètre :
 ||     Aucun
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_OuvertureApplication() ;

/*==============================================================================================
 || FONCTION : journal_FermetureApplication
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant la date et l'heure de la fermeture
 ||       de l'application
 ||
 || Paramètre :
 ||     Aucun
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_FermetureApplication() ;

/*==============================================================================================
 || FONCTION : journal_CreationEntreprise
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant les informations de l'entreprise créé
 ||
 || Paramètre :
 ||     e : pointeur sur une entreprise
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_CreationEntreprise(entreprise* e) ;

/*==============================================================================================
 || FONCTION : journal_ConnexionEntreprise
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant l'entreprise qui s'est connectée
 ||
 || Paramètre :
 ||     e : pointeur sur une entreprise
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_ConnexionEntreprise(entreprise* e) ;

/*==============================================================================================
 || FONCTION : journal_SuppressionEntreprise
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant l'entreprise qui a été supprimée
 ||
 || Paramètre :
 ||     e : pointeur sur une entreprise
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_SuppressionEntreprise(entreprise* e) ;

/*==============================================================================================
 || FONCTION : journal_SuppressionPoste
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant le poste qui a été supprimé
 ||
 || Paramètre :
 ||     p : pointeur sur un poste
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_SuppressionPoste(poste* p) ;

/*==============================================================================================
 || FONCTION : journal_CreationPoste
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant les informations du poste créé
 ||
 || Paramètre :
 ||     p : pointeur sur un poste
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_CreationPoste(poste* p) ;

/*==============================================================================================
 || FONCTION : journal_EntrepriseConsultePostes
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que l'entreprise connectée à consulté sa
 ||       liste des postes à pourvoir
 ||
 || Paramètre :
 ||     e : pointeur sur une entreprise
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_EntrepriseConsultePostes(entreprise* e) ;

/*==============================================================================================
 || FONCTION : journal_EntrepriseRechercheCompetence
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que l'entreprise a effectué une recherche
 ||       par compétence, et affiche la compétence
 ||
 || Paramètre :
 ||     e : pointeur sur une entreprise
 ||     competence : chaine de caractère contenant la compétence
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_EntrepriseRechercheCompetence(entreprise* e, char competence[128]) ;

/*==============================================================================================
 || FONCTION : journal_EntrepriseRechercheCompetenceEtCode
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que l'entreprise a effectué une recherche
 ||       par compétence et code postal, et affiche la compétence et le code postal
 ||
 || Paramètre :
 ||     e : pointeur sur une entreprise
 ||     competence : chaine de caractère contenant la compétence recherchée
 ||     code : entier contenant le code postal recherché
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_EntrepriseRechercheCompetenceEtCode(entreprise* e, char competence[128], int code) ;

/*==============================================================================================
 || FONCTION : journal_DeconnexionEntreprise
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant l'entreprise qui s'est déconnectée
 ||
 || Paramètre :
 ||     e : pointeur sur une entreprise
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_DeconnexionEntreprise(entreprise* e) ;