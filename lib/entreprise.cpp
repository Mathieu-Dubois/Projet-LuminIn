#include <iostream>
using namespace std ;
#include <fstream>
#include <string>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "entreprise.h"
#include "groupe.h"
#include "liste.h"
#include "journal.h"


// But : Création d'un groupe d'entreprise à partir d'un flux donné
groupeEntreprises* g_openEntreprisesCSV(FILE *db)
{
    groupeEntreprises *gE = NULL ;
    gE = (groupeEntreprises*)malloc(sizeof(groupeEntreprises));
    gE->entreprise = NULL ;
    entreprise data;

    // On "supprime" la première ligne du fichier car elle ne contient aucune donnée
    char poubelle[100]; 
    fscanf(db, "%s\n", poubelle);

    /* Puis on lit le fichier jusqu'à la fin en lisant à chaque fois :
     - un numéro correspondant à l'index de l'entreprise dans le fichier puis une virgule
     - une chaine de caractères correspondant au nom de l'entreprise puis une virgule
     - un numéro à 5 chiffres correspondant au code postale de l'entreprise puis une virgule
     - une chaine de caractères correspondant à l'adresse mail de l'entreprise puis un retour à la ligne

     Pour chaque ligne lue, on ajoute au groupe l'entreprise contenant les informations lues
     Si ces conditions ne sont pas vérifiées, cela signifie que le fichier a été lu en entier
     On retourne alors le groupe créé */
    while(fscanf(db, "%d,%128[^,],%d,%128[^\n]\n", &data.index, data.nom, &data.code_postal, data.courriel) == 4)
    {
        entreprise *e = (entreprise*)malloc(sizeof(entreprise));
        *e = data;
        l_append(&gE->entreprise, l_make_node((entreprise *)e));
    }

    return gE;
}

// But : Déterminer la taille d'un groupe de type : groupeEntreprises
int gEntreprise_size(groupeEntreprises* gE)
{
    return l_length(gE->entreprise);
}

// But : Afficher l'index et le nom de toutes les entreprises d'un même groupe
void AfficherEntreprises(groupeEntreprises* g)
{
    if (g->entreprise == NULL) cout << "Aucune entreprise enregistrée" << endl ;
    else
    {
        node *tmp = g->entreprise ;
        entreprise *e = (entreprise*)tmp->data ;
        while (e!= NULL && tmp != NULL)
        {
            cout << e->index << " - " << e->nom  << endl ;
            tmp = tmp->next ;
            if(tmp != NULL) e = (entreprise*)tmp->data ;
        }
    }
}

// But : Ajouter une entreprise à un groupe de type groupeEntreprises
void AjoutEntreprise(groupeEntreprises *gE, char nom[40], int code_postal, char courriel[128])
{
    // On récupère l'index de la dernière entreprise du groupe
    int index(0) ;
    index = LastEntreprise(gE) ; 
    
    // On créé une nouvelle entreprise et on lui attribue tout ses paramètres
    // Remarque : l'index de la nouvelle entreprise = index de la dernière entreprise du groupe + 1
    entreprise *nouveau = (entreprise*)malloc(sizeof(entreprise)) ;
    nouveau->index = index + 1 ;    
    strcpy(nouveau->nom, nom) ;
    nouveau->code_postal = code_postal;
    strcpy(nouveau->courriel, courriel) ;

    journal_CreationEntreprise(nouveau) ;


    // Ajout de la nouvelle entreprise au groupe
    l_append(&gE->entreprise, l_make_node((entreprise*)nouveau)) ;

    // Ajout de la nouvelle entreprise dans le fichier CSV
    ofstream fichier("entreprises.csv", ios::app) ;
    fichier << index+1 << "," << nom << "," << code_postal << "," << courriel << endl ;
    fichier.close() ;
}

// But : Déterminer l'index de la dernière entreprise d'un groupe de type groupeEntreprises
int LastEntreprise(groupeEntreprises* gE)
{
    int index(0) ;
    node *tmp = gE->entreprise ;
    tmp = l_tail(tmp) ;
    entreprise *e = (entreprise*)tmp->data ;
    index = e->index ;

    return index ;
}

