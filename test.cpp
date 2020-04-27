#include <iostream>
using namespace std ;
#include "lib/bibliotheques.h"

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>

using namespace std ;

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
    ReinitialiserCSV() ;

    //------------------- TESTS GROUPE ------------------

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



    // // Test des fonctiosn g_openEntreprisesCSV et gEntreprise_size.
    {
        TEST(gE != NULL);
        TEST(gEntreprise_size(gE) == 5);
        // AfficherEntreprises(gE) ;
    }

    // // Test des fonctions g_openPostesCSV
    {
        TEST(gP != NULL);
        // AfficherPostes(gP) ;
    }

    // // Test des fonctiosn g_open et g_size.
    {
        TEST(gPe != NULL);
        TEST(g_size(gPe) == 8);
    }

    // // Tests de la fonction g_index.
    {
        TEST(strcmp(g_index(gPe, 1)->nom, "Untel") == 0);
        TEST(strcmp(g_index(gPe, 1)->prenom, "Michel") == 0);
        TEST(strcmp(g_index(gPe, 2)->courriel, "mickey@mickeyville.gov") == 0);
        TEST(g_index(gPe, 6)->amis[0]->index == 5);
    }
    
    // // Tests de la fonction g_friends.
    {
         TEST(g_friends(gPe, 1, 1) == false);
         TEST(g_friends(gPe, 6, 5) == false);
         TEST(g_friends(gPe, 3, 2) == true);
         TEST(g_friends(gPe, 5, 4) == true);
         TEST(g_friends(gPe, 5, 2) == true);
    }
    
    // // Tests de la fonction g_bestie.
    {
        TEST(g_bestie(gPe, 2) == 3);
        TEST(g_bestie(gPe, 3) == 2);
        TEST(g_bestie(gPe, 1) == -1);
    }

    // // Tests de la fonction g_oneway.
    {
        TEST(g_oneway(gPe, 4, 5) == false);
        TEST(g_oneway(gPe, 3, 2) == false);
        TEST(g_oneway(gPe, 2, 3) == false);
        TEST(g_oneway(gPe, 6, 5) == true);
    }
    
    // // Tests de la fonction g_linked.
    {
        TEST(g_linked(gPe, 1, 1) == false);
        TEST(g_linked(gPe, 2, 2) == false);
        TEST(g_linked(gPe, 2, 6) == true);
        TEST(g_linked(gPe, 5, 4) == true);
        TEST(g_linked(gPe, 4, 1) == false);
        TEST(g_linked(gPe, 6, 4) == true);
    }
    
    // // Tests de la fonction g_distance.
    {
         TEST(g_distance(gPe, 1, 1) == 0); 
         TEST(g_distance(gPe, 5, 4) == 1);   
         TEST(g_distance(gPe, 1, 2) == -1);
         TEST(g_distance(gPe, 6, 4) == 2);    
    }
    
    // // Tests de la fonction g_remove.
    {
        // g_remove(gPe, 4);
        // TEST(g_size(gPe) == 7);
        // TEST(g_index(gPe, 4) == NULL);
        // TEST(g_friends(gPe, 5, 4) == false);
        // TEST(g_oneway(gPe, 5, 4) == false);
        // TEST(g_linked(gPe, 6, 4) == false);
    }

    //------------------- TESTS EMPLOYES ------------------

    // Tests de la fonction modifier adresse
    {
        modifier_adresse(4, gPe, 38000);
        TEST(g_index(gPe, 4)->adresse == 38000);
        TEST(modifier_adresse(4, gPe, 38000) == 1);
    }

    // Tests de la fonction modifier entreprise
    {
        modifier_entreprise(4, gPe, 3);
        TEST(g_index(gPe, 4)->entreprise == 3);
        TEST(modifier_entreprise(4, gPe, 3) == 1);
    }

    // Tests de la fonction ajouter compétence
    {
        char comp[5] = {'f', 'o', 'r', 't', '\0'};
        ajouter_competence(4, gPe, comp);
        TEST(strcmp(g_index(gPe, 4)->competence[1], comp) == 0);
        TEST(ajouter_competence(4, gPe, comp) == 1);
    }

    // Tests de la fonction quitter entreprise
    {
        quitter_entreprise(6, gPe);
        TEST(g_index(gPe, 6)->entreprise == -1);
        TEST(quitter_entreprise(6, gPe) == 1);
    }

    //Tests de la fonction ajouter collègue
    {
        TEST(ajouter_collegue(2, gPe, 3) == 1);
        TEST(ajouter_collegue(4, gPe, 3) == 2);
        TEST(ajouter_collegue(9, gPe, 3) == 3);
        TEST(g_friends(gPe, 2, 3) == true);
    }

    // Tests de la fonction supprimer collegue
    // {
    //     TEST(supprimer_collegue(4, gPe, 7) == 0);
    //     TEST(g_friends(gPe, 4, 7) == false);
    //     TEST(supprimer_collegue(4, gPe, 7) == 1);
    // }

    //Tests de la fonction rejoindre entreprise
    {
        TEST(rejoindre_entreprise(6, gPe, 3) == 0);
        TEST(rejoindre_entreprise(7, gPe, 3) == 0);
        TEST(g_oneway(gPe, 6, 4) == false);
        TEST(g_oneway(gPe, 6, 7) == false);
        TEST(g_friends(gPe, 6, 4) == true);
        TEST(g_friends(gPe, 6, 7) == true);
    }

    //Tests de la fonction supprimer employe
    {
        char comp[5][128] = {'\0'};
        int col[5];
        for (int i = 0; i < 5 ; i++) col[i] = -1;
        char Manon[6] = {'M','a','n','o', 'n', '\0'};
        char nom[5] = {'s', 'c', 't', 't', '\0'};
        char mail[5] = {'m', 'a', 'i', 'l', '\0'};
        creer_profil(Manon, nom, mail, 17800, comp, col, 2, gPe);
        TEST(g_size(gPe) == 9);
        supprimer_profil(9,gPe);
    }

    //Tests de la fonction rechercher poste competences
    {
        TEST(recherche_poste_comp(1, gPe, gP, gE) == 1);
        TEST(recherche_poste_comp(6, gPe, gP, gE) == 0);
        TEST(recherche_poste_comp(8, gPe, gP, gE) == 1); //Le 8 en trouve plusieurs
    }

    //Tests de la fonction rechercher poste competences
    {
        TEST(recherche_poste_postal(2, gPe, gP, gE) == 1);
        TEST(recherche_poste_postal(4, gPe, gP, gE) == 0);
        TEST(recherche_poste_postal(7, gPe, gP, gE) == 1);
    }

    //Tests de la fonction rechercher ancien collègue par entreprise
    {
        TEST(recherche_col_par_entre(2, gPe, 1)==1);
        TEST(recherche_col_par_entre(8, gPe, 2) == 0);
        TEST(recherche_col_par_entre(2, gPe, 11)== 0); //Il n'en trouve pas car il n'y a pas d'entreprise 11
    }

    //Tests de la fonction rechercher ancien collègue par compétence
    {
        char src[6] = {'c','h','a','n','t','\0'};
        TEST(recherche_col_comp(2, gPe, src)==1);
        TEST(recherche_col_comp(8, gPe, src) == 0);
        char src2[7] = {'t','e','n','n','i','s','\0'};
        TEST(recherche_col_comp(2, gPe, src2)== 0); //Il n'en trouve pas car il n'y a pas de competence tennis
    }

    //------------------- TESTS ENTREPRISE ------------------

    // // Test de la fonction LastEntreprise et ajout AjoutEntreprise
    {
        TEST(LastEntreprise(gE) == 5) ;
        char nom[40] = "Netflix" ;
        int code = 45789 ;
        char mail[128] = "netflixandchill@gmail.com" ;
        AjoutEntreprise(gE,nom,code,mail) ; // ATTENTION VA MODIFER LE CSV INITIAL
        TEST(LastEntreprise(gE) == 6) ;
    }

    // // Test de la fonction g_indexEntreprise
    {
        TEST(strcmp(g_indexEntreprise(gE, 1)->nom, "Disney") == 0);
        TEST(g_indexEntreprise(gE, 1)->code_postal == 77700) ;
        TEST(strcmp(g_indexEntreprise(gE, 2)->courriel, "emplois@google.com") == 0);
        TEST(strcmp(g_indexEntreprise(gE, 3)->nom, "Amazon") == 0);
    }

    // Test de la fonction g_ecrireEntreprise
    {
        g_ecrireEntreprise(gE) ; 
    }

    // Test de la fonction SupprimerEntreprise
    {
        SupprimerEntreprise(gE,1) ;
        SupprimerEntreprise(gE,2) ;
        SupprimerEntreprise(gE,3) ;
        SupprimerEntreprise(gE,4) ;
        SupprimerEntreprise(gE,5) ;
        SupprimerEntreprise(gE,6) ;
    }

    ReinitialiserCSV() ;
    
    // // Test de la fonction AfficherPostesEntreprise
    // {
    // AfficherPostesEntreprise(gE,gP,1) ;
    // AfficherPostesEntreprise(gE,gP,2) ;
    // AfficherPostesEntreprise(gE,gP,0) ;
    // AfficherPostesEntreprise(gE,gP,3) ;
    // AfficherPostesEntreprise(gE,gP,5) ;
    // }

    // Test de la fonction LastPoste
    {
        TEST(LastPoste(gP) == 4) ;
    }

    // Test de la fonction AjoutPoste
    {
        char titre[128] = "vendeur" ;
        int indexE = 4 ;
        char competence[5][128] = {'\0'};
        competence[0][0] = 'd';
        competence[0][1] = 'y';
        competence[0][2] = 'n';
        competence[0][3] = 'a';
        competence[0][4] = 'm';
        competence[0][5] = 'i';
        competence[0][6] = 'q';
        competence[0][7] = 'u';
        competence[0][8] = 'e';
        competence[0][9] = '\0';
        competence[1][0] = 'h';
        competence[1][1] = 'e';
        competence[1][2] = 'y';
        competence[1][3] = '\0';
        competence[2][0] = 'm';
        competence[2][1] = 'i';
        competence[2][2] = 'q';
        competence[2][3] = 'u';
        competence[2][4] = 'e';
        competence[2][5] = '\0';
        // competence[1] = "souriant" ;
        // competence[2] = "efficace" ;
        AjoutPoste(gP,titre,indexE,competence) ;
    }

    // {
    // char hey[128] = "comedie" ;
    // char hey2[128] = "Python" ;
    // EntrepriseRechercheParCompetence(gPe, hey) ;
    // EntrepriseRechercheParCompetence(gPe, hey2) ;

    // int codeP = 75020 ;
    // EntrepriseRechercheParCompetenceEtCode(gPe,hey2,codeP) ;
    // EntrepriseRechercheParCompetenceEtCode(gPe,hey2,codeP+1) ;
    // }

    ReinitialiserCSV() ;


    printf("%d/%d\n", tests_reussis, tests_executes);

    return tests_executes - tests_reussis;
}


