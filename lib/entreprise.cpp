#include <iostream>
using namespace std ;
#include <iostream>
#include <fstream>
#include <string>

#include "entreprise.h"
#include "groupe.h"
#include "liste.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

groupeEntreprises* g_openEntreprisesCSV(FILE *db)
{
    groupeEntreprises *g = (groupeEntreprises*)malloc(sizeof(groupeEntreprises));
    entreprise data;

    char poubelle[100]; //On tej la première ligne
    fscanf(db, "%s\n", poubelle);
    //Lecture du fichier
    while(fscanf(db, "%d,%128[^,],%128[^,],%128[^\n]\n", &data.index, data.nom, data.code_postal, data.courriel) == 4)
    {
        entreprise *e = (entreprise*)malloc(sizeof(entreprise));
        *e = data;
        l_append(&g->entreprise, l_make_node((entreprise *)e));
    }

    return g;
}

int gEntreprise_size(groupeEntreprises* g)
{
    return l_length(g->entreprise);
}

void AfficherEntreprises(groupeEntreprises* g)
{
    if (g->entreprise == NULL) cout << "groupe vide" << endl ;
    else
    {
        node *tmp = g->entreprise ;
        entreprise *e = (entreprise*)tmp->data ;
        while (e!= NULL && tmp != NULL)
        {
            // cout << e->index << " - " << e->nom << " - " << e->code_postal << " - " << e->courriel << endl ;
            cout << e->index << " - " << e->nom  << endl ;
            tmp = tmp->next ;
            if(tmp != NULL) e = (entreprise*)tmp->data ;
            
        }
    }
}

int AjoutEntreprise(groupeEntreprises *groupeEntr, char nom[40], char code_postal[10], char courriel[128])
{
    
    int index(0) ; // Contiendra l'index de la nouvelle entreprise à ajouter

    index = LastEntreprise(groupeEntr) ; // On récupère l'index de la dernière entreprise du groupe
    entreprise *nouveau = (entreprise*)malloc(sizeof(entreprise)) ;
    nouveau->index = index + 1 ;
    strcpy(nouveau->nom, nom) ;
    strcpy(nouveau->code_postal, code_postal) ;
    strcpy(nouveau->courriel, courriel) ;
    // Ajout de la nouvelle entreprise au groupe
    l_append(&groupeEntr->entreprise, l_make_node((entreprise*)nouveau)) ;
    // Ajout de la nouvelle entreprise dans le fichier CSV
    ofstream fichier("entreprises.csv", ios::app) ;
    fichier << index+1 << "," << nom << "," << code_postal << "," << courriel << endl ;
    fichier.close() ;

    return 0 ;
}

int LastEntreprise(groupeEntreprises* g)
{
    int index(0) ;
    node *tmp = g->entreprise ;
    tmp = l_tail(tmp) ;
    entreprise *e = (entreprise*)tmp->data ;
    index = e->index ;

    return index ;
}

entreprise* g_indexEntreprise(groupeEntreprises* g, int const index)
{
    assert(index <= gEntreprise_size(g)) ;
    assert(index > 0) ;
    if (g->entreprise == NULL) return NULL;
    node *tmp = g->entreprise;
    entreprise *e = (entreprise*)tmp->data;
    while (e->index != index && e != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        e = (entreprise*)tmp->data;
    } 
    if (e->index == index) return e;
    return NULL;
}




// void MenuEntreprise()
// {
//     char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
//     do
//     {
//         system("clear") ;
//         cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
//         cout << "Vous voulez :" << endl ;
//         cout << "1. Créer le profil de votre entreprise" << endl ;            
//         cout << "2. Supprimer le profil de votre entreprise" << endl ;
//         cout << "3. Créer le profil d'un poste à pourvoir" << endl ;                            
//         cout << "4. Supprimer le profil d'un poste maintenant pourvu" << endl ;
//         cout << "5. Faire une recherche parmi les chercheurs d'emploi" << endl << endl ;
//         cout << "m. Retourner au menu principal" << endl ;                       
//         cout << "q. Quitter l'application" << endl << endl ;        
//         cout << "Votre choix : " ;
//         cin >> choix ;
//     } while ((choix > '5' || choix < '1') && choix != 'q' && choix != 'm');