// But : Déterminer si une entreprise fait partie du groupe passé en paramètres
int ExisteEntreprise(groupeEntreprises*gE, int const indexE)
{
    // Si le groupe est vide, l'entreprise n'existe pas, on retourne 0
    if (gE->entreprise == NULL) return 0;

    // Si l'index demandé est supérieur à l'index de la dernière entreprise, l'entreprise n'existe pas, on retourne 0
    if(indexE > LastEntreprise(gE) || indexE < 0) return 0 ;

    // Sinon on parcourt tout le groupe jusqu'à trouver (ou non) l'entreprise voulue
    node *tmp = gE->entreprise;
    entreprise *e = (entreprise*)tmp->data;
    while(e->index != indexE && e != NULL && tmp->next !=NULL){
        tmp = tmp -> next;
        e = (entreprise*)tmp->data;
    } 
    if (e->index == indexE) return 1 ; // On l'a trouvé, on retourne 1
    // On l'a pas trouvé, on retourne 0
    return 0;
}

// But : Accéder à une entreprise du groupe pour la manipuler
entreprise* g_indexEntreprise(groupeEntreprises* gE, int const indexE)
{
    // Si l'entreprise recherchée existe, on va la chercher et on la retourne
    if(ExisteEntreprise(gE,indexE))
    {
        node *tmp = gE->entreprise;
        entreprise *e = (entreprise*)tmp->data;
        while(e->index != indexE && e != NULL && tmp->next !=NULL)
        {
            tmp = tmp -> next;
            e = (entreprise*)tmp->data;
        }
        if (e->index == indexE) return e ; 
    }

    // Sinon on affiche un message d'erreur et on retourne NULL
    else cout << "ERREUR ID ENTREPRISE" ;
    return NULL ;
}

// But : Supprimer une entreprise du groupe passé en paramètres et du fichier entreprises.csv
groupeEntreprises* SupprimerEntreprise(groupeEntreprises* gE, int const indexE)
{
    // On va chercher l'entreprise dans le groupe
    assert (gE) ;
    node *tmp = gE->entreprise ;
    entreprise *e = (entreprise*)tmp->data ;
    while (e->index != indexE)
    {
        tmp = tmp->next ;
        e = (entreprise*)(tmp->data) ;
    }
   
    journal_SuppressionEntreprise(e) ;
    // On raccroche les noeuds entre eux pour enlever l'entreprise
    if(tmp->previous != NULL) tmp->previous->next = tmp->next ;
    else gE->entreprise = tmp->next ;
    if(tmp->next != NULL) tmp->next->previous = tmp->previous ;
    
    // On libère la mémoire contenant l'entreprise supprimée
    free(tmp) ;

    // Puis on met à jour entreprises.csv
    g_ecrireEntreprise(gE) ;

    return gE ;
}

// But : Mettre à jour le fichier entreprises.csv à partir du groupe passé en paramètres
void g_ecrireEntreprise(groupeEntreprises* gE)
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

            // Maintenant il faut lire le groupe et écrire les informations ligne par ligne
            node *tmp = gE->entreprise ;
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

// But : Afficher le nom, le prénom et l'adresse mail de tous les chercheurs d'emploi possédant la compétence demandée
void EntrepriseRechercheParCompetence(groupePersonnes* gPe, char competence[128])
{
    int trouve(0) ;

    if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;

    // On parcourt tout le groupe
    else
    {
        node *tmp = gPe->personnes ;
        personne *p = (personne*)tmp->data ;
        while (p!= NULL && tmp != NULL)
        {
            // Si la personne courante est un chercheur d'emploi (ie : entreprise = -1)
            if(p->entreprise == -1)
            {
                // On regarde toutes ces compétences 
                for (int i = 0; i < 5; i++)
                {
                    // Si une compétence correspond à la compétence recherchée, on affiche la personne
                    if (!strcmp(competence, p->competence[i]))
                    {
                        if(trouve == 0) cout << endl << "Liste des chercheurs d'emploi possédant la compétence " << competence << " : " << endl ;
                        cout << p->nom << " - " << p->prenom << " - " << p->courriel << endl ;
                        trouve = 1 ;
                    }
                }
            }
            tmp = tmp->next ;
            if(tmp != NULL) p = (personne*)tmp->data ;
        }

        // Si on a rien trouvé, on l'indique à l'utilisateur
        if(!trouve) cout << "Aucun chercheur d'emploi ne correspond à votre recherche" << endl ;
    }
}

