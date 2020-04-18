#include "groupe.h"

#include "employe.h"
#include "groupe.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

void creer_profil(char *nom, char *prenom, char *courriel, int adresse, char competence[5][128], int collegue[5], int entreprise, groupe *gEmployes)
{
    FILE *employes; int i, j, index; char poub[128];

    //On ajoute d'abord dans la table csv
    //Il faut récupérer en premier lieu l'indice
    employes = fopen("employes.csv", "r");
    fscanf(employes, "%s\n", poub);
    i = 0;
    do {
        i++;
        fscanf(employes, "%d,", &j);
        fscanf(employes, "%s\n", poub);
    } while (i == j && !feof(employes));
    if (i != j){
        index = i;
    } 
    else index = i+1;
    fclose(employes);
    employes = fopen("employes.csv", "a");
    fprintf(employes, "\n%d,", index);
    fputs(nom, employes);
    fputc(',', employes);
    fputs(prenom, employes);
    fputc(',', employes);
    fputs(courriel, employes);
    fputc(',', employes);
    fprintf(employes, "%d,", adresse);
    //On écrit les compétences
    i = 0;
    while(competence[i][0] != '\0' && i < 5){
        j = 0;
        while(competence[i][j] != '\0') {
            fputc(competence[i][j], employes);
            j++;
        }
        i++;
        if (competence[i][0] != '\0') fputc(';', employes);
        else fputc(',', employes);
    }
    if (i == 0) fputc(',', employes); //Il n'y a pas de competences
    //On écrit les collègues
    i = 0;
    while(collegue[i] != -1){
        fputc(collegue[i], employes);
        i++;
        if (collegue[i] != -1) fputc(';', employes);
        else fputc(',', employes);
    }
    if (i == 0) fputc(',', employes); //Il n'y a pas de collègues
    fprintf(employes, "%d", entreprise);
    fclose(employes);

    //Ensuite on met à jour le groupe d'employés
    personne *p = (personne*)malloc(sizeof(personne));
    p->index = index;
    strcpy(p->nom, nom);
    strcpy(p->prenom, prenom);
    strcpy(p->courriel, courriel);
    p->adresse = adresse;
    p->entreprise = entreprise;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 128; j++){
            p->competence[i][j] = competence[i][j];
        }
    }
    l_append(&gEmployes->personnes, l_make_node((personne *)p));
    //Maintenant on link les amis
    node *parcours;
    personne* parcourami, *tmpami;
    int compt=0;
    for (int j = 0 ; j < 5 ; j++){
        if (collegue[j] != -1){
            parcours = gEmployes->personnes;
            tmpami = (personne*)p;
            parcourami = (personne*)(parcours->data);
            while(parcourami->index != collegue[j]){
                parcours = parcours->next;
                parcourami = (personne*)(parcours->data);
            }
            
            tmpami->amis[compt] = parcourami;
            compt++;
        }
    }
    return;
}

void supprimer_profil (int index, groupe *gEmployes){
    //On supprime du groupe
    g_remove(gEmployes, index);
    //On supprime la ligne du fichier
    //FILE *tmp = fopen("tmp.txt", "rw");
    //FILE *employes = fopen("employes.csv", "r");
    /*char poub[128];
    do {
        fscanf(employes, "%s\n", poub);
        fputs(poub, tmp);
        fputc('\n', tmp);
    } while (!feof(employes));
    fclose(employes);
    fclose(tmp);
    tmp = fopen("tmp.txt", "r");
    employes = fopen("final.txt", "w+");
    //Pour la première ligne
    fscanf(tmp, "%s\n", poub);
    fputs(poub, employes);
    fputc('\n', employes);
    int i = 1, ind, virgule; personne data;
    do {
        fscanf(tmp, "%d,", &ind);           //On récupère l'indice pour voir si c'est la ligne à enlever
        if (ind != index){                  //Si != ligne à enlever alors on lit puis écrit en supprimant les relations
            fprintf(employes, "%d,", ind);
            fscanf(tmp, "%128[^,],%128[^,],%128[^,],%d,",data.nom, data.prenom, data.courriel, &data.adresse);
            //IL MANQUE LES COMPETENCES
            fputs(data.nom, employes);
            fputc(',', employes);
            fputs(data.prenom, employes);
            fputc(',', employes);
            fputs(data.courriel, employes);
            fputc(',', employes);
            fprintf(employes, "%d,", data.adresse);
            //Pour les compétences
            int comp = 0;
            virgule = 0;
            while(fscanf(tmp, "%128[^,;];", data.competence[comp]) == 1){
                if (virgule == 1) fputc(';', employes);
                fputs(data.competence[comp], employes);
                virgule = 1;
                comp++;
            } 
            fscanf(tmp, "%c", poub);//on enleve une virgule
            fputc(',', employes);
            //Pour les amis
            virgule = 0; int ami = 0;
            while(fscanf(tmp, "%d;", &ami)==1){                                        //Pour supprimer les relations
                if (virgule == 0 &&ami != index){                                     //Si c'est le premier ami, pas de ;
                    fprintf(employes, "%d", ami);
                    virgule = 1;
                } 
                else if (ami != index && virgule == 1 ) fprintf(employes, ";%d", ami);    //Si ce n'est pas le premier ami, on met 
            }
            fscanf(tmp, "%s\n", poub);
            fputs(poub, employes);
            fputc('\n', employes);
        } else {
            fscanf(tmp, "%s\n", poub);
        }
        
        i++;
    } while (!feof(tmp));
    fclose(tmp);
    fclose(employes);
    //remove("tmp.txt");*/
    g_ecrire(gEmployes);
}

