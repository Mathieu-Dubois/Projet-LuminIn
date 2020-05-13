#pragma once

#include "liste.h"
#include "groupe.h"

typedef struct entreprise
{
    int index ;
    char nom[40] ;
    int code_postal;
    char courriel[128] ;
} entreprise ;

typedef struct groupeEntreprises
{
    node* entreprise ;
} groupeEntreprises ;


/*==============================================================================================
 || FONCTION : g_openEntrepriseCSV
  ==============================================================================================
 || But : Création d'un groupe d'entreprises à partir d'un flux donné
 ||
 || Paramètre :
 ||     db : pointeur sur une structure FILE
 ||
 || Retour :
 ||     Retourne un pointeur vers le groupe d'entreprises (ie : structure groupeEntreprises)  
  ============================================================================================== */
groupeEntreprises* g_openEntreprisesCSV(FILE* db) ;

/*==============================================================================================
 || FONCTION : gEntreprise_size
  ==============================================================================================
 || But : Déterminer la taille d'un groupe de type : groupeEntreprises
 ||
 || Paramètre :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||
 || Retour :
 ||     Retourne la taille du groupe sous la forme d'un entier
  ============================================================================================== */
int gEntreprise_size(groupeEntreprises* gE) ;

/*==============================================================================================
 || FONCTION : AfficherEntreprises
  ==============================================================================================
 || But : Afficher l'index et le nom de toutes les entreprises d'un même groupe
 ||
 || Paramètre :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void AfficherEntreprises(groupeEntreprises* gE) ;

/*==============================================================================================
 || FONCTION : AjoutEntreprise
  ==============================================================================================
 || But : Ajouter une entreprise à un groupe de type groupeEntreprises
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     nom : chaine de caractères contenant le nom de l'entreprise
 ||     code_postal : entier contenant le code postal de l'entreprise
 ||     courriel : chaine de caractères contenant l'adresse mail de l'entreprise
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void AjoutEntreprise(groupeEntreprises *gE, char nom[40], int code_postal, char courriel[128]) ;

/*==============================================================================================
 || FONCTION : LastEntreprise
  ==============================================================================================
 || But : Déterminer l'index de la dernière entreprise d'un groupe de type groupeEntreprises
 ||
 || Paramètre :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||
 || Retour :
 ||     Un entier correspondant à l'index de la dernière entreprise du groupe
  ============================================================================================== */
int LastEntreprise(groupeEntreprises* gE) ;

/*==============================================================================================
 || FONCTION : ExisteEntreprise
  ==============================================================================================
 || But : Déterminer si une entreprise fait partie du groupe passé en paramètres
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     indexE : index de l'entreprise que l'on cherche
 ||
 || Retour :
 ||     0 : l'entreprise ne fait pas partie du groupe
 ||     1 : l'entreprise fait partie du groupe
  ============================================================================================== */
int ExisteEntreprise(groupeEntreprises* gE, int const indexE) ;

/*==============================================================================================
 || FONCTION : g_indexEntreprise
  ==============================================================================================
 || But : Accéder à une entreprise du groupe pour la manipuler
 ||
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     indexE : index de l'entreprise que l'on cherche
 ||
 || Retour :
 ||     Si l'entreprise existe : retourne cette entreprise (ie : un pointeur sur une variable de type entreprise)
 ||     Si l'entreprise n'existe pas : affiche un message d'erreur et retourne NULL
  ============================================================================================== */
entreprise* g_indexEntreprise(groupeEntreprises* gE, int const indexE) ;

/*==============================================================================================
 || FONCTION : SupprimerEntreprise
  ==============================================================================================
 || But : Supprimer une entreprise du groupe passé en paramètres et du fichier entreprises.csv
 ||     
 || Paramètres :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     indexE : index de l'entreprise que l'on doit supprimer
 ||
 || Retour :
 ||     Retourne le groupe d'entreprise mis à jour
  ============================================================================================== */
groupeEntreprises* SupprimerEntreprise(groupeEntreprises* gE, int const indexE) ;

/*==============================================================================================
 || FONCTION : g_ecrireEntreprise
  ==============================================================================================
 || But : Mettre à jour le fichier entreprises.csv à partir du groupe passé en paramètres
 ||     
 || Paramètre :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void g_ecrireEntreprise(groupeEntreprises* gE) ;

/*==============================================================================================
 || FONCTION : EntrepriseRechercheParCompetence
  ==============================================================================================
 || But : Afficher le nom, le prénom et l'adresse mail de tous les chercheurs d'emploi possédant la compétence demandée
 ||     
 || Paramètres :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     competence : une chaine de caractère contenant la compétence demandée
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void EntrepriseRechercheParCompetence(groupePersonnes* gPe, char competence[128]) ;

/*==============================================================================================
 || FONCTION : EntrepriseRechercheParCompetenceEtCode
  ==============================================================================================
 || But : Afficher le nom, le prénom et l'adresse mail de tous les chercheurs d'emploi possédant la compétence et le code postal demandée
 ||     
 || Paramètres :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     competence : une chaine de caractère contenant la compétence demandée
 ||     code_postal : un entier contenant  le code postal demandé
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void EntrepriseRechercheParCompetenceEtCode(groupePersonnes* gPe, char competence[128], int code_postal) ;

/*==============================================================================================
 || FONCTION : EntrepriseRechercheParCompetenceEtCode
  ==============================================================================================
 || // But : Supprimer tous les employés d'une entreprise
 ||     
 || Paramètres :
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     indexE : index de l'entreprise dont on veut licencier tous les employés
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
groupePersonnes* LicencierToutLeMonde(groupePersonnes* gPe, groupeEntreprises* gE, int indexE) ;