// But : Afficher le nom, le prénom et l'adresse mail de tous les chercheurs d'emploi possédant la compétence et le code postal demandée
void EntrepriseRechercheParCompetenceEtCode(groupePersonnes* gPe, char competence[128], int code_postal)
{
    int trouve(0) ;

    if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;
    // On parcourt tout le groupe
    else
    {
        node *tmp = gPe->personnes ;
        personne *p = (personne*)tmp->data ;
        while (p!= NULL && tmp != NULL)
        {
            // Si la personne courante est un chercheur d'emploi (ie : entreprise = -1)
            if(p->entreprise == -1)
            {
                // Et que le code postal de cette personne est celui demandé
                if (p->adresse == code_postal)
                {
                    // On regarde toutes ces compétences 
                    for (int i = 0; i < 5; i++)
                    {
                        // Si une compétence correspond à la compétence recherchée, on affiche la personne
                        if (!strcmp(competence, p->competence[i]))
                        {
                             if(trouve == 0) cout << endl << "Liste des chercheurs d'emploi possédant la compétence " << competence << " et le code postal " << code_postal << " :" << endl ;
                            cout << p->nom << " - " << p->prenom << " - " << p->courriel << endl ;
                            trouve = 1 ;
                        }
                    }
                }
            }
            
            tmp = tmp->next ;
            if(tmp != NULL) p = (personne*)tmp->data ;
        }

        // Si on a rien trouvé, on l'indique à l'utilisateur
        if(!trouve) cout << "Aucun chercheur d'emploi ne correspond à votre recherche" << endl ;
    }
}

// But : Supprimer tous les employés d'une entreprise
groupePersonnes* LicencierToutLeMonde(groupePersonnes* gPe, groupeEntreprises* gE, int indexE)
{
    if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;

    // On parcourt tout le groupe
    else
    {
        node *tmp = gPe->personnes ;
        personne *p = (personne*)tmp->data ;
        while (p!= NULL && tmp != NULL)
        {
            // Si la personne courante est un chercheur d'emploi (ie : entreprise = -1)
            if(p->entreprise == indexE)
            {
                p->entreprise = -1 ;
                journal_QuitterEntreprise(p, g_indexEntreprise(gE,indexE)) ;
            }
            tmp = tmp->next ;
            if(tmp != NULL) p = (personne*)tmp->data ;
        }
    }

    return gPe ;
}

