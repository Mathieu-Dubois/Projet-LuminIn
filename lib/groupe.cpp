#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <fstream>
#include <string>
using namespace std ;
#include "groupe.h"

groupePersonnes* g_open(FILE *db)
{
    groupePersonnes *gPe = (groupePersonnes*)malloc(sizeof(groupePersonnes));
    gPe->personnes = NULL ;
    int amis[TAILLE_GPE_MAX][MAX_AMIS];
    int ami, i,j;
    personne data;

    //Initialisation du tableau amis
    for (int i = 0 ; i < TAILLE_GPE_MAX ; i++){ 
        for(int j = 0 ; j < MAX_AMIS; j++){
            amis[i][j] = -1;
        }
    }

    //Initialisation du tableau competence
    for (int i = 0 ; i < MAX_COMPETENCES ; i++){ 
        for(int j = 0 ; j < 128; j++){
            data.competence[i][j] = '\0';
        }
    }
    i = 0;
    char poubelle[100]; //On tej la première ligne
    fscanf(db, "%s\n", poubelle);
    //Lecture du fichier
    while(fscanf(db, "%d,%128[^,],%128[^,],%128[^,],%d", &data.index, data.nom, data.prenom, data.courriel, &data.adresse) == 5)
    {
        personne *p = (personne*)malloc(sizeof(personne));
        *p = data;
        for (int i = 0 ; i < MAX_AMIS ; i++){
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
        fscanf(db, ",%d\n", &p->entreprise);
        l_append(&gPe->personnes, l_make_node((personne *)p)); //Ca n'a pas l'air de linker
        i++;
    }

    //Maintenant on link les amis
    node *tmp = gPe->personnes;
    node *parcours = gPe->personnes;
    personne* parcourami, *tmpami;
    int compt=0;
    i = 0;
    while(tmp != NULL){
        compt = 0;
        for (int j = 0 ; j < MAX_AMIS ; j++){
            if (amis[i][j] != -1){
                parcours = gPe->personnes;
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
    return gPe;
}

void g_ecrire(groupePersonnes* gPe)
{
    char tampon[100]; 
    FILE *db = fopen("employes.csv", "r");
    fscanf(db, "%s\n", tampon);
    fclose(db);
    FILE *tmp = fopen("employes.csv", "w");
    fputs(tampon, tmp);
    fputc('\n', tmp);
    node *temp = gPe->personnes;
    personne*tmpami;
    node*rappel = gPe->personnes;
    int i = 1, consecutif = 0;

    while(temp != NULL){
        tmpami = (personne*)(temp->data);
        //Exception si numéros pas consécutifs
        if(tmpami->index != i){
            consecutif = 0;
            while(temp != NULL && tmpami->index != i){
                temp = temp->next;
                if (temp != NULL) tmpami = (personne*)(temp->data);
            }
            if (temp != NULL) consecutif = 1;
            else {
                temp = rappel;
                tmpami = (personne*)(temp->data);
            }
        }
        fprintf(tmp, "%d,", tmpami->index);
        fputs(tmpami->nom, tmp);
        fputc(',', tmp);
        fputs(tmpami->prenom, tmp);
        fputc(',', tmp);
        fputs(tmpami->courriel, tmp);
        fputc(',', tmp);
        fprintf(tmp, "%d,", tmpami->adresse);
        int virgule = 0;
        for (int x = 0; x < MAX_COMPETENCES ; x++){
            if (tmpami->competence[x][0] != '\0' && virgule == 0) {
                fputs(tmpami->competence[x], tmp);
                virgule = 1;
            }
            else if (tmpami->competence[x][0] != '\0' && virgule == 1) {
                fputc(';', tmp);
                fputs(tmpami->competence[x], tmp);
            }
        }
        fputc(',', tmp);
        virgule = 0;
        for (int j = 0 ; j < MAX_AMIS ; j++){
            if (tmpami->amis[j] != NULL){
                    if (virgule == 0 ){
                         fprintf(tmp, "%d", tmpami->amis[j]->index);
                         virgule = 1;
                    }
                    else if (virgule == 1) fprintf(tmp, ";%d", tmpami->amis[j]->index);
                
            }
        }
        fprintf(tmp, ",%d", tmpami->entreprise);
        fputc('\n', tmp);
        if (consecutif == 1) temp = rappel;
        else {
            temp = temp->next;
            rappel = rappel->next;
        }
        i++;
    }
    fclose(tmp);
    remove("tmp.txt");
}

int g_size(groupePersonnes* g)
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

personne* g_index(groupePersonnes* g, int const index)
{
    if(ExistePersonne(g,index))
    {
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
    return NULL ;
}

void g_remove(groupePersonnes* g, int const index)
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
    if (tmp->previous != NULL) tmp -> previous ->next = tmp->next;
    else g->personnes = tmp -> next;
    if (tmp->next != NULL) tmp -> next -> previous = tmp -> previous;
    free(tmp);

    


    return;
}





void ReinitialiserCSV()
{
    ofstream entreprise("tmp1.csv") ;
    if(entreprise)
    {
        entreprise << "id,nom,code_postal,mail" << endl ;
        entreprise << "1,Disney,77700,walt@disney.com" << endl ;
        entreprise << "2,Google,75009,emplois@google.com" << endl ;
        entreprise << "3,Amazon,65058,contact@amazon.com" << endl ;
        entreprise << "4,Apple,54410,contact@apple.com" << endl ;
        entreprise << "5,Doowap,42754,bonnebrioche@doowap.fr" << endl ;
        entreprise << "6,Poudlard,11499,nimbusdeuxmille@patronus.com" << endl ;
        entreprise << "7,Nintendo,45655,contact@nintendo.jp" << endl ;
        entreprise << "8,Netflix,77548,netflixandchill@tvpopcorn.com" << endl ;
        entreprise << "9,LucasFilm,44485,inagalaxy@farfaraway.us" << endl ;
        entreprise << "10,La Grande Recree,24120,jouetspar@millier.fr" << endl ;
        entreprise << "11,Decathlon,96521,contact@decathlon.com" << endl ;
        entreprise.close() ;
    }
    else cout << "ERREUR 1" << endl ;

    ofstream poste("tmp2.csv") ;
    if(poste)
    {
        poste << "id,titre,entreprise,competences" << endl ;
        poste << "1,Acteur,1,comedie;gag" << endl ;
        poste << "2,Developpeur,2,C;SQL;Python" << endl ;
        poste << "3,Briocheur,5,patisserie" << endl ;
        poste << "4,Mascotte Mickey,1,danse;sport" << endl ;
        poste << "5,Concierge,6,autoritaire;determine" << endl ;
        poste << "6,Professeur de defences contre les forces du mal,6,magie;defencesclfdm" << endl ;
        poste << "7,Chanteur,1,chant" << endl ;
        poste << "8,Professeur de sport,11,sport" << endl ;
        poste << "9,Entraineur,9,jedi" << endl ;
        poste << "10,Developpeur,2,informatique;c;python;java;html" << endl ;
        poste.close() ;
    }
    else cout << "ERREUR 2" << endl ;

    ofstream employes("tmp3.csv") ;
    if(employes)
    {
        employes << "id,nom,prenom,mail,code-postal,competences,collegues,entreprise" << endl ;
        employes << "1,Mouse,Mickey,mickey@mickeyville.com,77700,comedie;chant,2;3;4;5;6,1" << endl ;
        employes << "2,Mouse,Minnie,minnie@mickeyville.com,77700,comedie;chant;danse,1;3;4;6,-1" << endl ;
        employes << "3,Duck,Donald,donald@canardville.com,77730,comedie;humour,1;2;4;6,1" << endl ;
        employes << "4,Duck,Daisy,daisy@canardville.com,77730,chant;danse,1;2;3;6,1" << endl ;
        employes << "5,Lourson,Winnie,potdemiel@miam.com,77752,cuisine;comedie,1;6,-1" << endl ;
        employes << "6,Dingo,Tigrou,tidoublegreou@youpi.com,77752,humour;chant;comedie;danse;cuisine,1;2;3;4;5;7;8;9;10;11;12;13;14;15;16;17;18;19,10" << endl ;
        employes << "7,Brioche,Theo,sam.joli@coeur.fr,13120,patisserie;paschasse;informatique,8;9;6,5" << endl ;
        employes << "8,Scott,Monon,monon@cristalclear.com,38000,chant;abdotransat;informatique,7;6,4" << endl ;
        employes << "9,Delaforet,Mathieu,pasfred@lambda.com,13390,atr;traiderdenavet;informatique,7;8;10;11;12;6,6" << endl ;
        employes << "10,Dumbledore,Albus,percivalwulfric@brian.uk,93400,magie;metamorphose;transplanage;chimiste;savant,9;11;12;6,6" << endl ;
        employes << "11,McGonagall,Minerva,piertotum@locomotor.uk,93400,magie;metamorphose;animagus,9;10;12;13;6,6" << endl ;
        employes << "12,Rogue,Severus,lilyevans@always.uk,93400,magie;chimiste;defencesclfdm,9;10;11;6,6" << endl ;
        employes << "13,Argus,Rusard,cracmol@missteigne.uk,93400,perseverant;determine;autoritaire,10;6,-1" << endl ;
        employes << "14,Dark,Vador,jesuistonpere@obscur.us,66650,force;sith;autoritaire,15;6,9" << endl ;
        employes << "15,Kenobi,Obiwan,monseulespoir@jedi.us,66655,force;jedi;loyal;courageux,14;6,9" << endl ;
        employes << "16,Skywalker,Rey,sithoujedi@kyloren.us,66655,force;jedi,6,-1" << endl ;
        employes << "17,Mua,Sissy,fitgens@houuh.fr,98000,sport;danse,6,-1" << endl ;
        employes << "18,Inshape,Tibo,daamlesgens@whey,81000,sport,19;6,11" << endl ;
        employes << "19,Fitcat,Juju,etcafaitbimbamboum@pshitvroum,81000,sport;danse,18;6,11" << endl ;
        employes.close() ;
    }
    else cout << "ERREUR 3" << endl ;

    remove("entreprises.csv") ;
    remove("postes.csv") ;
    remove("employes.csv") ;
    rename("tmp1.csv","entreprises.csv") ;
    rename("tmp2.csv","postes.csv") ;
    rename("tmp3.csv","employes.csv") ;
}

void SauvegardeJournal()
{
    ifstream journal("journal.txt");  // Flux de lecture
    ofstream sauvegarde("journaltmp.txt"); // Flux d'ecriture
 
   if(journal) // Si le fichier existe bien
   {
      string ligne;
 
      while(getline(journal, ligne)) // On le lis ligne par ligne
      {
            if(sauvegarde) // Si le lieu de destination existe
            {
                sauvegarde << ligne << endl; // On ecrit dans le fichier de destination
            }                      
            else
            {
                cout << "ERREUR: Impossible d'ouvrir journaltmp.txt." << endl;
            }
      }
   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le journal." << endl;
   }
}

void RestaurerJournal()
{
    remove("journal.txt") ;
    rename("journaltmp.txt","journal.txt") ;
}



// // But : Mettre à jour le fichier employes.csv à partir du groupe passé en paramètres
// void g_ecrire(groupePersonnes* gPe)
// {
//     // On ouvre en écriture le fichier tmp.csv (comme il n'existe pas, il est créé)
//     ofstream nouveauCSV("tmp.csv") ;
//     if(nouveauCSV)
//     {
//         // On ouvre en lecture le fichier entreprises.csv
//         ifstream ancienCSV("employes.csv") ;
//         if(ancienCSV)
//         {
//             // On récupère la première ligne et on l'écrit dans le nouveau fichier
//             string ligne ;
//             getline(ancienCSV, ligne) ;
//             nouveauCSV << ligne << endl ;

//             // Maintenant il faut lire le groupe et écrire les informations ligne par ligne
//             node *tmp = gPe->personnes ;
//             personne *pe = NULL ;
//             while (tmp != NULL)
//             {
//                 pe = (personne*)(tmp->data) ;
//                 nouveauCSV << pe->index << "," << pe->nom << "," << pe->prenom << "," << pe->courriel << "," << pe->adresse << "," ;  ;
//                 if(pe->competence[0][0] != '\0') nouveauCSV << pe->competence[0] ;
//                 for (int i = 1; i < 5; i++)
//                 {
//                     if(pe->competence[i][0] != '\0') nouveauCSV << ";" << pe->competence[i] ;
//                 }
//                 nouveauCSV << "," ;
//                 if(pe->amis[0] != NULL) nouveauCSV << pe->amis[0]->index ;
//                 for (int i = 1; i < 5; i++)
//                 {
//                     if(pe->amis[i] != NULL) nouveauCSV << ";" << pe->amis[i]->index;
//                 }
//                 nouveauCSV << "," << pe->entreprise ;
//                 nouveauCSV << endl ;
//                 tmp = tmp->next ;
//             }

//             nouveauCSV.close() ;
//             ancienCSV.close() ;

//             // Il ne reste plus qu'à supprimer l'ancien entreprises.csv et renommer tmp.csv 
//             remove("employes.csv") ;
//             rename("tmp.csv", "employes.csv") ;
//         }
//         else
//         {
//             cout << "ERREUR : Impossible d'ouvrir entreprises.csv" << endl ;
//         }
//     }
//     else
//     {
//         cout << "ERREUR : Impossible d'ouvrir tmp.csv" << endl ;
//     }
// }



// bool g_friends(groupePersonnes* g, int const index_a, int const index_b)
// {
//     personne* a = g_index(g,index_a);
//     personne* b = g_index(g,index_b);
//     if (a == NULL || b == NULL) return false;
//     int i;
//     bool res1=false,res2=false;
//     for(i=0;i<MAX_AMIS;i++){
//         if(a->amis[i]->nom==b->nom){
//                 res1=true;
//         }
//         if(b->amis[i]->nom==a->nom){
//                 res2=true;
//         }
//     }
//     if((res1 == true) && (res2 == true)) return true;
//     return false;
// }

// int g_bestie(groupePersonnes* g, int const index)
// {
//     personne* origin = g_index(g, index);
//     if (origin == NULL || origin->amis[0] == NULL) return -1;
//     int b = origin->amis[0]->index;
//     personne* dest = g_index(g, b);
//     if (dest == NULL || origin->amis[0] == NULL) return -1;
//     if (dest->amis[0]->index == index) return b;
//     else return -1;
// }

// bool g_oneway(groupePersonnes* g, int const index_a, int const index_b)
// {
//     personne* a = g_index(g,index_a);
//     personne* b = g_index(g,index_b);
//     if (a == NULL || b == NULL) return false;
//     int i;
//     bool res1=false,res2=false;
//     for(i=0;i<MAX_AMIS;i++){
//         if(a->amis[i]->nom==b->nom){
//                 res1=true;
//         }
//         if(b->amis[i]->nom==a->nom){
//                 res2=true;
//         }
//     }
//     if((res1 == true) && (res2 == false)) return true;
//     if((res1 == false) && (res2 == true)) return true;
//     return false;
// }

// bool g_linked(groupePersonnes* g, int const index_a, int const index_b)
// {
//     int sec[TAILLE_GPE_MAX]; //tableau d'attente
//     int wet[TAILLE_GPE_MAX];
//     for (int i = 0 ; i<TAILLE_GPE_MAX ; i++){
//         sec[i] = 0;
//         wet[i] = 0;
//     }
//     int i;
//     if (index_a == index_b) return false;
//     personne* origin;
//     int code = 0;
//     origin = g_index(g, index_a);
//     while (code == 0){
//         if (origin==NULL) return false;
//         wet[origin->index-1] = 1;
//         sec[origin->index-1] = 0;
//         int compt=0;
//         personne*parcourami = (personne*)(origin->amis[compt]);
//         while(parcourami != NULL){
//             if (wet[parcourami->index-1] != 1) {
//                 if (parcourami->index == index_b) return true;
//                 else sec[parcourami->index-1] = 1;
//             }
//             compt++;
//             parcourami = (personne*)(origin->amis[compt]);
//         }
//         i = 0;
//         while (sec[i] == 0 && i < TAILLE_GPE_MAX) i++;
//         if (i >= TAILLE_GPE_MAX) return false;
//         else origin = g_index(g, i+1);
//     }
//     return false;
// }

// int g_distance(groupePersonnes* g, int const index_a, int const index_b)
// {
//     int n=1;
   
//      if (index_a==index_b) return 0;
//      if(g_linked(g,index_a,index_b)){
//         personne* a = g_index(g,index_a);
//         personne* b = g_index(g,index_b);
//         personne* tmp = g_index(g,index_a); 
//         personne* aprev = g_index(g,index_b); 
//         int i,l,k;
         
//         while(1){
//             int p=0;  
//             for(l=0;l<MAX_AMIS;l++){
                
//                 if(aprev==a){
//                    if(tmp->amis[0]) tmp=tmp->amis[0];
//                     p=p+1;
//                     l=0;
//                 }
//                 a=tmp;
//                 n=p+2;
//                 if(tmp->amis[l]){
//                 if(a->amis[l]->nom==b->nom) return 1;
//                 a=tmp->amis[l];
//                 k=0;
//                 while(k<MAX_AMIS){
//                     i=0;
//                     for(i=0;i<MAX_AMIS;i++){
//                         if(a->amis[i]){
//                         if(a->amis[i]->nom==b->nom){
//                             return n;
//                         }
//                         }
//                      }
//                     if(tmp->amis[l]->amis[k]) a=tmp->amis[l]->amis[k];
//                     k++;
//                     if(k==1) n++;
//                 }
//              }
//             aprev=a;
//             if(tmp->amis[l+1]) a=tmp->amis[l+1];
//            }
//         }
//      }
//      else return -1;
// }
