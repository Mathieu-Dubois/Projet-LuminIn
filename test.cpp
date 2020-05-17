#include <iostream>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
using namespace std ;
#include "lib/bibliotheques.h"

int tests_executes = 0;
int tests_reussis = 0;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

// Incrémente le nombre de test exécutés de 1.
// Si le test réussi, incrémente le nombre de tests réussis de 1.
#define TEST(x) tests_executes += 1;    \
                if(x)                   \
                {                       \
                    tests_reussis += 1; \
                    printf("[SUCCES] ");\
                }                       \
                else                    \
                {                       \
                    printf("[ECHEC ] ");\
                }                       \
                printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n");


int main()
{   
    // On commence par réinitialiser les fichiers CSV à leur état "de base"
    ReinitialiserCSV() ;
    // On fait une sauvegarde du journal qu'on viendra restituer à la fin du programme de test
    // Ainsi le programme de test ne modifiera pas la journal (uniquement l'application qui peut le modifier)
    SauvegardeJournal() ;

    
/* ============================================================================================================
||
||                                 CREATION DES TROIS GROUPES
||
   ============================================================================================================ */
    // Lecture de la DB vers une liste en mémoire.
    // Création du groupe d'entreprises
    groupeEntreprises *gE = NULL;
    {
        FILE *dbE = NULL ;
        dbE = fopen("entreprises.csv", "r");
        gE = g_openEntreprisesCSV(dbE);
        fclose(dbE);
    }

    // Lecture de la DB vers une liste en mémoire.
    // Création du groupe de postes
    groupePostes *gP = NULL ;
    {
        FILE *dbP = NULL ;
        dbP = fopen("postes.csv", "r");
        gP = g_openPostesCSV(dbP);
        fclose(dbP);
    }

    // Lecture de la DB vers une liste en mémoire.
    // Création du groupe de personnes 
    groupePersonnes *gPe = NULL ;
    {
        FILE *dbPe = NULL ;
        dbPe = fopen("employes.csv", "r");
        gPe = g_open(dbPe);
        fclose(dbPe);
    }

/* ============================================================================================================
||
||                                 TEST DES FONCTIONS DU FICHIER : entreprise.h
||
   ============================================================================================================ */
    // Test de la fonction g_openEntreprisesCSV
    TEST(gE != NULL);
    // Test de la fonction gEntreprise_size
    TEST(gEntreprise_size(gE) == 11);
    // Test de la fonction g_indexEntreprise
    TEST(g_indexEntreprise(gE,20) == NULL) ;
        // On vérifie la première entreprise
        TEST(g_indexEntreprise(gE,1)->index == 1) ;
        TEST(strcmp(g_indexEntreprise(gE,1)->nom, "Disney") == 0) ;
        TEST(g_indexEntreprise(gE,1)->code_postal == 77700) ;
        TEST(strcmp(g_indexEntreprise(gE,1)->courriel, "walt@disney.com") == 0) ;
        // On vérifie la dernière entreprise
        TEST(g_indexEntreprise(gE,11)->index == 11) ;
        TEST(strcmp(g_indexEntreprise(gE,11)->nom, "Decathlon") == 0) ;
        TEST(g_indexEntreprise(gE,11)->code_postal == 96521) ;
        TEST(strcmp(g_indexEntreprise(gE,11)->courriel, "contact@decathlon.com") == 0) ;
        // On vérifie quelques entreprises entre les deux
        TEST(g_indexEntreprise(gE,7)->index == 7) ;
        TEST(strcmp(g_indexEntreprise(gE,10)->nom, "La Grande Recree") == 0) ;
        TEST(g_indexEntreprise(gE,3)->code_postal == 65058) ;
        TEST(strcmp(g_indexEntreprise(gE,6)->courriel, "nimbusdeuxmille@patronus.com") == 0) ;
    // Test de la fonction LastEntreprise
    TEST(LastEntreprise(gE) == 11) ;
    // Test de la fonction ExisteEntreprise
    TEST(ExisteEntreprise(gE,1) == 1) ;
    TEST(ExisteEntreprise(gE,11) == 1) ;
    TEST(ExisteEntreprise(gE,7) == 1) ;
    TEST(ExisteEntreprise(gE,0) == 0) ;
    TEST(ExisteEntreprise(gE,22) == 0) ;
    // Test de la fonction AjoutEntreprise
    string s_nomE = "Carglass" ;
    string s_courrielE = "contact@carglass.com" ;
    size_t size = s_nomE.size() + 1 ;
    char c_nomE[40];
    strncpy(c_nomE, s_nomE.c_str(), size) ;
    size = s_courrielE.size() + 1 ;
    char c_courrielE[128];
    strncpy(c_courrielE, s_courrielE.c_str(), size) ;
    AjoutEntreprise(gE,c_nomE,54710,c_courrielE) ;
    TEST(gEntreprise_size(gE) == 12);
    TEST(g_indexEntreprise(gE,12)->index == 12) ;
    TEST(strcmp(g_indexEntreprise(gE,12)->nom, "Carglass") == 0) ;
    TEST(g_indexEntreprise(gE,12)->code_postal == 54710) ;
    TEST(strcmp(g_indexEntreprise(gE,12)->courriel, "contact@carglass.com") == 0) ;
    TEST(LastEntreprise(gE) == 12) ;
    // Test des fonctions de recherche pour une entreprise
        // L'entreprise 1 fait une recherche de personne par compétence
        // Les compétences que propose cette entreprise sont :
        // poste 1 : comedie et gag
        // poste 4 : danse et sport
        // poste 7 : chant
        // parmi les chercheurs d'emploi :
        // Mouse Minnie a les compétences comédie, chant et danse
        // Lourson Winnie a la compétence comedie
        // Mua Sissy a la compétence danse
        // Seul ces trois personnes doivent apparaître dans le résultat de la recherche (et une seule fois)
        cout << "======================================== Test recherche 1" << endl ;
        EntrepriseRecherchePersonneParCompetence(gPe,gP,1) ;
        cout << "======================================== Test recherche 1 validé" << endl ;
        // L'entreprise 1 fait une recherche de personne par compétence et code postal
        // Tous les paramètres sont identiques à la recherche précédente
        // Sauf qu'il n'y a que Mouse Minnie qui a le même code postal que l'entreprise
        // Elle doit être la seule à apparaitre dans les résultats
        cout << "======================================== Test recherche 2" << endl ;
        EntrepriseRecherchePersonneParCompetenceEtCode(gPe,gP,g_indexEntreprise(gE,1)) ;
        cout << "======================================== Test recherche 2 validé" << endl ;
        // L'entreprise 11 fait une recherche de personne par compétence
        // L'entreprise ne propose qu'un seul poste avec la compétence sport
        // Parmi les chercheurs d'emploi, seule Mua Sissy a la compétence sport
        // Elle doit donc être la seule à apparaitre dans le résultat de la recherche
        cout << "======================================== Test recherche 3" << endl ;
        EntrepriseRecherchePersonneParCompetence(gPe,gP,11) ;
        cout << "======================================== Test recherche 3 validé" << endl ;
        // L'entreprise 11 fait une recherche de personne par compétence et par code postal
        // Tous les paramètres sont identiques à la recherche précédente
        // Cependant, Mua Sissy n'a pas le même code postal que l'entreprise 11
        // La recherche affiche aucun résultat
        cout << "======================================== Test recherche 4" << endl ;
        EntrepriseRecherchePersonneParCompetenceEtCode(gPe,gP,g_indexEntreprise(gE,11)) ;
        cout << "======================================== Test recherche 4 validé" << endl ;
    // Test de la fonction LicencierToutLeMonde
    LicencierToutLeMonde(gPe,gE,1) ;
    TEST(g_index(gPe,1)->entreprise == -1) ;
    TEST(g_index(gPe,3)->entreprise == -1) ;
    TEST(g_index(gPe,4)->entreprise == -1) ; 
    // Test de la fonction SupprimerEntreprise
        // On supprime une entreprise du milieu
        SupprimerEntreprise(gE,7) ;
        TEST(LastEntreprise(gE) == 12) ;
        TEST(gEntreprise_size(gE) == 11);
        TEST(g_indexEntreprise(gE,7) == NULL) ;
        // On supprime la première entreprise
        SupprimerEntreprise(gE,1) ;
        TEST(LastEntreprise(gE) == 12) ;
        TEST(gEntreprise_size(gE) == 10);
        TEST(g_indexEntreprise(gE,1) == NULL) ;
        // On supprime les deux dernières entreprises
        SupprimerEntreprise(gE,12) ;
        SupprimerEntreprise(gE,11) ;
        TEST(LastEntreprise(gE) == 10) ;
        TEST(gEntreprise_size(gE) == 8);
        TEST(g_indexEntreprise(gE,12) == NULL) ;
        TEST(g_indexEntreprise(gE,11) == NULL) ;
    // On fait le propre dans les fichiers csv pour tester la suite
    ReinitialiserCSV() ;

/* ============================================================================================================
||
||                                 TEST DES FONCTIONS DU FICHIER : postes.h
||
   ============================================================================================================ */
    // Test de la fonction g_openPostesCSV
    TEST(gP != NULL);
    // Test de la fonction gPoste_size
    TEST(gPoste_size(gP) == 10);
    // Test de la fonction g_indexPoste
    TEST(g_indexPoste(gP,20) == NULL) ;
        // On vérifie le premier poste
        TEST(g_indexPoste(gP,1)->index == 1) ;
        TEST(strcmp(g_indexPoste(gP,1)->titre, "Acteur") == 0) ;
        TEST(g_indexPoste(gP,1)->entreprise == 1) ;
        TEST(strcmp(g_indexPoste(gP,1)->competence[1], "gag") == 0) ;
        // On vérifie le dernier poste
        TEST(g_indexPoste(gP,10)->index == 10) ;
        TEST(strcmp(g_indexPoste(gP,10)->titre, "Developpeur") == 0) ;
        TEST(g_indexPoste(gP,10)->entreprise == 2) ;
        TEST(strcmp(g_indexPoste(gP,10)->competence[0], "informatique") == 0) ;
        // On vérifie quelques postes entre les deux
        TEST(g_indexPoste(gP,8)->index == 8) ;
        TEST(strcmp(g_indexPoste(gP,8)->titre, "Professeur de sport") == 0) ;
        TEST(g_indexPoste(gP,3)->entreprise == 5) ;
        TEST(strcmp(g_indexPoste(gP,6)->competence[0], "magie") == 0) ;
    // Test de la fonction LastPoste
    TEST(LastPoste(gP) == 10) ;
    // Test de la fonction ExistePoste
    TEST(ExistePoste(gP,1) == 1) ;
    TEST(ExistePoste(gP,10) == 1) ;
    TEST(ExistePoste(gP,7) == 1) ;
    TEST(ExistePoste(gP,0) == 0) ;
    TEST(ExistePoste(gP,22) == 0) ;
    // Test de la fonction ExistePosteEntreprise
    TEST(ExistePosteEntreprise(gP,1,1) == 1) ;
    TEST(ExistePosteEntreprise(gP,4,1) == 1) ;
    TEST(ExistePosteEntreprise(gP,7,1) == 1) ;
    TEST(ExistePosteEntreprise(gP,8,1) == 0) ;
    TEST(ExistePosteEntreprise(gP,5,1) == 0) ;
    TEST(ExistePosteEntreprise(gP,6,6) == 1) ;
    TEST(ExistePosteEntreprise(gP,3,5) == 1) ;
    TEST(ExistePosteEntreprise(gP,3,2) == 0) ;
    // Test de la fonction AjoutPoste
    string s_titreP = "Boulanger" ;
    string s_comp0 = "ponctuel" ;
    string s_comp1 = "patisserie" ;
    string s_comp2 = "cuisine" ;
    char tab_comp[MAX_COMPETENCES][128] = {'\0'} ;
    size = s_titreP.size() + 1 ;
    char c_titreP[128];
    strncpy(c_titreP, s_titreP.c_str(), size) ;
    size = s_comp0.size() + 1 ;
    strncpy(tab_comp[0], s_comp0.c_str(), size) ;
    size = s_comp1.size() + 1 ;
    strncpy(tab_comp[1], s_comp1.c_str(), size) ;
    size = s_comp2.size() + 1 ;
    strncpy(tab_comp[2], s_comp2.c_str(), size) ;
    AjoutPoste(gP,c_titreP,5,tab_comp) ;
    TEST(gPoste_size(gP) == 11);
    TEST(g_indexPoste(gP,11)->index == 11) ;
    TEST(strcmp(g_indexPoste(gP,11)->titre, "Boulanger") == 0) ;
    TEST(g_indexPoste(gP,11)->entreprise == 5) ;
    TEST(strcmp(g_indexPoste(gP,11)->competence[0], "ponctuel") == 0) ;
    TEST(strcmp(g_indexPoste(gP,11)->competence[2], "cuisine") == 0) ;
    TEST(LastPoste(gP) == 11) ;
    // Test de la fonction SupprimerPoste
    SupprimerPoste(gP,8) ;
    TEST(LastPoste(gP) == 11) ;
    TEST(gPoste_size(gP) == 10);
    // Test de la fonction SupprimerEntreprise_postes
    SupprimerEntreprise_postes(gP,1) ;
    TEST(gPoste_size(gP) == 7);
    TEST(LastPoste(gP) == 11) ;
    TEST(g_indexPoste(gP,1) == NULL) ;
    TEST(g_indexPoste(gP,4) == NULL) ;
    TEST(g_indexPoste(gP,7) == NULL) ;
    // On fait le propre dans les fichiers csv pour tester la suite
    ReinitialiserCSV() ;

/* ============================================================================================================
||
||                                 TEST DES FONCTIONS DU FICHIER : employe.h
||
   ============================================================================================================ */
    // Test de la fonction g_open
    TEST(gPe != NULL);
    // Test de la fonction g_size
    TEST(g_size(gPe) == 19);
    // Test de la fonction g_index
    TEST(g_index(gPe,20) == NULL) ;
        // On vérifie la première personne
        TEST(g_index(gPe,1)->index == 1) ;
        TEST(strcmp(g_index(gPe,1)->nom, "Mouse") == 0) ;
        TEST(strcmp(g_index(gPe,1)->prenom, "Mickey") == 0) ;
        TEST(g_index(gPe,1)->adresse == 77700) ;
        TEST(strcmp(g_index(gPe,1)->courriel, "mickey@mickeyville.com") == 0) ;
        TEST(strcmp(g_index(gPe,1)->amis[0]->prenom, "Minnie") == 0) ;
        TEST(g_index(gPe,1)->amis[5] == NULL) ;
        TEST(strcmp(g_index(gPe,1)->competence[0], "comedie") == 0) ;
        TEST(strcmp(g_index(gPe,1)->competence[1], "chant") == 0) ;
        TEST(g_index(gPe,1)->competence[2][0] == '\0') ;
        // On vérifie la dernière personne
        TEST(g_index(gPe,19)->index == 19) ;
        TEST(strcmp(g_index(gPe,19)->nom, "Fitcat") == 0) ;
        TEST(strcmp(g_index(gPe,19)->prenom, "Juju") == 0) ;
        TEST(g_index(gPe,19)->adresse == 81000) ;
        TEST(strcmp(g_index(gPe,19)->courriel, "etcafaitbimbamboum@pshitvroum") == 0) ;
        TEST(strcmp(g_index(gPe,19)->amis[0]->prenom, "Tibo") == 0) ;
        TEST(g_index(gPe,19)->amis[5] == NULL) ;
        TEST(strcmp(g_index(gPe,19)->competence[0], "sport") == 0) ;
        TEST(strcmp(g_index(gPe,19)->competence[1], "danse") == 0) ;
        TEST(g_index(gPe,19)->competence[2][0] == '\0') ;
        // On vérifie quelques personnes entre les deux
        TEST(g_index(gPe,7)->index == 7) ;
        TEST(strcmp(g_index(gPe,10)->nom, "Dumbledore") == 0) ;
        TEST(g_index(gPe,3)->adresse == 77730) ;
        TEST(strcmp(g_index(gPe,6)->courriel, "tidoublegreou@youpi.com") == 0) ;
        TEST(strcmp(g_index(gPe,12)->amis[0]->prenom, "Mathieu") == 0) ;
        TEST(strcmp(g_index(gPe,6)->amis[5]->prenom, "Theo") == 0) ;
        TEST(strcmp(g_index(gPe,6)->amis[6]->prenom, "Monon") == 0) ;
        TEST(g_index(gPe,7)->amis[5] == NULL) ;
        TEST(strcmp(g_index(gPe,13)->competence[0], "perseverant") == 0) ;
        TEST(strcmp(g_index(gPe,6)->competence[1], "chant") == 0) ;
        TEST(g_index(gPe,17)->competence[2][0] == '\0') ;
    // Test de la fonction LastPersonne
    TEST(LastPersonne(gPe) == 19) ;
    // Test de la fonction ExistePersonne
    TEST(ExistePersonne(gPe,1) == 1) ;
    TEST(ExistePersonne(gPe,19) == 1) ;
    TEST(ExistePersonne(gPe,0) == 0) ;
    TEST(ExistePersonne(gPe,32) == 0) ;
    TEST(ExistePersonne(gPe,7) == 1) ;
    // Test de la fonction creer_profil
    string s_nomPe = "Delmas" ;
    string s_prenomPe = "Albert" ;
    string s_courrielPe = "albert.delmas@gmail.fr" ;
    s_comp0 = "ponctuel" ;
    s_comp1 = "patisserie" ;
    s_comp2 = "cuisine" ;
    char tab_comppE[MAX_COMPETENCES][128] = {'\0'} ;
    int colleguesPe[MAX_AMIS] ;
    for (int i = 0; i < MAX_AMIS; i++) colleguesPe[i] = -1 ;
    for (int i = 0; i < 8; i++) colleguesPe[i] = i+1 ;
    size = s_nomPe.size() + 1 ;
    char c_nomPe[128];
    strncpy(c_nomPe, s_nomPe.c_str(), size) ;
    size = s_prenomPe.size() + 1 ;
    char c_prenomPe[128];
    strncpy(c_prenomPe, s_prenomPe.c_str(), size) ;
    size = s_courrielPe.size() + 1 ;
    char c_courrielPe[128];
    strncpy(c_courrielPe, s_courrielPe.c_str(), size) ;
    size = s_comp0.size() + 1 ;
    strncpy(tab_comppE[0], s_comp0.c_str(), size) ;
    size = s_comp1.size() + 1 ;
    strncpy(tab_comppE[1], s_comp1.c_str(), size) ;
    size = s_comp2.size() + 1 ;
    strncpy(tab_comppE[2], s_comp2.c_str(), size) ;
    creer_profil(c_nomPe,c_prenomPe,c_courrielPe,78969,tab_comppE,colleguesPe,7,gPe) ;
    TEST(g_size(gPe) == 20);
    TEST(LastPersonne(gPe) == 20) ;
    TEST(g_index(gPe,20)->index == 20) ;
    TEST(strcmp(g_index(gPe,20)->nom, "Delmas") == 0) ;
    TEST(strcmp(g_index(gPe,20)->prenom, "Albert") == 0) ;
    TEST(g_index(gPe,20)->adresse == 78969) ;
    TEST(strcmp(g_index(gPe,20)->courriel, "albert.delmas@gmail.fr") == 0) ;
    TEST(strcmp(g_index(gPe,20)->amis[0]->prenom, "Mickey") == 0) ;
    TEST(g_index(gPe,20)->amis[5] != NULL) ;
    TEST(strcmp(g_index(gPe,20)->competence[0], "ponctuel") == 0) ;
    TEST(strcmp(g_index(gPe,20)->competence[1], "patisserie") == 0) ;
    TEST(g_index(gPe,20)->competence[3][0] == '\0') ;
    // Test de la fonction supprimer_profil
    supprimer_profil(20,gPe) ;
    supprimer_profil(13,gPe) ;
    supprimer_profil(4,gPe) ;
    TEST(g_size(gPe) == 17);
    TEST(LastPersonne(gPe) == 19) ;
    // Test de la fonction modifier_adresse
    TEST(modifier_adresse(1,gPe,11111) == 0) ;
    TEST(g_index(gPe,1)->adresse == 11111) ;
    TEST(modifier_adresse(2,gPe,77700) == 1) ;
    TEST(modifier_adresse(19,gPe,12345) == 0) ;
    TEST(g_index(gPe,19)->adresse == 12345) ;
    TEST(modifier_adresse(12,gPe,45825) == 0) ;
    TEST(g_index(gPe,12)->adresse == 45825) ;
    TEST(modifier_adresse(35,gPe,45825) == 2) ;
    // Test de la fonction modifier_mail
    string s_courrielPeme = "adressedetest@test.com" ;
    char c_courrielPeme[128];
    size = s_courrielPeme.size() + 1 ;
    strncpy(c_courrielPeme, s_courrielPeme.c_str(), size) ;
    string s_courrielPem = "minnie@mickeyville.com" ;
    size = s_courrielPem.size() + 1 ;
    char c_courrielPem[128];
    strncpy(c_courrielPem, s_courrielPem.c_str(), size) ;
    TEST(modifier_mail(1,gPe,c_courrielPeme) == 0) ;
    TEST(strcmp(g_index(gPe,1)->courriel, "adressedetest@test.com") == 0) ;
    TEST(modifier_mail(2,gPe,c_courrielPem) == 0) ;
    TEST(modifier_mail(19,gPe,c_courrielPeme) == 0) ;
    TEST(strcmp(g_index(gPe,19)->courriel, "adressedetest@test.com") == 0) ;
    TEST(modifier_mail(12,gPe,c_courrielPeme) == 0) ;
    TEST(strcmp(g_index(gPe,12)->courriel, "adressedetest@test.com") == 0) ;
    TEST(modifier_mail(35,gPe,c_courrielPeme) == 2) ;
    // Test de la fonction modifier_entreprise
    TEST(modifier_entreprise(1,gPe,1) == 0) ;
    TEST(modifier_entreprise(1,gPe,1) == 1) ;
    TEST(modifier_entreprise(5,gPe,7) == 0) ;
    TEST(modifier_entreprise(45,gPe,7) == 2) ;



    




//     // Tests de la fonction modifier entreprise
//     {
//         modifier_entreprise(4, gPe, 3);
//         TEST(g_index(gPe, 4)->entreprise == 3);
//         TEST(modifier_entreprise(4, gPe, 3) == 1);
//     }

//     // Tests de la fonction ajouter compétence
//     {
//         char comp[5] = {'f', 'o', 'r', 't', '\0'};
//         ajouter_competence(4, gPe, comp);
//         TEST(strcmp(g_index(gPe, 4)->competence[1], comp) == 0);
//         TEST(ajouter_competence(4, gPe, comp) == 1);
//     }

//     // Tests de la fonction quitter entreprise
//     {
//         quitter_entreprise(6, gPe);
//         TEST(g_index(gPe, 6)->entreprise == -1);
//         TEST(quitter_entreprise(6, gPe) == 1);
//     }

//     //Tests de la fonction ajouter collègue
//     {
//         TEST(ajouter_collegue(2, gPe, 3) == 1);
//         TEST(ajouter_collegue(4, gPe, 3) == 2);
//         // TEST(ajouter_collegue(9, gPe, 3) == 3);
//         TEST(g_friends(gPe, 2, 3) == true);
//     }

//     // Tests de la fonction supprimer collegue
//     // {
//         // TEST(supprimer_collegue(4, gPe, 7) == 0);
//         TEST(g_friends(gPe, 4, 7) == false);
//         TEST(supprimer_collegue(4, gPe, 7) == 1);
//     // }

// //     //Tests de la fonction rejoindre entreprise
// //     {
//         TEST(rejoindre_entreprise(6, gPe, 3) == 0);
//         TEST(rejoindre_entreprise(7, gPe, 3) == 0);
//         TEST(g_oneway(gPe, 6, 4) == false);
//         TEST(g_oneway(gPe, 6, 7) == false);
//         TEST(g_friends(gPe, 6, 4) == true);
//         TEST(g_friends(gPe, 6, 7) == true);
// //     }

// //     //Tests de la fonction rechercher poste competences
// //     {
//         TEST(recherche_poste_comp(1, gPe, gP, gE) == 1);
//         TEST(recherche_poste_comp(6, gPe, gP, gE) == 0);
//         TEST(recherche_poste_comp(8, gPe, gP, gE) == 1); //Le 8 en trouve plusieurs
// //     }

// //     //Tests de la fonction rechercher poste competences
//     {
//         TEST(recherche_poste_postal(2, gPe, gP, gE) == 1);
//         TEST(recherche_poste_postal(4, gPe, gP, gE) == 0);
//         TEST(recherche_poste_postal(7, gPe, gP, gE) == 1);
//     }

// //     //Tests de la fonction rechercher ancien collègue par entreprise
// //     {
//         TEST(recherche_col_par_entre(2, gPe, 1)==1);
//         TEST(recherche_col_par_entre(8, gPe, 2) == 0);
//         TEST(recherche_col_par_entre(2, gPe, 11)== 0); //Il n'en trouve pas car il n'y a pas d'entreprise 11
// //     }

// //     //Tests de la fonction rechercher ancien collègue par compétence
// //     {
//         char src[6] = {'c','h','a','n','t','\0'};
//         TEST(recherche_col_comp(2, gPe, src)==1);
//         TEST(recherche_col_comp(8, gPe, src) == 0);
//         char src2[7] = {'t','e','n','n','i','s','\0'};
//         TEST(recherche_col_comp(2, gPe, src2)== 0); //Il n'en trouve pas car il n'y a pas de competence tennis
// //     }

// //     //  //Tests de la fonction supprimer employe
// //     // {
//         char competence[5][128] = {'\0'};
//         int col[5] = {-1,-1,-1,-1,-1};
//         for (int i = 0; i < 5 ; i++) col[i] = -1;
//         char Manon[6] = {'M','a','n','o', 'n', '\0'};
//         char nom[5] = {'s', 'c', 't', 't', '\0'};
//         char mail[5] = {'m', 'a', 'i', 'l', '\0'};
//         competence[0][0] = 'd';
//         competence[0][1] = 'y';
//         competence[0][2] = 'n';
//         competence[0][3] = 'a';
//         competence[0][4] = 'm';
//         competence[0][5] = 'i';
//         competence[0][6] = 'q';
//         competence[0][7] = 'u';
//         competence[0][8] = 'e';
//         competence[0][9] = '\0';
//         creer_profil(Manon, nom, mail, 17800, competence, col, 2, gPe);
//         // TEST(g_size(gPe) == 9);
//         // supprimer_profil(9,gPe);
// //     // }
// //     // {
// //     //     supprimer_profil (6, gPe);
// //     //     char comp[5][128] = {'\0'};
// //     //     int col[5];
// //     //     for (int i = 0; i < 5 ; i++) col[i] = -1;
// //     //     char Manon[6] = {'M','a','n','o', 'n', '\0'};
// //     //     char nom[5] = {'s', 'c', 't', 't', '\0'};
// //     //     char mail[5] = {'m', 'a', 'i', 'l', '\0'};
// //     //     creer_profil(Manon, nom, mail, 17800, comp, col, 2, gPe);
// //     // }

    

    // Sort automatiquement TOUS les postes qui demandent une compétence que la personne possède
    // recherche_poste_comp(2,gPe, gP,gE) ;
    // PersonneRecherchePosteParCompetence(g_index(gPe,9), gP, gE) ;

    // Sort automatiquement TOUS les postes qui demandent une compétence que la personne possède
    // Si l'entreprise qui propose ces postes à le même code postal que la personne
    // recherche_poste_postal(2,gPe, gP,gE) ;
    // PersonneRecherchePosteParCompetenceEtCode(g_index(gPe,2), gP, gE) ;

    // La personne entre l'index de l'entreprise, et ça lui sort tous les collègues de son réseau
    // qui travaillent dans cette entreprise
    // recherche_col_par_entre(9,gPe,1) ;
    // PersonneRechercheCollegueParEntreprise(gPe, 9, 1) ;

    // La personne ne rentre rien et ça lui retourne tous les collègues de son réseau qui travaillent dans une entreprise
    // qui propose un poste avec une compétence en commum avec les compétences de la personne qui fait la recherche
    // Exemple : Robert possède la compétence Anglais
    //           Albert (collègue de Robert) travaille chez Netflix qui propose un poste avec de l'anglais
    //           Odette (collègue de Robert) travaille chez Auchan qui ne propose pas de poste avec de l'anglais
    //           La recherche affiche uniquement les coordonnées d'Albert
    // string comp = "anglais" ;
    // size_t size = comp.size() + 1 ;
    // char compcomp[30] ;
    // strncpy(compcomp, comp.c_str(), size) ;
    // recherche_col_comp(2,gPe,compcomp) ;
    // PersonneRechercheCollegueParCompetence(g_index(gPe,2), gE, gP) ;

    // L'entreprise ne rentre rien et ça lui sort tous les chercheurs d'emploi qui ont une compétence qui correspond
    // à l'un des postes proposés par l'entreprise
    // EntrepriseRecherchePersonneParCompetence(gPe,gP,5) ;

    // L'entreprise ne rentre rien et ça lui sort tous les chercheurs d'emploi qui ont une compétence qui correspond
    // à l'un des postes proposés par l'entreprise ssi l'entreprise et le chercheur d'emploi on le même code postal
    // cout << endl << endl ;
    // EntrepriseRecherchePersonneParCompetenceEtCode(gPe,gP,g_indexEntreprise(gE,5)) ;

    // Test suppression collègue
    // supprimer_collegue(9,gPe,3);




    // ReinitialiserCSV() ;
    RestaurerJournal() ;


    printf("%d/%d\n", tests_reussis, tests_executes);

    return tests_executes - tests_reussis;
}


