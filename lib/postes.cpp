#include <iostream>
using namespace std ;
#include <iostream>
#include <fstream>
#include <string>

#include "entreprise.h"
#include "groupe.h"
#include "liste.h"
#include "postes.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>


groupePostes* g_openPostesCSV(FILE* db)
{
    groupePostes *g = NULL ;
    g = (groupePostes*)malloc(sizeof(groupePostes)) ;
    g->poste = NULL ;
    poste data ;
    char caracterelu ;

    //Initialisation du tableau competence
    for (int i = 0 ; i < 5 ; i++)
        for(int j = 0 ; j < 128; j++) data.competence[i][j] = '\0';
        
    

    char poubelle[100]; //On tej la première ligne
    fscanf(db, "%s\n", poubelle);
    //Lecture du fichier
    while(fscanf(db, "%d,%127[^,],%d,\n", &data.index, data.titre, &data.entreprise) == 3)
    {
        poste *p = (poste*)malloc(sizeof(poste));
        *p = data ;

        //Maintenant on gère les compétences
        int i = 0 ;
        fscanf(db, "%127[^;\n]", p->competence[i]) ;
        i++ ;
        caracterelu = fgetc(db) ; //Soit on a lu "\n" soit ";"
        while (caracterelu == ';')
        {
            fscanf(db, "%127[^;\n]", p->competence[i]) ; //On lit la compétence suivante
            i++ ;
            caracterelu = fgetc(db) ;
        }
        
        l_append(&g->poste, l_make_node((poste *)p)) ; 

    }

    return g;
}

void AfficherPostes(groupePostes* g)
{
    if (g->poste == NULL) cout << "Aucun poste enregistrée" << endl ;
    else
    {
        node *tmp = g->poste ;
        poste *p = (poste*)tmp->data ;
        while (p!= NULL && tmp != NULL)
        {
            // cout << e->index << " - " << e->nom << " - " << e->code_postal << " - " << e->courriel << endl ;
            cout << p->index << " - " << p->titre << " - " << p->entreprise << " - | " ;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 128; j++) cout << p->competence[i][j] ;
                if(p->competence[i][0] != '\0') cout << " | " ;
            }
            cout << endl ;
            tmp = tmp->next ;
            if(tmp != NULL) p = (poste*)tmp->data ;
            
        }
    }
}

void AfficherPoste(groupePostes* g, int index)
{
    int trouve = 0;
    if (g->poste == NULL) cout << "Aucun poste enregistrée" << endl ;
    else
    {
        node *tmp = g->poste ;
        poste *p;
        while (tmp != NULL && trouve ==0){
            p = (poste*)tmp->data ;
            if(p->index == index){
                trouve = 1;
                cout << p->index << " - " << p->titre << " - " << p->entreprise << " - | " ;
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 128; j++) cout << p->competence[i][j] ;
                    if(p->competence[i][0] != '\0') cout << " | " ;
                }
                cout << endl ;
                
            } else tmp = tmp->next ;
        }
    }
}

void AfficherPostesEntreprise(groupeEntreprises* gE, groupePostes* gP, int index)
{
    if (gE->entreprise == NULL) cout << "Aucune entreprise enregistrée" << endl ;
    else
    {
        if(ExisteEntreprise(gE,index))
        {
            if (gP->poste == NULL) cout << "Aucun poste enregistré" << endl ;
            else
            {
                node *tmp = gP->poste ;
                poste *p = (poste*)tmp->data ;
                int test = 0 ;
                while (p!= NULL && tmp != NULL)
                {
                    if(p->entreprise == index)
                    {
                        cout << p->index << " - " << p->titre << " - | " ;
                        for (int i = 0; i < 5; i++)
                        {
                            for (int j = 0; j < 128; j++) cout << p->competence[i][j] ;
                            if(p->competence[i][0] != '\0') cout << " | " ;
                        }
                        cout << endl ;
                        test = 1 ;
                        
                    } 
                    tmp = tmp->next ;
                    if(tmp != NULL) p = (poste*)tmp->data ;
                }
                if (!test) cout << "Aucun poste enregistré pour le moment." << endl ;
               
                
            }
        }
        else cout << "ERREUR : L'entreprise n'existe pas" << endl ;
    }
    
    
    
}

int AjoutPoste(groupePostes *gP, char titre[128], int index, char competence[5][128])
{
    
    // int index(0) ; // Contiendra l'index de la nouvelle entreprise à ajouter

    // index = LastPoste(groupeEntr) ; // On récupère l'index du dernier poste du groupe
    // entreprise *nouveau = (entreprise*)malloc(sizeof(entreprise)) ;
    // nouveau->index = index + 1 ;
    // strcpy(nouveau->nom, nom) ;
    // strcpy(nouveau->code_postal, code_postal) ;
    // strcpy(nouveau->courriel, courriel) ;
    // // Ajout de la nouvelle entreprise au groupe
    // l_append(&groupeEntr->entreprise, l_make_node((entreprise*)nouveau)) ;
    // // Ajout de la nouvelle entreprise dans le fichier CSV
    // ofstream fichier("entreprises.csv", ios::app) ;
    // fichier << index+1 << "," << nom << "," << code_postal << "," << courriel << endl ;
    // fichier.close() ;

    return 0 ;
}

int LastPoste(groupePostes* gP)
{
    int index(0) ;
    node *tmp = gP->poste ;
    tmp = l_tail(tmp) ;
    poste *p = (poste*)tmp->data ;
    index = p->index ;

    return index ;
}