// But : Afficher les informations de tous les chercheurs d'emploi ayant une compétence 
//       en commun avec un poste de l'entreprise
void EntrepriseRecherchePersonneParCompetence(groupePersonnes* gPe, groupePostes* gP, int indexE)
{
    int trouve(0), personneDejaAffiche(0) ;
    string competencePoste ;
    string competencePersonne ;

    if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;
    else if (gP->poste == NULL) cout << "Aucun poste enregistré" << endl ;
    else
    {
        // On parcourt toutes les personnes
        node *p_gPe = gPe->personnes ;
        personne *personneCourante = (personne*)p_gPe->data ;
        while (personneCourante!= NULL && p_gPe != NULL)
        {
            // Si cette personne est un chercheur d'emploi
            if(personneCourante->entreprise == -1)
            {
                // On doit regarder si l'une de ses compétence match avec les compétences des postes à pourvoir de l'entreprise
                // On doit donc regarder la liste des postes
                node *p_gP = gP->poste ;
                poste *posteCourant = (poste*)p_gP->data ;
                while (posteCourant!= NULL && p_gP != NULL)
                {
                    // On s'interresse qu'aux postes de l'entreprise
                    if(posteCourant->entreprise == indexE)
                    {
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        personneDejaAffiche = 0 ;
                        // On parcourt toutes les compétences du poste pour voir si il y a un match
                        for (int i = 0; i < 5; i++)
                        {
                            competencePoste = "" ;
                            if(posteCourant->competence[i][0] != '\0') competencePoste = string(posteCourant->competence[i]) ;
                            if(competencePoste == "") ; // On a aucune compétence à comparer, on ne fait rien
                            else
                            {
                                // On parcourt toutes les compétences de la personne pour voir si il y a un match
                                for (int i = 0; i < 5; i++)
                                {
                                    if(!personneDejaAffiche)
                                    {
                                        competencePersonne = "" ;
                                        if(personneCourante->competence[i][0] != '\0') competencePersonne = string(personneCourante->competence[i]) ;
                                        if(competencePersonne == "") ; // On a aucune compétence à rechercher, on ne fait rien
                                        else
                                        {
                                            if(competencePersonne == competencePoste)
                                            {
                                                trouve = 1 ;
                                                personneDejaAffiche = 1 ;
                                                 cout << "- " << personneCourante->nom << " " << personneCourante->prenom << " (" << personneCourante->courriel << ")" << endl ;
                                                journal_PersonneApparuRecherche(personneCourante) ;
                                            }
                                        }
                                    } 
                                }
                            }
                        }       

                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                    // on passe au poste suivant
                    p_gP = p_gP->next ;
                    if(p_gP != NULL) posteCourant = (poste*)p_gP->data ;
                }
            }
            // on passe à la personne suivante
            p_gPe = p_gPe->next ;
            if(p_gPe != NULL) personneCourante = (personne*)p_gPe->data ;
        }
    }
    // Si on a rien trouvé, on l'indique à l'utilisateur
    if(!trouve)
    {
        cout << "Aucun chercheur d'emploi ne correspond à vos postes à pourvoir" << endl ;
        journal_RechercheSansResultat() ;
    }
}

// But : Afficher les informations de tous les chercheurs d'emploi ayant une compétence 
//       en commun avec un poste de l'entreprise ssi l'entreprise et la personne ont le même code postal
void EntrepriseRecherchePersonneParCompetenceEtCode(groupePersonnes* gPe, groupePostes* gP, entreprise* e)
{
    int trouve(0), personneDejaAffiche(0), indexE(0) ;
    string competencePoste ;
    string competencePersonne ;

    if (gPe->personnes == NULL) cout << "Aucune personne enregistrée" << endl ;
    else if (gP->poste == NULL) cout << "Aucun poste enregistré" << endl ;
    else
    {
        // On récupéère l'index de l'entreprise qui fait la recherche
        indexE = e->index ;

        // On parcourt toutes les personnes
        node *p_gPe = gPe->personnes ;
        personne *personneCourante = (personne*)p_gPe->data ;
        while (personneCourante!= NULL && p_gPe != NULL)
        {
            //Si cette personne a le même code postal que l'entreprise
            if(personneCourante->adresse == e->code_postal)
            {
                // Si cette personne est un chercheur d'emploi
                if(personneCourante->entreprise == -1)
                {
                    // On doit regarder si l'une de ses compétence match avec les compétences des postes à pourvoir de l'entreprise
                    // On doit donc regarder la liste des postes
                    node *p_gP = gP->poste ;
                    poste *posteCourant = (poste*)p_gP->data ;
                    while (posteCourant!= NULL && p_gP != NULL)
                    {
                        // On s'interresse qu'aux postes de l'entreprise
                        if(posteCourant->entreprise == indexE)
                        {
                            personneDejaAffiche = 0 ;
                            // On parcourt toutes les compétences du poste pour voir si il y a un match
                            for (int i = 0; i < 5; i++)
                            {
                                competencePoste = "" ;
                                if(posteCourant->competence[i][0] != '\0') competencePoste = string(posteCourant->competence[i]) ;
                                if(competencePoste == "") ; // On a aucune compétence à comparer, on ne fait rien
                                else
                                {
                                    // On parcourt toutes les compétences de la personne pour voir si il y a un match
                                    for (int i = 0; i < 5; i++)
                                    {
                                        if(!personneDejaAffiche)
                                        {
                                            competencePersonne = "" ;
                                            if(personneCourante->competence[i][0] != '\0') competencePersonne = string(personneCourante->competence[i]) ;
                                            if(competencePersonne == "") ; // On a aucune compétence à rechercher, on ne fait rien
                                            else
                                            {
                                                if(competencePersonne == competencePoste)
                                                {
                                                    trouve = 1 ;
                                                    personneDejaAffiche = 1 ;
                                                    cout << "- " << personneCourante->nom << " " << personneCourante->prenom << " (" << personneCourante->courriel << ")" << endl ;
                                                    journal_PersonneApparuRecherche(personneCourante) ;
                                                }
                                            }
                                        } 
                                    }
                                }
                            }       
                        }
                        // on passe au poste suivant
                        p_gP = p_gP->next ;
                        if(p_gP != NULL) posteCourant = (poste*)p_gP->data ;
                    }
                }
            }

            
            // on passe à la personne suivante
            p_gPe = p_gPe->next ;
            if(p_gPe != NULL) personneCourante = (personne*)p_gPe->data ;
        }
    }
    // Si on a rien trouvé, on l'indique à l'utilisateur
    if(!trouve)
    {
        cout << "Aucun chercheur d'emploi ne correspond à vos postes à pourvoir" << endl ;
        journal_RechercheSansResultat() ;
    }
}



