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
    groupePostes *g = (groupePostes*)malloc(sizeof(groupePostes)) ;
    poste data ;
    char caracterelu ;

    //Initialisation du tableau competence
    for (int i = 0 ; i < 5 ; i++){ 
        for(int j = 0 ; j < 128; j++){
            data.competence[i][j] = '\0';
        }
    }

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

void AfficherPostes(groupeEntreprises* gE, groupePostes* gP, int index)
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
