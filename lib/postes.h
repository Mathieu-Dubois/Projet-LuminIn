#pragma once
#include <string>
#include "bibliotheques.h"


/*==============================================================================================
 || FONCTION : g_openPostesCSV
  ==============================================================================================
 || But : Création d'un groupe de postes à partir d'un flux donné
 ||
 || Paramètre :
 ||     db : pointeur sur une structure FILE
 ||
 || Retour :
 ||     Retourne un pointeur vers le groupe de postes (ie : structure groupePoste)  
  ============================================================================================== */
groupePostes* g_openPostesCSV(FILE* db) ;

/*==============================================================================================
 || FONCTION : AfficherPostes
  ==============================================================================================
 || But : Afficher tous les postes à pourvoir
 ||
 || Paramètre :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void AfficherPostes(groupePostes* gP) ;

/*==============================================================================================
 || FONCTION : AfficherPoste
  ==============================================================================================
 || But : Afficher le titre d'un poste ainsi que l'adresse mail et le code postal
 ||       de l'entreprise qui le propose
 ||
 || Paramètre :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexP : index du poste que l'on veut afficher
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void AfficherPoste(groupePostes* gP, int indexP, groupeEntreprises *gE);

/*==============================================================================================
 || FONCTION : AfficherPostesEntreprise
  ==============================================================================================
 || But : Afficher tous les postes pourvus par une entreprise
 ||
 || Paramètre :
 ||     gE : pointeur sur un groupe de type groupeEntreprises
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexP : index du poste que l'on veut afficher
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void AfficherPostesEntreprise(groupeEntreprises* gE, groupePostes* gP, int indexP) ;

/*==============================================================================================
 || FONCTION : AjoutPoste
  ==============================================================================================
 || But : Ajouter un poste à un groupe de type groupePostes
 ||
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     titre : chaine de caractères contenant le titre du poste
 ||     indexE : entier contenant l'index de l'entreprise qui ajoute le poste
 ||     competence : un tableau qui peut contenir MAX_COMPETENCES compéteces maximum
 ||
 || Retour :
 ||     Retourne 0 si tout s'est bien passé
  ============================================================================================== */
int AjoutPoste(groupePostes *gP, char titre[128], int index, char competence[MAX_COMPETENCES][128]) ;

/*==============================================================================================
 || FONCTION : LastPoste
  ==============================================================================================
 || But : Déterminer l'index du dernier poste d'un groupe de type groupePostes
 ||
 || Paramètre :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||
 || Retour :
 ||     Un entier correspondant à l'index du dernier poste du groupe
  ============================================================================================== */
int LastPoste(groupePostes* gP) ;

/*==============================================================================================
 || FONCTION : SupprimerPoste
  ==============================================================================================
 || But : Supprimer un poste du groupe passé en paramètres et du fichier postes.csv
 ||     
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexP : index du poste que l'on doit supprimer
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void SupprimerPoste(groupePostes* gP, int const indexP) ;

/*==============================================================================================
 || FONCTION : g_ecrirePoste
  ==============================================================================================
 || But : Mettre à jour le fichier postes.csv à partir du groupe passé en paramètres
 ||     
 || Paramètre :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void g_ecrirePoste(groupePostes* gP) ;

/*==============================================================================================
 || FONCTION : ExistePosteEntreprise
  ==============================================================================================
 || But : Déterminer si un poste appartient bien à une entreprise
 ||
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexP : index du poste que l'on cherche
 ||     indexE : index de l'entreprise
 ||
 || Retour :
 ||     0 : l'entreprise ne fait pas partie du groupe
 ||     1 : l'entreprise fait partie du groupe
  ============================================================================================== */
int ExistePosteEntreprise(groupePostes* gP, int const indexP, int const indexE) ;

/*==============================================================================================
 || FONCTION : SupprimerEntreprise_postes
  ==============================================================================================
 || But : Supprimer tous les postes associés à la même entreprise
 ||
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexE : index de l'entreprise
 ||
 || Retour :
 ||     Retourne le groupe de postes mis à jour
  ============================================================================================== */
void SupprimerEntreprise_postes(groupePostes* gP, int const indexE) ;

/*==============================================================================================
 || FONCTION : gPoste_size
  ==============================================================================================
 || But : Déterminer la taille d'un groupe de type : groupePostes
 ||
 || Paramètre :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||
 || Retour :
 ||     Retourne la taille du groupe sous la forme d'un entier
  ============================================================================================== */
int gPoste_size(groupePostes* gP) ;

/*==============================================================================================
 || FONCTION : g_indexPoste
  ==============================================================================================
 || But : Accéder à un poste du groupe pour la manipuler
 ||
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexP : index du poste que l'on cherche
 ||
 || Retour :
 ||     Si le poste existe : retourne ce poste (ie : un pointeur sur une variable de type poste)
 ||     Si le poste n'existe pas : affiche retourne NULL
  ============================================================================================== */
poste* g_indexPoste(groupePostes* gP, int const indexP) ;

/*==============================================================================================
 || FONCTION : ExistePoste
  ==============================================================================================
 || But : Déterminer si un poste fait partie du groupe passé en paramètres
 ||
 || Paramètres :
 ||     gP : pointeur sur un groupe de type groupePostes
 ||     indexE : index du poste que l'on cherche
 ||
 || Retour :
 ||     0 : le poste ne fait pas partie du groupe
 ||     1 : le poste fait partie du groupe
  ============================================================================================== */
int ExistePoste(groupePostes* gP, int const indexP) ;