// entreprises.csv :

// id,nom,code_postal,mail
// 1,Disney,77700,walt@disney.com
// 2,Google,75009,emplois@google.com
// 3,Amazon,65058,contact@amazon.com
// 4,Apple,54410,contact@apple.com
// 5,Doowap,42754,bonnebrioche@doowap.com6,Netflix,45789,netflixandchill@gmail.com

// postes.csv : 

// id,titre,entreprise,competences
// 1,acteur,1,comedie;gag
// 2,developpeur,2,C;SQL;Python
// 3,briocheur,5,patisserie
// 4,mascotte_Mickey,1,danse;

// employes.csv :
// id,nom,prenom,mail,code-postal,competences,collegues,entreprise
// 1,Untel,Michel,m_untel@google.com,13010,C++;Python,,2
// 2,Mouse,Mickey,mickey@mickeyville.gov,77700,comedie,3;5;6,1
// 3,Mouse,Minnie,minnie@mickeyville.gov,77700,comedie;chant,2,1
// 4,Brioche,Theo,theobrioche@doowap.fr,13400,patisserie,5,5
// 5,Scott,Monon,monon@cristalclear.com,54879,chant;abdotransat,4;2,4
// 6,Pas,Fred,cestquilui@invisible.com,54710,sieste,5,1
// 7,Duck,Donald,donal.duck@canardville.gov,77700,comedie;gagPe,2,-1
// 8,Pignon,Francois,pignouf@gmail.com,75020,C;SQL;Python,,-1
