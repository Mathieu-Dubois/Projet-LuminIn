#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
using namespace std ;
#include "employe.h"


void creer_profil(char *nom, char *prenom, char *courriel, int adresse, char competence[MAX_COMPETENCES][128], int collegue[MAX_AMIS], int entreprise, groupePersonnes *gPe)
{ 
    int i, j, index; char poub[128];

    //Il faut récupérer en premier lieu l'indice
    FILE *employes = fopen("employes.csv", "r");
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
    //Ensuite on met à jour le groupe d'employés
    personne *p = (personne*)malloc(sizeof(personne));
    p->index = index;
    strcpy(p->nom, nom);
    strcpy(p->prenom, prenom);
    strcpy(p->courriel, courriel);
    p->adresse = adresse;
    p->entreprise = entreprise;
    for (int i = 0; i < MAX_COMPETENCES; i++){
        for (int j = 0; j < 128; j++) p->competence[i][j] = competence[i][j];
        
    }
    for (int i = 0; i < MAX_AMIS; i++)
    {
        p->amis[i] = NULL ;
    }
    

    //On ajoute au bon endroit
    node *parcours = gPe->personnes;
    personne* parcourami;
    int done = 0;
    while (parcours != NULL && done == 0){
        parcourami = (personne*)(parcours->data);
        if(parcourami->index != (index-1)) parcours = parcours->next;
        else done = 1;
    }
    if(parcours == NULL) l_append(&gPe->personnes, l_make_node((personne *)p));
    else l_insert(&parcours, l_make_node((personne *)p));
    //Maintenant on link les amis
    personne* tmpami;
    int compt=0;
    for (int j = 0 ; j < MAX_AMIS ; j++){
        if (collegue[j] != -1){
            parcours = gPe->personnes;
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
    journal_CreationPersonne(p) ;
    g_ecrire(gPe);
    return;
}

void supprimer_profil (int index, groupePersonnes *gPe){
    //On supprime du groupe
    journal_SuppressionPersonne(g_index(gPe, index)) ;
    g_remove(gPe, index);
    g_ecrire(gPe);
}

/*  Entrée :        indice : indice de la personne qui change de code-postal
                    nouv_adresse : changement de code-postal
                    
    Code retour:    0 Si tout se passe bien
                    1 si l'adresse est identique
                    2 si on ne trouve pas l'indice dans le groupe               */
int modifier_adresse(int indice, groupePersonnes *gPe, int nouv_adresse)
{
    node *temp = gPe->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
            if (tmpami->adresse == nouv_adresse) code_retour = 1;   //Si l'adresse est identique
            else {
                tmpami->adresse = nouv_adresse;                     //Si tout se passe bien
                g_ecrire(gPe);
                code_retour = 0;
            }
            trouve = 1;
        }
        else if (trouve == 0){
            temp = temp->next;
        }
    }
    if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondant
    g_ecrire(gPe);
    return code_retour;
}

/*  Entrée :        indice : indice de la personne qui change de mail
                    nouv_adresse : nouvelle adresse mail
                    
    Code retour:    0 Si tout se passe bien
                    1 si l'adresse est identique
                    2 si on ne trouve pas l'indice dans le groupe */      
int modifier_mail(int indice, groupePersonnes *gPe, char *new_mail)
{
    node *temp = gPe->personnes;
    personne *tmpami;
    int trouve = 0, code_retour = -1;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
            if (tmpami->courriel == new_mail) code_retour = 1;   //Si l'adresse est identique
            else {
                strcpy(tmpami->courriel, new_mail);                  //Si tout se passe bien
                g_ecrire(gPe);
                code_retour = 0;
            }
            trouve = 1;
        }
        else if (trouve == 0){
            temp = temp->next;
        }
    }
    if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondant
    g_ecrire(gPe);
    return code_retour;
}

/*  Entrée :        indice : indice de la personne qui change d'entreprise
                    nouv_entre: changement d'entreprise
                    
    Code retour:    0 Si tout se passe bien
                    1 si l'entreprise est identique
                    2 si on ne trouve pas l'indice dans le groupe               */
