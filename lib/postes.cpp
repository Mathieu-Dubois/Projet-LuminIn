#include <iostream>
#include <fstream>
#include <string>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
using namespace std ;
#include "postes.h"

// But : Création d'un groupe de postes à partir d'un flux donné
groupePostes* g_openPostesCSV(FILE* db)
{
    groupePostes *gP = NULL ;
    gP = (groupePostes*)malloc(sizeof(groupePostes)) ;
    gP->poste = NULL ;
    poste data ;
    char caracterelu ;

    //Initialisation du tableau competence
    for (int i = 0 ; i < MAX_COMPETENCES ; i++)
        for(int j = 0 ; j < 128; j++) data.competence[i][j] = '\0';
        
    
    // On "supprime" la première ligne du fichier car elle ne contient aucune donnée
    char poubelle[100];
    fscanf(db, "%s\n", poubelle);

    /* Puis on lit le fichier jusqu'à la fin en lisant à chaque fois :
     - un numéro correspondant à l'index du poste dans le fichier puis une virgule
     - une chaine de caractères correspondant au titre du poste puis une virgule
     - un numéro correspondant à l'index de l'entreprise qui propose ce poste puis une virgule
     - entre 1 et MAX_COMPETENCES compétences avec un ; entre chaque et un retour à la ligne à la fin

     Pour chaque ligne lue, on ajoute au groupe le poste contenant les informations lues
     Si ces conditions ne sont pas vérifiées, cela signifie que le fichier a été lu en entier
     On retourne alors le groupe créé */
    while(fscanf(db, "%d,%127[^,],%d,\n", &data.index, data.titre, &data.entreprise) == 3)
    {
        poste *p = (poste*)malloc(sizeof(poste));
        *p = data ;

        //Maintenant on gère les compétences
        int i = 0 ;
        fscanf(db, "%127[^;\n]", p->competence[i]) ;
        i++ ;
        caracterelu = fgetc(db) ; // Soit on a lu "\n" soit ";"
        while (caracterelu == ';')
        {
            fscanf(db, "%127[^;\n]", p->competence[i]) ; // On lit la compétence suivante
            i++ ;
            caracterelu = fgetc(db) ;
        }
        
        l_append(&gP->poste, l_make_node((poste *)p)) ; 

    }

    return gP;
}

