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
    groupeEntreprises *g = NULL ;
    g = (groupeEntreprises*)malloc(sizeof(groupeEntreprises));
    g->entreprise = NULL ;
    entreprise data;

    char poubelle[100]; //On tej la première ligne
    fscanf(db, "%s\n", poubelle);
    //Lecture du fichier
    while(fscanf(db, "%d,%128[^,],%d,%128[^\n]\n", &data.index, data.nom, &data.code_postal, data.courriel) == 4)
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
    if (g->entreprise == NULL) cout << "Aucune entreprise enregistrée" << endl ;
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

int AjoutEntreprise(groupeEntreprises *groupeEntr, char nom[40], int code_postal, char courriel[128])
{
    
    int index(0) ; // Contiendra l'index de la nouvelle entreprise à ajouter

    index = LastEntreprise(groupeEntr) ; // On récupère l'index de la dernière entreprise du groupe
    entreprise *nouveau = (entreprise*)malloc(sizeof(entreprise)) ;
    nouveau->index = index + 1 ;
    strcpy(nouveau->nom, nom) ;
    nouveau->code_postal = code_postal;
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

int ExisteEntreprise(groupeEntreprises*g, int const index)
{
    if (g->entreprise == NULL) return 0;
    if(index > LastEntreprise(g) || index < 0) return 0 ;
    node *tmp = g->entreprise;
    entreprise *e = (entreprise*)tmp->data;
    while(e->index != index && e != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        e = (entreprise*)tmp->data;
    } 
    if (e->index == index) return 1;
    return 0;
}

entreprise* g_indexEntreprise(groupeEntreprises* g, int const index)
{
    assert(index <= LastEntreprise(g)) ;
    assert(index > 0) ;
    if (g->entreprise == NULL) return NULL;
    node *tmp = g->entreprise;
    entreprise *e = (entreprise*)tmp->data;
    while(e->index != index && e != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        e = (entreprise*)tmp->data;
    } 
    if (e->index == index) return e;
    return NULL;
}

groupeEntreprises* SupprimerEntreprise(groupeEntreprises* g, int const index)
{
    // On supprime le noeud dans le groupe
    assert (g) ;
    node *tmp = g->entreprise ;
    entreprise *e = (entreprise*)tmp->data ;
    while (e->index != index)
    {
        tmp = tmp->next ;
        e = (entreprise*)(tmp->data) ;
    }
   
    if(tmp->previous != NULL) tmp->previous->next = tmp->next ;
    else g->entreprise = tmp->next ;
    if(tmp->next != NULL) tmp->next->previous = tmp->previous ;
    
    free(tmp) ;

    // Puis on met à jour entreprises.csv
    g_ecrireEntreprise(g) ;

    return g ;
}

void g_ecrireEntreprise(groupeEntreprises* g)
{
    // On ouvre en écriture le fichier tmp.csv (comme il n'existe pas, il est créé)
    ofstream nouveauCSV("tmp.csv") ;
    if(nouveauCSV)
    {
        // On ouvre en lecture le fichier entreprises.csv
        ifstream ancienCSV("entreprises.csv") ;
        if(ancienCSV)
        {
            // On récupère la première ligne et on l'écrit dans le nouveau fichier
            string ligne ;
            getline(ancienCSV, ligne) ;
            nouveauCSV << ligne << endl ;

            //Maintenant il faut lire le groupe et écrire les informations ligne par ligne
            node *tmp = g->entreprise ;
            entreprise *e = NULL ;
            while (tmp != NULL)
            {
                e = (entreprise*)(tmp->data) ;
                nouveauCSV << e->index << "," << e->nom << "," << e->code_postal << "," << e->courriel << endl ;
                tmp = tmp->next ;
            }
            nouveauCSV.close() ;
            ancienCSV.close() ;

            // Il ne reste plus qu'à supprimer l'ancien entreprises.csv et renommer tmp.csv 
            remove("entreprises.csv") ;
            rename("tmp.csv", "entreprises.csv") ;
        }
        else
        {
            cout << "ERREUR : Impossible d'ouvrir entreprises.csv" << endl ;
        }
    }
    else
    {
        cout << "ERREUR : Impossible d'ouvrir tmp.csv" << endl ;
    }
 
}