int modifier_entreprise(int indice, groupePersonnes *gPe, int nouv_entre)
{
    node *temp = gPe->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                                //Quand on atteint la personne souhaitée
            if (tmpami->entreprise == nouv_entre) code_retour = 1;   //Si l'entreprise est identique
            else {
                tmpami->entreprise = nouv_entre;                     //Si tout se passe bien
                g_ecrire(gPe);
                code_retour = 0;
            }
            trouve = 1;
        }
        else if (trouve == 0){
            temp = temp->next;
        }
    }
    if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondant
    g_ecrire(gPe);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui change d'entreprise
                    comp[128]: competence à ajouter
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne a déjà cette compétence
                    2 si la personne a déjà la nombre maximum de compétences
                    3 si on ne trouve pas l'indice dans le groupe               */
int ajouter_competence(int indice, groupePersonnes *gPe, char comp[128])
{
    node *temp = gPe->personnes;
    personne*tmpami;
    int trouve = 0, code_retour = -1, i, fait = 0;
    while(temp != NULL && trouve ==0){
        tmpami = (personne*)(temp->data);
        if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
            i = 0;
            trouve = 1;                          
            while(i<MAX_COMPETENCES && fait == 0){
                if (tmpami->competence[i][0] == '\0'){              //Si il reste de la place on ajoute la compétence
                    strcpy(tmpami->competence[i], comp);
                    g_ecrire(gPe);
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
    g_ecrire(gPe);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui quitte son entreprise
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne n'a pas d'entreprise
                    2 si on ne trouve pas l'indice dans le groupe               */
int quitter_entreprise(int indice, groupePersonnes *gPe)
{
    node *temp = gPe->personnes;
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
    g_ecrire(gPe);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui veut ajouter un collègue
                    col : indice du collègue que la personne veut ajouter
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne a déjà cette personne en ami
                    2 si la personne n'est pas dans la même entreprise
                    3 si on ne trouve pas l'indice dans le groupe  
                    4 si la personne a deja trop d'amis
                    5 si la personne veut s'ajouter elle même en collègue           */
int ajouter_collegue(int indice, groupePersonnes *gPe, int col)
{
    if(indice == col) return 5 ;
    node *temp = gPe->personnes;
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
                node *parcours = gPe->personnes;
                personne*parcourami;
                i = 0;
                fait = 0;                    
                while(i< MAX_AMIS && fait == 0){
                    if (tmpami->amis[i]== NULL){                        //Endroit ou on va ajouter le collègue
                        while (parcours != NULL && fait == 0){
                            parcourami = (personne*)(parcours->data);
                            if (parcourami->index == col){
                                // if(parcourami->entreprise == tmpami -> entreprise){
                                tmpami->amis[i] = parcourami;
                                code_retour = 0;
                                // } else code_retour= 2;
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
    g_ecrire(gPe);
    return code_retour;
}

/*  Entrée :        indice : indice de la personne qui rejoint une entreprise
                    entre : indice de l'entreprise que la personne rejoint
                    
    Code retour:    0 Si tout se passe bien
                    1 si on ne trouve pas l'indice de la personne dans le groupe
                    2 si on a pas assez de place pour ajouter tous les collegues          */
int rejoindre_entreprise(int indice, groupePersonnes *gPe, int entre)
{
    node *temp = gPe->personnes;
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
        node *parcours = gPe->personnes;
        personne*parcourami;
        while(parcours != NULL){
            parcourami = (personne*)(parcours->data);
            if (parcourami->entreprise == tmpami->entreprise){                  //Quand on rencontre un potentiel collègue
                code_retour = ajouter_collegue(indice, gPe, parcourami->index);
                ajouter_collegue(parcourami->index, gPe, indice);                 //On ajoute aussi la personne en collègue aux employes
                if(code_retour == 4) code_retour = 2;
                else code_retour = 0;                 
            }
            parcours = parcours -> next;
        }
    }
    g_ecrire(gPe);
    return code_retour;
}


/*  Entrée :        indice : indice de la personne qui veut supprimer un collègue
                    col : indice du collègue que la personne veut supprimer
                    
    Code retour:    0 Si tout se passe bien
                    1 si la personne n'a pas cette personne en ami
                    2 si on ne trouve pas l'indice dans le groupe                         */
int supprimer_collegue(int indice, groupePersonnes *gPe, int col)
{
    node *temp = gPe->personnes;
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
    g_ecrire(gPe);
    return code_retour;
}

// printemployes
// But : Afficher l'index, le nom et le prénom de toutes les personnes d'un même groupe
void AfficherPersonnes(groupePersonnes* gPe)
{
 if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;
    else
    {
        node *tmp = gPe->personnes ;
        personne *e = (personne*)tmp->data ;
        while (e!= NULL && tmp != NULL)
        {
            cout << e->index << " - " << e->nom << " " << e->prenom << endl ; /* << " - " << e->courriel << " - " << e->entreprise << endl ; */
            tmp = tmp->next ;
            if(tmp != NULL) e = (personne*)tmp->data ;   
        }
    }
}


// But : Afficher l'index, le nom et le prénom de toutes les personnes que cette personne a en ami
void AfficherAmis(groupePersonnes* gPe, int index)
{
    if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;
    else
    {
        for (int i = 0; i < MAX_AMIS; i++)
        {
            if(g_index(gPe,index)->amis[i] != NULL)
            {
                cout << g_index(gPe,index)->amis[i]->index << ". " << g_index(gPe,index)->amis[i]->nom << " " << g_index(gPe,index)->amis[i]->prenom << endl ;
            }
        }
        
    }
    
        
}

// But : Déterminer si une personne fait partie du groupe passé en paramètres
int ExistePersonne(groupePersonnes* gPe, int const indexP)
{
    // Si le groupe est vide, la personne n'existe pas, on retourne 0
    if (gPe->personnes == NULL) return 0;

    // Si l'index demandé est supérieur à l'index de la dernière personne, la personne n'existe pas, on retourne 0
    if(indexP > LastPersonne(gPe) || indexP < 0) return 0 ;

    // Sinon on parcourt tout le groupe jusqu'à trouver (ou non) la personne voulue
    node *tmp = gPe->personnes;
    personne *p = (personne*)tmp->data;
    while(p->index != indexP && p != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        p = (personne*)tmp->data;
    } 
    if (p->index == indexP) return 1 ; // On l'a trouvé, on retourne 1
    // On l'a pas trouvé, on retourne 0
    return 0;
}

// But : Déterminer l'index de la dernière personne d'un groupe de type groupePersonnes
int LastPersonne(groupePersonnes* gPe)
{
    int index(0) ;
    node *tmp = gPe->personnes ;
    tmp = l_tail(tmp) ;
    personne *p = (personne*)tmp->data ;
    index = p->index ;

    return index ;
}

int printemployes(groupePersonnes* gPe)
{
    cout << "VIEUX PRINT" << endl ;

    return 0 ;
}


// But : Afficher les informations de tous les postes à pourvoir ayant dans leur description
//       au moins une compétence du chercheur d'emploi
void PersonneRecherchePosteParCompetence(personne* pe, groupePostes* gP, groupeEntreprises* gE)
{
    int trouve(0), posteDejaAffiche(0);
    if (gP->poste == NULL) cout << "Aucun poste enregistré" << endl ;
    else
    {    
        // pour voir si il y a un match de compétence
        string competenceRecherchee ; // La compétence que l'on cherche
        string competenceComparee ; // La compétence que l'on va comparer avec la compétence que l'on cherche

        node *tmp = gP->poste ;
        poste *posteCourant = (poste*)tmp->data ;
        while (posteCourant!= NULL && tmp != NULL)
        {
            posteDejaAffiche = 0 ;
            // On parcourt toutes les compétences du poste pour voir si il y a un match
            for (int i = 0; i < MAX_COMPETENCES; i++)
            {
                competenceComparee = "" ;
                if(posteCourant->competence[i][0] != '\0') competenceComparee = string(posteCourant->competence[i]) ;
                if(competenceComparee == "") ; // On a aucune compétence à comparer, on ne fait rien
                else
                {
                    // On parcourt toutes les compétences de la personne pour voir si il y a un match
                    for (int i = 0; i < MAX_COMPETENCES; i++)
                    {
                        if(!posteDejaAffiche)
                        {
                            competenceRecherchee = "" ;
                            if(pe->competence[i][0] != '\0') competenceRecherchee = string(pe->competence[i]) ;
                            if(competenceRecherchee == "") ; // On a aucune compétence à rechercher, on ne fait rien
                            else
                            {
                                if(competenceRecherchee == competenceComparee)
                                {
                                    trouve = 1 ;
                                    posteDejaAffiche = 1 ;
                                    cout << "Titre du poste : " << posteCourant->titre << " dans l'entreprise " <<
                                    g_indexEntreprise(gE,posteCourant->entreprise)->nom << 
                                    " (mail : " << g_indexEntreprise(gE,posteCourant->entreprise)->courriel <<
                                    " - code postal : " << g_indexEntreprise(gE,posteCourant->entreprise)->code_postal << ")" << endl ;
                                    journal_PosteApparuRecherche(posteCourant,g_indexEntreprise(gE,posteCourant->entreprise)) ;
                                }
                            }
                        } 
                    }
                }
            }       
            // on passe au poste suivant
            tmp = tmp->next ;
            if(tmp != NULL) posteCourant = (poste*)tmp->data ;
        }
        // Si on a rien trouvé, on l'indique à l'utilisateur
        if(!trouve)
        {
            cout << "Aucun poste ne correspond à votre profil" << endl ;
            journal_RechercheSansResultat() ;
        }
    }
}

// But : Afficher les informations de tous les postes à pourvoir ayant dans leur description au moins 
//       une compétence du chercheur d'emploi ssi l'entreprise qui propose ce poste à le même code postal
void PersonneRecherchePosteParCompetenceEtCode(personne* pe, groupePostes* gP, groupeEntreprises* gE)
{
    int trouve(0), posteDejaAffiche(0);
    if (gP->poste == NULL) cout << "Aucun poste enregistré" << endl ;
    else
    {    
        // pour voir si il y a un match de compétence
        string competenceRecherchee ; // La compétence que l'on cherche
        string competenceComparee ; // La compétence que l'on va comparer avec la compétence que l'on cherche

        // on récupère l'adresse de la personne qui fait la recherche
        int adressePersonne = pe->adresse ;

        node *tmp = gP->poste ;
        poste *posteCourant = (poste*)tmp->data ;
        while (posteCourant!= NULL && tmp != NULL)
        {
            posteDejaAffiche = 0 ;
            // On récupère l'adresse de l'entreprise qui propose le poste pour la comparer à celle de la personne
            int adresseEntreprise = g_indexEntreprise(gE,posteCourant->entreprise)->code_postal ;

            if(adressePersonne == adresseEntreprise)
            {
                // On parcourt toutes les compétences du poste pour voir si il y a un match
                for (int i = 0; i < MAX_COMPETENCES; i++)
                {
                    competenceComparee = "" ;
                    if(posteCourant->competence[i][0] != '\0') competenceComparee = string(posteCourant->competence[i]) ;
                    if(competenceComparee == "") ; // On a aucune compétence à comparer, on ne fait rien
                    else
                    {
                        // On parcourt toutes les compétences de la personne pour voir si il y a un match
                        for (int i = 0; i < MAX_COMPETENCES; i++)
                        {
                            if(!posteDejaAffiche)
                            {
                                competenceRecherchee = "" ;
                                if(pe->competence[i][0] != '\0') competenceRecherchee = string(pe->competence[i]) ;
                                if(competenceRecherchee == "") ; // On a aucune compétence à rechercher, on ne fait rien
                                else
                                {
                                    if(competenceRecherchee == competenceComparee)
                                    {
                                        trouve = 1 ;
                                        posteDejaAffiche = 1 ;
                                        cout << "Titre du poste : " << posteCourant->titre << " dans l'entreprise " <<
                                        g_indexEntreprise(gE,posteCourant->entreprise)->nom << 
                                        " (mail : " << g_indexEntreprise(gE,posteCourant->entreprise)->courriel <<
                                        " - code postal : " << g_indexEntreprise(gE,posteCourant->entreprise)->code_postal << ")" << endl ;
                                        journal_PosteApparuRecherche(posteCourant,g_indexEntreprise(gE,posteCourant->entreprise)) ;
                                    }
                                }
                            } 
                        }
                    }
                }
            }       
            // on passe au poste suivant
            tmp = tmp->next ;
            if(tmp != NULL) posteCourant = (poste*)tmp->data ;
        }
        // Si on a rien trouvé, on l'indique à l'utilisateur
        if(!trouve)
        {
            cout << "Aucun poste ne correspond à votre profil" << endl ;
            journal_RechercheSansResultat() ;
        }
    }
}

// But : Afficher les informations de tous les collègues de son réseau qui travaillent
//       actuellement dans l'entreprise demandée
void PersonneRechercheCollegueParEntreprise(groupePersonnes* gPe, int indexPe, int indexE)
{
    int trouve(0) ;

    if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;
    else
    {
        // On récupère les informations de la personne qui fait la recherche
        personne *pe = g_index(gPe, indexPe) ;

        // On parcourt son réseau de collègue et on affiche tous ceux dont l'index de l'entreprise est le même que l'index demandé
        for (int i = 0; i < MAX_AMIS; i++)
        {
            if(pe->amis[i] != NULL)
            {
                if(pe->amis[i]->entreprise == indexE)
                {
                    cout << "- " << pe->amis[i]->nom << " " << pe->amis[i]->prenom << " (" << pe->amis[i]->courriel << ")" << endl ;
                    journal_PersonneApparuRecherche(pe->amis[i]) ;
                    trouve = 1 ;
                }
            }
        }
    }
    // Si on a rien trouvé, on l'indique à l'utilisateur
    if(!trouve)
    {
        cout << "Aucun collègue de votre réseau travaille dans cette entreprise" << endl ; 
        journal_RechercheSansResultat() ;
    }  
}

// But : Afficher les informations de tous les collègues de son réseau qui travaillent dans une
//       entreprise proposant un poste avec une compétence en commum avec la personne qui fait
//       la recherche
void PersonneRechercheCollegueParCompetence(personne* pe, groupeEntreprises* gE, groupePostes* gP)
{
    int indexE(0), trouve(0), collegueDejaAffiche(0) ;
    string competencePersonne ;
    string competencePoste ;

    if (gE->entreprise == NULL) cout << "Aucune entreprise enregistré" << endl ;
    else if (gP->poste == NULL) cout << "Aucun poste enregistré" << endl ;
    else
    {
        for (int i = 0; i < MAX_AMIS; i++)
        {
            if(pe->amis[i] != NULL)
            {
                // On récupère le i-ème collègue de la personne
                personne* collegue = pe->amis[i];
                // cout << "Collègue n°" << collegue->index << endl ;
                collegueDejaAffiche = 0 ;

                // On récupère l'indice de l'entreprise dans laquelle travaille ce collègue
                indexE = collegue->entreprise ;
                // Si le collègue est actuellement employé
                if(indexE != -1)
                {
                    // cout << "   Travaillant dans l'entreprise n°"<< indexE << endl ;

                    // On parcourt le groupe de postes pour vérifier uniquement ceux proposé par l'entreprise du collègue
                    node *p_gP = gP->poste ;
                    poste *posteCourant = (poste*)p_gP->data ;
                    while (posteCourant!= NULL && p_gP != NULL)
                    {
                        // si le poste courant appartient à l'entreprise du collègue
                        if(posteCourant->entreprise == indexE)
                        {   
                            // cout << "       poste : " << posteCourant->titre << endl ;

                            // Pour chaque compétence de la personne
                            for (int i = 0; i < MAX_COMPETENCES; i++)
                            {
                                if(!collegueDejaAffiche)
                                {
                                    competencePersonne = "" ;
                                    if(pe->competence[i][0] != '\0') competencePersonne = string(pe->competence[i]) ;
                                    // Si la i-eme compétence est renseignée
                                    if(competencePersonne != "")
                                    {
                                        // cout << "           " << competencePersonne << " : " ;
                                        // Pour chaque compétence du poste
                                        for (int j = 0; j < MAX_COMPETENCES; j++)
                                        {
                                            competencePoste = "" ;
                                            if(posteCourant->competence[j][0] != '\0') competencePoste = string(posteCourant->competence[j]) ;
                                            // Si la i-ème compétence est renseignée
                                            if(competencePoste != "")
                                            {
                                                // cout << competencePoste << " - " ;
                                                if(competencePersonne == competencePoste)
                                                {
                                                    cout << "- " << collegue->nom << " " << collegue->prenom << " (" << collegue->courriel << ")" << endl ;
                                                    journal_PersonneApparuRecherche(collegue) ;
                                                    trouve = 1 ;
                                                    collegueDejaAffiche = 1 ;
                                                }     
                                            }
                                        }
                                        // cout << endl ;
                                    }
                                }
                                
                            } 
                            // cout << endl ;
                        }
                    
                        // On passe au poste suivant
                        p_gP = p_gP->next ;
                        if(p_gP != NULL) posteCourant = (poste*)p_gP->data ;
                    }
                }
                
                

                
            }
        }
    
    }
    // Si on a rien trouvé, on l'indique à l'utilisateur
    if(!trouve)
    {
        cout << "Aucun collègue de votre réseau ne travaille dans une entreprise pouvant vous proposer un poste" << endl ;
    } 
    
}

// But : Déterminer si une personne fait partie du réseau de collègue d'une autre personne
int ExisteCollegue(personne* pe, int const indexCo)
{
    // On parcourt le réseau de collègues de la personne jusqu'à trouver (ou non) d'index du collègue
    for (int i = 0; i < MAX_AMIS; i++)
    {
        if(pe->amis[i] != NULL)
        {
            if(pe->amis[i]->index == indexCo) return 1 ;
        }
    }  
    // On l'a pas trouvé, on retourne 0
    return 0;
}

















// Cimetière ***********************************************************************************

// /*  Entrée :        indice : indice de la personne qui veut rechercher un poste
                    
//     Code retour:    0 Si tout se passe bien mais qu'on a pas trouvé de match
//                     1 Si tout se passe bien et qu'on a trouvé au moins un match
//                     2 si on ne trouve pas l'indice dans le groupe                         */
// int recherche_poste_comp(int indice, groupePersonnes *gPe, groupePostes *gPostes, groupeEntreprises *gEntre)
// {
//     int trouve = 0, code_retour = 0, i, j, fait = 0;
//     node *temp = gPe->personnes;
//     personne*tmpami;

//     node*temposte = gPostes->poste;
//     poste*amiposte;

    
//     while(temp != NULL && trouve ==0){
//         tmpami = (personne*)(temp->data);
//         if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
//             i = 0;
//             trouve = 1;   
//             while (temposte != NULL){
//                 amiposte = (poste*)(temposte->data);
//                 j = 0;
//                 while(j < 5){
//                     if (amiposte->competence[j][0] != '\0'){
//                         i = 0;     
//                         tmpami = (personne*)(temp->data);                  
//                         while(i<5 && fait == 0){
//                             if (tmpami->competence[i][0] != '\0'){              //Si il a une competence, on va chercher les match
//                                 if (!strcmp(amiposte->competence[j], tmpami->competence[i])){
//                                     code_retour = 1;
//                                     AfficherPoste(gPostes, amiposte->index, gEntre);
//                                     fait = 1;
//                                 }
                                
//                             } 
//                             i++;
//                         }  
                        
//                     }
//                     j++;
//                 }
//                 temposte = temposte->next;
//             }
            

//         } else {
//             temp = temp -> next;
//         }
//     }
//     if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondan
//     return code_retour;
// }


// /*  Entrée :        indice : indice de la personne qui veut rechercher un poste
                    
//     Code retour:    0 Si tout se passe bien mais qu'on a pas trouvé de match
//                     1 Si tout se passe bien et qu'on a trouvé au moins un match
//                     2 si on ne trouve pas l'indice dans le groupe                         */
// int recherche_poste_postal(int indice, groupePersonnes *gPe, groupePostes *gPostes, groupeEntreprises *gEntre)
// {
//     int trouve = 0, trouveentre = 0, code_retour = 0;
//     node *temp = gPe->personnes;
//     personne*tmpami;

//     node*temposte = gPostes->poste;
//     poste*amiposte;

//     node*tempentre = gEntre->entreprise;
//     entreprise*amientre;

    
//     while(temp != NULL && trouve ==0){
//         tmpami = (personne*)(temp->data);
//         if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
//             trouve = 1;   
//             while (temposte != NULL){                               //On cherche parmi les postes
//                 amiposte = (poste*)(temposte->data);
//                 trouveentre = 0;
//                 while (tempentre != NULL && trouveentre == 0){                          //On recherche parmi les entreprises
//                     amientre = (entreprise*)(tempentre->data);
//                     if(amientre->index == amiposte->entreprise){
//                         trouveentre = 1;
//                         if(amientre->code_postal == tmpami->adresse){
//                             code_retour = 1;
//                             AfficherPoste(gPostes, amiposte->index, gEntre);
//                         }
//                     } else tempentre = tempentre->next;
//                 }
//                 temposte = temposte->next;
//             }
//         } else temp = temp -> next;
//     }
//     if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondan
//     return code_retour;
// }


// /*  Entrée :        indice : indice de la personne qui fait la recherche
//                     index : indice de l'entreprise à laquelle doivent appartenir les anciens collègues
                    
//     Code retour:    0 Si tout se passe bien mais qu'on a pas trouvé de match
//                     1 Si tout se passe bien et qu'on a trouvé au moins un match
//                     2 si on ne trouve pas l'indice dans le groupe                         */
// int recherche_col_par_entre(int indice, groupePersonnes *gPe, int index)
// {
//     int trouve = 0, code_retour = 0, i;
//     node *temp = gPe->personnes;
//     personne*tmpami;
    
//     while(temp != NULL && trouve ==0){
//         tmpami = (personne*)(temp->data);
//         if (tmpami->index == indice){                               //Quand on atteint la personne souhaitée
//             i = 0;
//             trouve = 1;   
//             while (tmpami->amis[i] != NULL){                           //On recherche parmi ses amis
//                 if (tmpami->amis[i]->entreprise == index){
//                     code_retour = 1;
//                     printf("- %s | %s | %s\n", tmpami->amis[i]->nom, tmpami->amis[i]->prenom, tmpami->amis[i]->courriel);
//                 }
//                 i++;
//             }
//         } else temp = temp -> next;
//     }
//     if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondan
//     return code_retour;
// }


// /*  Entrée :        indice : indice de la personne qui veut rechercher un collègue
                    
//     Code retour:    0 Si tout se passe bien mais qu'on a pas trouvé de match
//                     1 Si tout se passe bien et qu'on a trouvé au moins un match
//                     2 si on ne trouve pas l'indice dans le groupe                         */
// int recherche_col_comp(int indice, groupePersonnes *gPe, char comp[128])
// {
//     int trouve = 0, code_retour = 0, i, j, fait = 0;
//     node *temp = gPe->personnes;
//     personne*tmpami;

//     while(temp != NULL && trouve ==0){
//         tmpami = (personne*)(temp->data);
//         if (tmpami->index == indice){                                       //Quand on atteint la personne souhaitée
//             i = 0;
//             trouve = 1;   
//             while (tmpami->amis[i] != NULL && fait ==0){
//                 j = 0;
//                 while(tmpami->amis[i]->competence[j][0] != '\0' && fait ==0){
//                     if (!strcmp(tmpami->amis[i]->competence[j], comp)){ //Si la personne correspond
//                         code_retour = 1;
//                         printf("- %s | %s | %s\n", tmpami->amis[i]->nom, tmpami->amis[i]->prenom, tmpami->amis[i]->courriel);
//                         fait = 1;
//                     }
//                     j++;
//                 } 
//                 i++;
//             }  
            
//         } else temp = temp -> next;
//     }
//     if (trouve == 0) code_retour = 2;                               //Si on ne trouve pas l'index correspondan
//     return code_retour;
// }