/*  Entrée :        indice : indice de la personne qui change de code-postal
                    nouv_adresse : changement de code-postal
                    
    Code retour:    0 Si tout se passe bien
                    1 si l'adresse est identique
                    2 si on ne trouve pas l'indice dans le groupe               */
int modifier_adresse(int indice, groupe *gEmployes, int nouv_adresse)
{
    node *temp = gEmployes->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
            if (tmpami->adresse == nouv_adresse) code_retour = 1;   //Si l'adresse est identique
            else {
                tmpami->adresse = nouv_adresse;                     //Si tout se passe bien
                g_ecrire(gEmployes);
                code_retour = 0;
            }
            trouve = 1;
        }
        else if (trouve == 0){
            temp = temp->next;
        }
    }
    if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondant
    g_ecrire(gEmployes);
    return code_retour;
}

/*  Entrée :        indice : indice de la personne qui change d'entreprise
                    nouv_entre: changement d'entreprise
                    
    Code retour:    0 Si tout se passe bien
                    1 si l'entreprise est identique
                    2 si on ne trouve pas l'indice dans le groupe               */
int modifier_entreprise(int indice, groupe *gEmployes, int nouv_entre)
{
    node *temp = gEmployes->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                                //Quand on atteint la personne souhaitée
            if (tmpami->entreprise == nouv_entre) code_retour = 1;   //Si l'entreprise est identique
            else {
                tmpami->entreprise = nouv_entre;                     //Si tout se passe bien
                g_ecrire(gEmployes);
                code_retour = 0;
            }
            trouve = 1;
        }
        else if (trouve == 0){
            temp = temp->next;
        }
    }
    if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondant
    g_ecrire(gEmployes);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui change d'entreprise
                    comp[128]: competence à ajouter
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne a déjà cette compétence
                    2 si la personne a déjà la nombre maximum de compétences
                    3 si on ne trouve pas l'indice dans le groupe               */
int ajouter_competence(int indice, groupe *gEmployes, char comp[128])
{
    node *temp = gEmployes->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1, i, fait = 0;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
            i = 0;
            trouve = 1;                          
            while(i<5 && fait == 0){
                if (tmpami->competence[i][0] == '\0'){              //Si il reste de la place on ajoute la compétence
                    strcpy(tmpami->competence[i], comp);
                    g_ecrire(gEmployes);
                    code_retour = 0;
                    fait = 1;
                } else if (!strcmp(tmpami->competence[i], comp)) {     //Si la personne a déjà cette compétence
                    code_retour = 1 ;
                    fait = 1; 
                }

                i++;
            }  

            if (fait == 0) code_retour = 2;                         //Si la personne a déjà le maximum de compétences                       
        } else {
            temp = temp -> next;
        }
    }
    if (trouve == 0) code_retour = 3;                               //Si on ne trouve pas l'index correspondant
    g_ecrire(gEmployes);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui quitte son entreprise
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne n'a pas d'entreprise
                    2 si on ne trouve pas l'indice dans le groupe               */