// But : Afficher tous les postes à pourvoir
void AfficherPostes(groupePostes* gP)
{
    if (gP->poste == NULL) cout << "Aucun poste enregistrée" << endl ;
    else
    {
        node *tmp = gP->poste ;
        poste *p = (poste*)tmp->data ;
        while (p!= NULL && tmp != NULL)
        {
            cout << p->index << " - " << p->titre << " - " << p->entreprise << " - | " ;
            for (int i = 0; i < MAX_COMPETENCES; i++)
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

// But : Afficher le titre d'un poste ainsi que l'adresse mail et le code postal de l'entreprise qui le propose
void AfficherPoste(groupePostes* gP, int indexP, groupeEntreprises *gE)
{
    int trouve = 0, fait = 0;
    if (gP->poste == NULL) cout << "Aucun poste enregistrée" << endl ;
    else
    {
        node *tmp = gP->poste ;
        poste *p;

        node*tempentre = gE->entreprise;
        entreprise*entrami;

        while (tmp != NULL && trouve ==0){
            p = (poste*)tmp->data ;
            if(p->index == indexP){                                      //On a trouvé le poste correspondant
                trouve = 1;
                fait = 0;
                while (gE != NULL && fait == 0){
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

//But : Afficher tous les postes pourvus par une entreprise
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
                        for (int i = 0; i < MAX_COMPETENCES; i++)
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

// But : Ajouter un poste à un groupe de type groupePostes
int AjoutPoste(groupePostes *gP, char titre[128], int indexE, char competence[MAX_COMPETENCES][128])
{
    // On récupère l'index du dernier poste du groupe 
    int indexP(0) ;
    indexP = LastPoste(gP) ;

    // On créé un nouveau poste et on lui attribue tout ses paramètres
    // Remarque : l'index du nouveau poste = index du dernier poste du groupe + 1
    poste *nouveau = (poste*)malloc(sizeof(poste)) ;
    nouveau->index = indexP + 1 ;
    strcpy(nouveau->titre, titre) ;
    nouveau->entreprise = indexE ;
    for (int i = 0; i < MAX_COMPETENCES; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            nouveau->competence[i][j] = competence[i][j] ;
        } 
    }

    journal_CreationPoste(nouveau) ;
    
    // Ajout du nouveau poste au groupe
    l_append(&gP->poste, l_make_node((poste*)nouveau)) ;

    // Ajout du nouveau poste dans le fichier CSV
    ofstream fichier("postes.csv", ios::app) ;
    fichier << indexP+1 << "," << titre << "," << indexE << "," ;
    if(competence[0][0] != '\0') fichier << competence[0] ;
    for (int i = 1; i < MAX_COMPETENCES; i++)
    {
        if(competence[i][0] != '\0') fichier << ";" << competence[i] ;
    }
    fichier << endl ;
    fichier.close() ;

    return 0 ;
}

// But : Déterminer l'index du dernier poste d'un groupe de type groupePostes
int LastPoste(groupePostes* gP)
{
    int index(0) ;
    node *tmp = gP->poste ;
    tmp = l_tail(tmp) ;
    poste *p = (poste*)tmp->data ;
    index = p->index ;

    return index ;
}

// But : Supprimer un poste du groupe passé en paramètres et du fichier postes.csv
groupePostes* SupprimerPoste(groupePostes* gP, int const indexP)
{
    // On va chercher le poste dans le groupe
    assert (gP) ;
    node *tmp = gP->poste ;
    poste *p = (poste*)tmp->data ;
    while (p->index != indexP)
    {
        tmp = tmp->next ;
        p = (poste*)(tmp->data) ;
    }
    
    journal_SuppressionPoste(p) ;
    // On raccroche les noeuds entre eux pour enlever le poste
    if(tmp->previous != NULL) tmp->previous->next = tmp->next ;
    else gP->poste = tmp->next ;
    if(tmp->next != NULL) tmp->next->previous = tmp->previous ;
    
    // On libère la mémoire contenant le poste supprimé
    free(tmp) ;

    // Puis on met à jour postes.csv
    g_ecrirePoste(gP) ;

    return gP ;
}

// But : Mettre à jour le fichier postes.csv à partir du groupe passé en paramètres
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
                for (int i = 1; i < MAX_COMPETENCES; i++)
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

// But : Déterminer si un poste appartient bien à une entreprise
int ExistePosteEntreprise(groupePostes* gP, int const indexP, int const indexE)
{
    // Si le groupe est vide, le poste n'existe pas, on retourne 0
    if (gP->poste == NULL) return 0;

    // Si l'index demandé est supérier à l'index du dernier poste, le poste n'existe, on retourne 0
    if(indexP > LastPoste(gP) || indexP < 0) return 0 ;

    // Sinon on parcourt tout le groupe jusqu'à trouver (ou non) le groupe voulue
    node *tmp = gP->poste;
    poste *p = (poste*)tmp->data;
    while(p->index != indexP && p != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        p = (poste*)tmp->data;
    }
    // Si on l'a trouvé, on vérifie que l'entreprise match et si c'est le cas on retourne 1
    if (p->index == indexP && p->entreprise == indexE ) return 1;

    // On l'a pas trouvé, on retourne 0
    return 0;
}

// But : Supprimer tous les postes associés à la même entreprise
groupePostes* SupprimerEntreprise_postes(groupePostes* gP, int const indexE)
{
    // On récupère l'index du dernier poste
    int indexMax = LastPoste(gP) ;

    // On parcourt tous les index jusqu'à l'index max
    for (int i = 1; i <= indexMax; i++)
    {
        // Si le poste existe et qu'il appartient à l'entreprise, on le supprime
        if (ExistePosteEntreprise(gP, i, indexE))
        {
            gP = SupprimerPoste(gP, i) ;
        }
    }
    
    return gP ;
}