// // entreprises.csv :

// // id,nom,code_postal,mail
// // 1,Disney,77700,walt@disney.com
// // 2,Google,75009,emplois@google.com
// // 3,Amazon,65058,contact@amazon.com
// // 4,Apple,54410,contact@apple.com
// // 5,Doowap,42754,bonnebrioche@doowap.com6,Netflix,45789,netflixandchill@gmail.com

// // postes.csv : 

// // id,titre,entreprise,competences
// // 1,acteur,1,comedie;gag
// // 2,developpeur,2,C;SQL;Python
// // 3,briocheur,5,patisserie
// // 4,mascotte_Mickey,1,danse;

// // employes.csv :
// // id,nom,prenom,mail,code-postal,competences,collegues,entreprise
// // 1,Untel,Michel,m_untel@google.com,13010,C++;Python,,2
// // 2,Mouse,Mickey,mickey@mickeyville.gov,77700,comedie,3;5;6,1
// // 3,Mouse,Minnie,minnie@mickeyville.gov,77700,comedie;chant,2,1
// // 4,Brioche,Theo,theobrioche@doowap.fr,13400,patisserie,5,5
// // 5,Scott,Monon,monon@cristalclear.com,54879,chant;abdotransat,4;2,4
// // 6,Pas,Fred,cestquilui@invisible.com,54710,sieste,5,1
// // 7,Duck,Donald,donal.duck@canardville.gov,77700,comedie;gagPe,2,-1
// // 8,Pignon,Francois,pignouf@gmail.com,75020,C;SQL;Python,,-1
