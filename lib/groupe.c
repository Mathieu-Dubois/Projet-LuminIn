#include "groupe.h"

#include "liste.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

groupe* g_open(FILE *db)
{
    groupe *g = (groupe*)malloc(sizeof(groupe));
    int amis[20][5];
    int ami, i,j;
    personne data;

    //Initialisation du tableau amis
    for (int i = 0 ; i < 20 ; i++){ 
        for(int j = 0 ; j < 5; j++){
            amis[i][j] = -1;
        }
    }

    //Initialisation du tableau competence
    for (int i = 0 ; i < 5 ; i++){ 
        for(int j = 0 ; j < 128; j++){
            data.competence[i][j] = '\0';
        }
    }
    i = 0;
    char poubelle[100]; //On tej la première ligne
    fscanf(db, "%s\n", poubelle);
    //Lecture du fichier
    while(fscanf(db, "%d,%128[^,],%128[^,],%128[^,],%d", &data.index, data.nom, data.prenom, data.courriel, data.adresse) == 5)
    {
        personne *p = (personne*)malloc(sizeof(personne));
        *p = data;
        for (int i = 0 ; i < 5 ; i++){
            p->amis[i] = NULL;
        }
        //Maintenant on gère competences et entreprise
        int comp = 0;
        fscanf(db, "%c", poubelle);
        while(fscanf(db, "%128[^,;];", p->competence[comp]) == 1) comp++;//Probleme Mickey car n'a qu'une competence
        fscanf(db, "%c", poubelle);//on enleve une virgule
        
        j = 0;
        while(fscanf(db, "%d;", &ami)==1){ 
            amis[i][j] = ami;
            j++;
        }
        fscanf(db, ",%d\n", p->numEntreprise);
        l_append(&g->personnes, l_make_node((personne *)p)); //Ca n'a pas l'air de linker
        i++;
    }

    //Maintenant on link les amis
    node *tmp = g->personnes;
    node *parcours = g->personnes;
    personne* parcourami, *tmpami;
    int compt=0;
    i = 0;
    while(tmp != NULL){
        compt = 0;
        for (int j = 0 ; j < 5 ; j++){
            if (amis[i][j] != -1){
                parcours = g->personnes;
                tmpami = (personne*)(tmp->data);
                parcourami = (personne*)(parcours->data);
                while(parcourami->index != amis[i][j]){
                    parcours = parcours->next;
                    parcourami = (personne*)(parcours->data);
                }
                
                tmpami->amis[compt] = parcourami;
                compt++;
            }
        }
        tmp = tmp->next;
        i++;
    }
    return g;
}

int g_size(groupe* g)
{
     int x=0;
  
    if(g->personnes){
        x=1;
        while(g->personnes->next != NULL){
            g->personnes=g->personnes->next;  
        }

        while(g->personnes->previous != NULL){
            g->personnes=g->personnes->previous;  
            x=x+1;
        }
  
    
    }
    return x;
}

personne* g_index(groupe* g, int const index)
{
    assert(index<21);
    assert(index>=0);
    if (g->personnes == NULL) return NULL;
    node *tmp = g->personnes;
    personne *p = (personne*)tmp->data;
    while (p->index != index && p != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        p = (personne*)tmp->data;
    } 
    if (p->index == index) return p;
    return NULL;
}

bool g_friends(groupe* g, int const index_a, int const index_b)
{
    personne* a = g_index(g,index_a);
    personne* b = g_index(g,index_b);
    if (a == NULL || b == NULL) return false;
    int i;
    bool res1=false,res2=false;
    for(i=0;i<5;i++){
        if(a->amis[i]->nom==b->nom){
                res1=true;
        }
        if(b->amis[i]->nom==a->nom){
                res2=true;
        }
    }
    if((res1 == true) && (res2 == true)) return true;
    return false;
}

int g_bestie(groupe* g, int const index)
{
    personne* origin = g_index(g, index);
    if (origin == NULL || origin->amis[0] == NULL) return -1;
    int b = origin->amis[0]->index;
    personne* dest = g_index(g, b);
    if (dest == NULL || origin->amis[0] == NULL) return -1;
    if (dest->amis[0]->index == index) return b;
    else return -1;
}

