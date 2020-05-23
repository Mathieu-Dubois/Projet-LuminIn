#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "bibliotheques.h"


/*==============================================================================================
 || FONCTION : ReinitialiserCSV
  ==============================================================================================
 || But : Réinitialiser les trois fichiers csv à leut état initial
 ||       Cela permet que les fichiers de départs soient identiques à chaque exécution du
 ||       programme de test.
 ||       La commande "make reset" fait exactement la même chose
 ||     
 || Paramètres :
 ||     Aucun
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void ReinitialiserCSV() ;

/*==============================================================================================
 || FONCTION : SauvegardeJournal
  ==============================================================================================
 || But : Réaliser une sauvegarde du journal dans le fichier journaltmp.txt
 ||     
 || Paramètres :
 ||     Aucun
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void SauvegardeJournal() ;

/*==============================================================================================
 || FONCTION : RestaurerJournal
  ==============================================================================================
 || But : Permet de restaurer la sauvegarde du journal (supprime journal.txt puis renomme 
 || journaltmp.txt en journal.txt)
 || Cela permet d'éviter que le journal soit modifié quand on lance le programme de test.
 || On veut en effet que je journal ne conseve que les manipulations réalisés dans l'application
 ||     
 || Paramètres :
 ||     Aucun
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void RestaurerJournal() ;

/*==============================================================================================
 || FONCTION : ViderGroupes
  ==============================================================================================
 || But : Vide les 3 groupes
 ||     
 || Paramètres :
 ||     gE :  pointeur sur un groupe de type groupeEntreprises
 ||     gPe : pointeur sur un groupe de type groupePersonnes
 ||     gP : pointeur sur un groupe de type groupePostes
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void ViderGroupes(groupeEntreprises* gE, groupePersonnes* gPe, groupePostes* gP) ;

/*==============================================================================================
 || FONCTION : SauvegardeCSV
  ==============================================================================================
 || But : Réaliser une sauvegarde des fichiers csv
 ||     
 || Paramètres :
 ||     Aucun
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void SauvegardeCSV() ;

/*==============================================================================================
 || FONCTION : RestaurerCSV
  ==============================================================================================
 || But : Permet de restaurer la sauvegarde des fichiers CSV 
 || Cela permet d'éviter que la base de données soit modifié quand on lance le programme de test.
 ||     
 || Paramètres :
 ||     Aucun
 ||
 || Retour :
 ||     Aucun
  ============================================================================================== */
void RestaurerCSV() ;