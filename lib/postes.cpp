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

void AfficherPoste(groupePostes* g, int index, groupeEntreprises *gEntre)
{
    int trouve = 0, fait = 0;
    if (g->poste == NULL) cout << "Aucun poste enregistrée" << endl ;
    else
    {
        node *tmp = g->poste ;
        poste *p;

        node*tempentre = gEntre->entreprise;
        entreprise*entrami;

        while (tmp != NULL && trouve ==0){
            p = (poste*)tmp->data ;
            if(p->index == index){                                      //On a trouvé le poste correspondant
                trouve = 1;
                fait = 0;
                while (gEntre != NULL && fait == 0){
                    entrami = (entreprise*)(tempentre->data);
                    if (p->entreprise == entrami->index){               //On a trouvé l'entreprise correspondant au poste
                        cout << p->titre << " - " << entrami->nom << " - " << entrami->courriel << " - " << entrami->code_postal << endl;
                        fait = 1;
                    }
                    tempentre = tempentre -> next;
                }               
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

int AjoutPoste(groupePostes *gP, char titre[128], int indexE, char competence[5][128])
{
    
    int indexP(0) ; // Contiendra l'index du nouveau poste à ajouter

    indexP = LastPoste(gP) ; // On récupère l'index du dernier poste du 
    poste *nouveau = (poste*)malloc(sizeof(poste)) ;
    nouveau->index = indexP + 1 ;
    strcpy(nouveau->titre, titre) ;
    nouveau->entreprise = indexE ;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            nouveau->competence[i][j] = competence[i][j] ;
        } 
    }
    // Ajout du nouveau poste au groupe
    l_append(&gP->poste, l_make_node((poste*)nouveau)) ;
    // Ajout du nouveau poste dans le fichier CSV
    ofstream fichier("postes.csv", ios::app) ;
    fichier << indexP+1 << "," << titre << "," << indexE << "," ;
    if(competence[0][0] != '\0') fichier << competence[0] ;
    for (int i = 1; i < 5; i++)
    {
        if(competence[i][0] != '\0') fichier << ";" << competence[i] ;
    }
    fichier << endl ;
    fichier.close() ;

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

groupePostes* SupprimerPoste(groupePostes* gP, int const index)
{
    // On supprime le noeud dans le groupe
    assert (gP) ;
    node *tmp = gP->poste ;
    poste *p = (poste*)tmp->data ;
    while (p->index != index)
    {
        tmp = tmp->next ;
        p = (poste*)(tmp->data) ;
    }
   
    if(tmp->previous != NULL) tmp->previous->next = tmp->next ;
    else gP->poste = tmp->next ;
    if(tmp->next != NULL) tmp->next->previous = tmp->previous ;
    
    free(tmp) ;

    // Puis on met à jour poste.csv
    g_ecrirePoste(gP) ;

    return gP ;
}

void g_ecrirePoste(groupePostes* gP)
{
    // On ouvre en écriture le fichier tmp.csv (comme il n'existe pas, il est créé)
    ofstream nouveauCSV("tmp.csv") ;
    if(nouveauCSV)
    {
        // On ouvre en lecture le fichier postes.csv
        ifstream ancienCSV("postes.csv") ;
        if(ancienCSV)
        {
            // On récupère la première ligne et on l'écrit dans le nouveau fichier
            string ligne ;
            getline(ancienCSV, ligne) ;
            nouveauCSV << ligne << endl ;

            //Maintenant il faut lire le groupe et écrire les informations ligne par ligne
            node *tmp = gP->poste ;
            poste *p = NULL ;
            while (tmp != NULL)
            {
                p = (poste*)(tmp->data) ;
                nouveauCSV << p->index << "," << p->titre << "," << p->entreprise << "," ;
                if(p->competence[0][0] != '\0') nouveauCSV << p->competence[0] ;
                for (int i = 1; i < 5; i++)
                {
                    if(p->competence[i][0] != '\0') nouveauCSV << ";" << p->competence[i] ;
                }
                nouveauCSV << endl ;
                tmp = tmp->next ;
            }
            nouveauCSV.close() ;
            ancienCSV.close() ;

            // Il ne reste plus qu'à supprimer l'ancien poste.csv et renommer tmp.csv 
            remove("postes.csv") ;
            rename("tmp.csv", "postes.csv") ;
        }
        else
        {
            cout << "ERREUR : Impossible d'ouvrir postes.csv" << endl ;
        }
    }
    else
    {
        cout << "ERREUR : Impossible d'ouvrir tmp.csv" << endl ;
    }
 
}

int ExistePosteEntreprise(groupePostes* gP, int const indexP, int const indexE)
{
    if (gP->poste == NULL) return 0;
    if(indexP > LastPoste(gP) || indexP < 0) return 0 ;
    node *tmp = gP->poste;
    poste *p = (poste*)tmp->data;
    while(p->index != indexP && p != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        p = (poste*)tmp->data;
    } 
    if (p->index == indexP && p->entreprise == indexE ) return 1;
    return 0;
}

groupePostes* SupprimerEntreprise_postes(groupePostes* gP, int const indexE)
{
    int indexMax = LastPoste(gP) ;

    for (int i = 1; i <= indexMax; i++)
    {
        if (ExistePosteEntreprise(gP, i, indexE))
        {
            gP = SupprimerPoste(gP, i) ;
        }
    }
    
    return gP ;
}