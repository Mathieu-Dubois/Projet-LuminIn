#include <iostream>
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
    // Lecture de la DB vers une liste en mémoire.
    groupe *g;
    {
        FILE *db = fopen("employes.csv", "r");
        g = g_open(db);
        fclose(db);
    }

    // Tests des fonctiosn g_open et g_size.
    {
        TEST(g != NULL);
        TEST(g_size(g) == 6);
    }

    // Tests de la fonction g_index.
    {
        TEST(strcmp(g_index(g, 1)->nom, "Untel") == 0);
        TEST(strcmp(g_index(g, 1)->prenom, "Michel") == 0);
        TEST(strcmp(g_index(g, 2)->courriel, "mickey@mickeyville.gov") == 0);
        TEST(g_index(g, 6)->amis[0]->index == 5);
    }
    
    // Tests de la fonction g_friends.
    {
         TEST(g_friends(g, 1, 1) == false);
         TEST(g_friends(g, 6, 5) == false);
         TEST(g_friends(g, 3, 2) == true);
         TEST(g_friends(g, 5, 4) == true);
         TEST(g_friends(g, 5, 2) == true);
    }
    
    // Tests de la fonction g_bestie.
    {
        TEST(g_bestie(g, 2) == 3);
        TEST(g_bestie(g, 3) == 2);
        TEST(g_bestie(g, 1) == -1);
    }

    // Tests de la fonction g_oneway.
    {
        TEST(g_oneway(g, 4, 5) == false);
        TEST(g_oneway(g, 3, 2) == false);
        TEST(g_oneway(g, 2, 3) == false);
        TEST(g_oneway(g, 6, 5) == true);
    }
    
    // Tests de la fonction g_linked.
    {
        TEST(g_linked(g, 1, 1) == false);
        TEST(g_linked(g, 2, 2) == false);
        TEST(g_linked(g, 2, 6) == true);
        TEST(g_linked(g, 5, 4) == true);
        TEST(g_linked(g, 4, 1) == false);
        TEST(g_linked(g, 6, 4) == true);
    }
    
    // Tests de la fonction g_distance.
    {
         TEST(g_distance(g, 1, 1) == 0); 
         TEST(g_distance(g, 5, 4) == 1);   
         TEST(g_distance(g, 1, 2) == -1);
         TEST(g_distance(g, 6, 4) == 2);    
    }
    
    // Tests de la fonction g_remove.
    {
        g_remove(g, 4);
        TEST(g_size(g) == 5);
        TEST(g_index(g, 4) == NULL);
        TEST(g_friends(g, 5, 4) == false);
        TEST(g_oneway(g, 5, 4) == false);
        TEST(g_linked(g, 6, 4) == false);
    }

    
    // Lecture de la DB vers une liste en mémoire.
    groupeEntreprises *gE ;
    {
        FILE *dbE = fopen("entreprises.csv", "r");
        gE = g_openEntreprisesCSV(dbE);
        fclose(dbE);
    }

    // Test des fonctiosn g_openEntreprisesCSV et gEntreprise_size.
    {
        TEST(gE != NULL);
        TEST(gEntreprise_size(gE) == 5);
    }
    
    // Test de la fonction LastEntreprise et ajout AjoutEntreprise
    {
        TEST(LastEntreprise(gE) == 5) ;
        char nom[40] = "Netflix" ;
        char code[10] = "45789" ;
        char mail[128] = "netflixandchill@gmail.com" ;
        AjoutEntreprise(gE,nom,code,mail) ;
        TEST(LastEntreprise(gE) == 6) ;
    }

    // Test de la fonction g_indexEntreprise
    {
        TEST(strcmp(g_indexEntreprise(gE, 1)->nom, "Disney") == 0);
        TEST(strcmp(g_indexEntreprise(gE, 1)->code_postal, "77700") == 0);
        TEST(strcmp(g_indexEntreprise(gE, 2)->courriel, "emplois@google.com") == 0);
        TEST(strcmp(g_indexEntreprise(gE, 3)->nom, "Amazon") == 0);
    }

    // Test de la fonction g_ecrireEntreprise
    {
        g_ecrireEntreprise(gE) ;
    }



    printf("%d/%d\n", tests_reussis, tests_executes);

    return tests_executes - tests_reussis;

    cout << "Tous les tests passent" << endl ;

    return 0 ;
}