int quitter_entreprise(int indice, groupe *gEmployes)
{
    node *temp = gEmployes->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                       //Quand on atteint la personne souhaitée
            trouve = 1;
            if(tmpami->entreprise != -1){
                tmpami->entreprise = -1;
                code_retour = 0;
            }
            else code_retour = 1;                           //Si la personne n'a pas d'entreprise                     
        } else {
            temp = temp -> next;
        }
    }
    if (trouve == 0) code_retour = 2;                       //Si on ne trouve pas l'index correspondant
    g_ecrire(gEmployes);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui veut ajouter un collègue
                    col : indice du collègue que la personne veut ajouter
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne a déjà cette personne en ami
                    2 si la personne n'est pas dans la même entreprise
                    3 si on ne trouve pas l'indice dans le groupe  
                    4 si la personne a deja trop d'amis                          */
int ajouter_collegue(int indice, groupe *gEmployes, int col)
{
    node *temp = gEmployes->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1, i, fait = 0, place = 0;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                                   //Quand on atteint la personne souhaitée
            i = 0;
            trouve = 1;                          
            while(i< MAX_AMIS && fait == 0){
                if (tmpami->amis[i]== NULL) place = 1;
                else if (tmpami->amis[i]->index == col){                //si la personne a déjà cette personne en ami
                    code_retour = 1;
                    fait = 1;
                }
                i++;
            }
            if (code_retour != 1 && place != 1) code_retour =  4;        //si la personne a deja trop d'amis 
            else if (code_retour == -1){                                 //La personne ne fait pas partie de ses amis et il y a de la place
                node *parcours = gEmployes->personnes;
                personne*parcourami;
                i = 0;
                fait = 0;                    
                while(i< MAX_AMIS && fait == 0){
                    if (tmpami->amis[i]== NULL){                        //Endroit ou on va ajouter le collègue
                        while (parcours != NULL && fait == 0){
                            parcourami = (personne*)(parcours->data);
                            if (parcourami->index == col){
                                if(parcourami->entreprise == tmpami -> entreprise){
                                    tmpami->amis[i] = parcourami;
                                    code_retour = 0;
                                } else code_retour= 2;
                                fait = 1;
                            } else parcours = parcours->next;
                        }

                    }
                    i++;
                }
            }               
        } else temp = temp -> next;
    }
    if (trouve == 0) code_retour = 3;                               //Si on ne trouve pas l'index correspondant
    g_ecrire(gEmployes);
    return code_retour;
}

/*  Entrée :        indice : indice de la personne qui rejoint une entreprise
                    entre : indice de l'entreprise que la personne rejoint
                    
    Code retour:    0 Si tout se passe bien
                    1 si on ne trouve pas l'indice de la personne dans le groupe
                    2 si on a pas assez de place pour ajouter tous les collegues          */
int rejoindre_entreprise(int indice, groupe *gEmployes, int entre)
{
    node *temp = gEmployes->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){           //Quand on atteint la personne souhaitée
            trouve = 1;
            tmpami->entreprise = entre;
            code_retour = 0;                     
        } else {
            temp = temp -> next;
        }
    }
    if (trouve == 0) code_retour = 1;           //Si on ne trouve pas l'index correspondant

    //On ajoute maintenant ses collègues
    else{
        node *parcours = gEmployes->personnes;
        personne*parcourami;
        while(parcours != NULL){
            parcourami = (personne*)(parcours->data);
            if (parcourami->entreprise == tmpami->entreprise){                  //Quand on rencontre un potentiel collègue
                code_retour = ajouter_collegue(indice, gEmployes, parcourami->index);
                ajouter_collegue(parcourami->index, gEmployes, indice);                 //On ajoute aussi la personne en collègue aux employes
                if(code_retour == 4) code_retour = 2;
                else code_retour = 0;                 
            }
            parcours = parcours -> next;
        }
    }
    g_ecrire(gEmployes);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui veut supprimer un collègue
                    col : indice du collègue que la personne veut supprimer
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne n'a pas cette personne en ami
                    2 si on ne trouve pas l'indice dans le groupe                         */
int supprimer_collegue(int indice, groupe *gEmployes, int col)
{
    node *temp = gEmployes->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1, i, fait = 0;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                                   //Quand on atteint la personne souhaitée
            i = 0;
            trouve = 1;                          
            while(i< MAX_AMIS && fait == 0){
                if(tmpami->amis[i] != NULL){
                    if (tmpami->amis[i]->index == col){                //si la personne a cette personne en ami
                        tmpami->amis[i] = NULL;
                        code_retour = 0;
                        fait = 1;
                    }
                }
                i++;
            }
            if (fait == 0) code_retour = 1;                             //si la personne n'a pas cette personne en ami
                 
        } else temp = temp -> next;
    }
    if (trouve == 0) code_retour = 2;                                   //Si on ne trouve pas l'index correspondant
    g_ecrire(gEmployes);
    return code_retour;
}