bool g_oneway(groupe* g, int const index_a, int const index_b)
{
    personne* a = g_index(g,index_a);
    personne* b = g_index(g,index_b);
    if (a == NULL || b == NULL) return false;
    int i;
    bool res1=false,res2=false;
    for(i=0;i<5;i++){
        if(a->amis[i]->nom==b->nom){
                res1=true;
        }
        if(b->amis[i]->nom==a->nom){
                res2=true;
        }
    }
    if((res1 == true) && (res2 == false)) return true;
    if((res1 == false) && (res2 == true)) return true;
    return false;
}

bool g_linked(groupe* g, int const index_a, int const index_b)
{
    int sec[20]; //tableau d'attente
    int wet[20];
    for (int i = 0 ; i<20 ; i++){
        sec[i] = 0;
        wet[i] = 0;
    }
    int i;
    if (index_a == index_b) return false;
    personne* origin;
    int code = 0;
    origin = g_index(g, index_a);
    while (code == 0){
        if (origin==NULL) return false;
        wet[origin->index-1] = 1;
        sec[origin->index-1] = 0;
        int compt=0;
        personne*parcourami = (personne*)(origin->amis[compt]);
        while(parcourami != NULL){
            if (wet[parcourami->index-1] != 1) {
                if (parcourami->index == index_b) return true;
                else sec[parcourami->index-1] = 1;
            }
            compt++;
            parcourami = (personne*)(origin->amis[compt]);
        }
        i = 0;
        while (sec[i] == 0 && i < 20) i++;
        if (i >= 20) return false;
        else origin = g_index(g, i+1);
    }
    return false;
}

int g_distance(groupe* g, int const index_a, int const index_b)
{
    int n=1;
   
     if (index_a==index_b) return 0;
     if(g_linked(g,index_a,index_b)){
        personne* a = g_index(g,index_a);
        personne* b = g_index(g,index_b);
        personne* tmp = g_index(g,index_a); 
        personne* aprev = g_index(g,index_b); 
        int i,l,k;
         
        while(1){
            int p=0;  
            for(l=0;l<5;l++){
                
                if(aprev==a){
                   if(tmp->amis[0]) tmp=tmp->amis[0];
                    p=p+1;
                    l=0;
                }
                a=tmp;
                n=p+2;
                if(tmp->amis[l]){
                if(a->amis[l]->nom==b->nom) return 1;
                a=tmp->amis[l];
                k=0;
                while(k<5){
                    i=0;
                    for(i=0;i<5;i++){
                        if(a->amis[i]){
                        if(a->amis[i]->nom==b->nom){
                            return n;
                        }
                        }
                     }
                    if(tmp->amis[l]->amis[k]) a=tmp->amis[l]->amis[k];
                    k++;
                    if(k==1) n++;
                }
             }
            aprev=a;
            if(tmp->amis[l+1]) a=tmp->amis[l+1];
           }
        }
     }
     else return -1;
}

void g_remove(groupe* g, int const index)
{
    assert(g);

    //Suppression des relations A METTRE AVANT SUPPRESSION
    node *tmp=g->personnes;
    personne* ami = (personne*)(tmp->data);
    personne* tmpami;
    int compt = 0;
    int flag=0;
    tmpami = ami->amis[compt];
    while (tmp != NULL){
        compt = 0;
        tmpami = ami->amis[compt];
        while (tmpami != NULL){
            if (tmpami->index == index){
                flag = 1; //On supprime des relation d'ami
                ami->amis[compt] = NULL;
            } 
            if (tmpami->index != index && flag == 1){ //On écrase
                ami->amis[compt-1] = tmpami;
                tmpami = NULL;
            } 
            compt++;
            tmpami = ami->amis[compt];
        }
        flag = 0;
        tmp = tmp -> next;
        if (tmp != NULL) ami = (personne*)(tmp->data);
    }
    
    //Suppression dans le groupe
    tmp=g->personnes;
    ami = (personne*)(tmp->data);
    while(ami->index != index){
        tmp = tmp -> next;
        ami = (personne*)(tmp->data);
    }
    tmp -> previous ->next = tmp->next;
    tmp -> next -> previous = tmp -> previous;
    free(tmp);

    


    return;
}
