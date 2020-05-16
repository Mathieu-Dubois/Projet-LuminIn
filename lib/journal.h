#pragma once

#include "entreprise.h"
#include "postes.h"
#include "groupe.h"


/* ============================================================================================================
||
||                                 JOURNAL PARTIE GENERALE 
||
   ============================================================================================================ */

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



/* ============================================================================================================
||
||                                 JOURNAL PARTIE ENTREPRISE 
||
   ============================================================================================================ */

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
 || But : Ajouter une entrée au journal renseignant les informations du poste créée
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



/* ============================================================================================================
||
||                                 JOURNAL PARTIE PERSONNE 
||
  ============================================================================================================ */

/*==============================================================================================
 || FONCTION : journal_ConnexionPersonne
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant la personne qui s'est connectée
 ||
 || Paramètre :
 ||     p : pointeur sur une personne
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_ConnexionPersonne(personne* p) ;

/*==============================================================================================
 || FONCTION : journal_DeconnexionPersonne
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant la personne qui s'est déconnectée
 ||
 || Paramètre :
 ||     p : pointeur sur une personne
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_DeconnexionPersonne(personne* p) ;

/*==============================================================================================
 || FONCTION : journal_CreationPersonne
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant les informations de la personne créée
 ||
 || Paramètre :
 ||     p : pointeur sur une personne
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_CreationPersonne(personne* p) ;

/*==============================================================================================
 || FONCTION : journal_SuppressionPersonne
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant la personne qui a été supprimée
 ||
 || Paramètre :
 ||     p : pointeur sur une personne
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_SuppressionPersonne(personne* p) ;

/*==============================================================================================
 || FONCTION : journal_QuitterEntreprise
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a quitté son entreprise
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     e : pointeur sur l'entreprise quitté
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_QuitterEntreprise(personne* p, entreprise* e) ;

/*==============================================================================================
 || FONCTION : journal_PersonneMod_CodePostal
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a modifié son code postal
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     code_postal : entier contenant le nouveau code postal
 ||     new_code_postal : entier contenant le nouveau code postal
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_PersonneMod_CodePostal(personne* p, int code_postal, int new_code_postal) ;

/*==============================================================================================
 || FONCTION : journal_Personneajouter_Competence
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a ajouté une compétence
 ||       à son profil
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     competence : chaine de caractère contenant la nouvelle compétence
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_Personneajouter_Competence(personne* p, char competence[128]) ;

/*==============================================================================================
 || FONCTION : journal_Personne_mod_entreprise
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a changé d'entreprise
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     e : pointeur sur l'entreprise actuelle de la personne
 ||     new_e : pointeur sur la nouvelle entreprise
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_Personne_mod_entreprise(personne* p, entreprise* e, entreprise*  new_e) ;

/*==============================================================================================
 || FONCTION : journal_PersonneAjouter_Collegue
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a ajouté un collègue à son
 ||       réseau
 ||
 || Paramètres :
 ||     p : pointeur sur la personne connectée
 ||    np : pointeur sur le collègue
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_PersonneAjouter_Collegue(personne* p, personne* np) ;

/*==============================================================================================
 || FONCTION : journal_PersonneSupprimer_Collegue
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a supprimé un collègue de
 ||       son réseau
 ||
 || Paramètres :
 ||     p : pointeur sur la personne connectée
 ||    np : pointeur sur le collègue
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_PersonneSupprimer_Collegue(personne* p, personne* np) ;

/*==============================================================================================
 || FONCTION : journal_PersonneRecherchePosteParCompetence
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche
 ||       de poste par compétence, et affiche la compétence
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     competence : chaine de caractère contenant la compétence
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_PersonneRecherchePosteParCompetence(personne* p, char competence[128]) ;

/*==============================================================================================
 || FONCTION : journal_PersonneRecherchePosteParCompetenceEtCode
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche
 ||       de poste par compétence et code, et affiche la compétence et le code
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     competence : chaine de caractère contenant la compétence
 ||     code : int contenant le code postal
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_PersonneRecherchePosteParCompetenceEtCode(personne* p, char competence[128], int code) ;

/*==============================================================================================
 || FONCTION : journal_PersonneRechercheCollegueParCompetence
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche
 ||       de collègue par compétence, et affiche la compétence
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     competence : chaine de caractère contenant la compétence
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_PersonneRechercheCollegueParCompetence(personne* p, char competence[128]) ;

/*==============================================================================================
 || FONCTION : journal_PersonneRechercheCollegueParEntreprise
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche
 ||       de collègue par entreprise, et affiche l'entreprise
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     e : pointeur sur une personne
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_PersonneRechercheCollegueParEntreprise(personne* p, entreprise* e) ;

/*==============================================================================================
 || FONCTION : journal_Personne_modifier_mail
  ==============================================================================================
 || But : Ajouter une entrée au journal renseignant que la personne a modifié son adresse mail
 ||
 || Paramètres :
 ||     p : pointeur sur une personne
 ||     mail : chaine de caractère contenant l'ancienne adresse mail
 ||     newmail : chaine de caractère contenant la nouvelle adresse mail
 ||
 || Retour :
 ||     Aucun 
  ============================================================================================== */
void journal_Personne_modifier_mail(personne* p, char mail[128], char newmail[128]) ;