#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <fstream>
#include <string>
using namespace std ;
#include "maintenance.h"

// But : Réinitialiser les trois fichiers csv à leut état initial
//       Cela permet que les fichiers de départs soient identiques à chaque exécution du
//       programme de test.
//       La commande "make reset" fait exactement la même chose
void ReinitialiserCSV()
{
    ofstream entreprise("tmp1.csv") ;
    if(entreprise)
    {
        entreprise << "id,nom,code_postal,mail,mot_de_passe" << endl ;
        entreprise << "1,Disney,77700,walt@disney.com,11496423714628635658" << endl ;
        entreprise << "2,Google,75009,emplois@google.com,11133306840870253038" << endl ;
        entreprise << "3,Amazon,65058,contact@amazon.com,15847797536889294320" << endl ;
        entreprise << "4,Apple,54410,contact@apple.com,5678395738750946751" << endl ;
        entreprise << "5,Doowap,42754,bonnebrioche@doowap.fr,11223670787206848358" << endl ;
        entreprise << "6,Poudlard,11499,nimbusdeuxmille@patronus.com,17672155724294466829" << endl ;
        entreprise << "7,Nintendo,45655,contact@nintendo.jp,10826349166962143310" << endl ;
        entreprise << "8,Netflix,77548,netflixandchill@tvpopcorn.com,12279484559975216856" << endl ;
        entreprise << "9,LucasFilm,44485,inagalaxy@farfaraway.us,18141727040968517239" << endl ;
        entreprise << "10,La Grande Recree,24120,jouetspar@millier.fr,8753650948427237990" << endl ;
        entreprise << "11,Decathlon,96521,contact@decathlon.com,17808258231338552370" << endl ;
        entreprise.close() ;
    }
    else cout << "ERREUR 1" << endl ;

    ofstream poste("tmp2.csv") ;
    if(poste)
    {
        poste << "id,titre,entreprise,competences" << endl ;
        poste << "1,Acteur,1,comedie;gag" << endl ;
        poste << "2,Developpeur,2,c;sql;python" << endl ;
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
        employes << "id,nom,prenom,mail,code-postal,competences,collegues,entreprise,mot_de_passe" << endl ;
        employes << "1,Mouse,Mickey,mickey@mickeyville.com,77700,comedie;chant;sport,2;3;4;5;6,1,15945130241660423850" << endl ;
        employes << "2,Mouse,Minnie,minnie@mickeyville.com,77700,comedie;chant;danse,1;3;4;6,-1,17631803937843566598" << endl ;
        employes << "3,Duck,Donald,donald@canardville.com,77730,comedie;humour,1;2;4;6,1,17466742159995245853" << endl ;
        employes << "4,Duck,Daisy,daisy@canardville.com,77730,chant;danse,1;2;3;6,1,11528681184898398757" << endl ;
        employes << "5,Lourson,Winnie,potdemiel@miam.com,77752,cuisine;comedie,1;6,-1,10654269406589400228" << endl ;
        employes << "6,Dingo,Tigrou,tidoublegreou@youpi.com,77752,humour;chant;comedie;danse;cuisine,1;2;3;4;5;7;8;9;10;11;12;13;14;15;16;17;18;19,10,3785616969478571695" << endl ;
        employes << "7,Brioche,Theo,sam.joli@coeur.fr,13120,patisserie;paschasse;informatique,8;9;6,5,5227873794114946850" << endl ;
        employes << "8,Scott,Monon,monon@cristalclear.com,38000,chant;abdotransat;informatique,7;6,4,7072131466311524309" << endl ;
        employes << "9,Delaforet,Mathieu,pasfred@lambda.com,13390,atr;traiderdenavet;informatique,7;8;10;11;12;6,6,10272462645516849158" << endl ;
        employes << "10,Dumbledore,Albus,percivalwulfric@brian.uk,93400,magie;metamorphose;transplanage;chimiste;savant,9;11;12;6,6,2156238556791444590" << endl ;
        employes << "11,McGonagall,Minerva,piertotum@locomotor.uk,93400,magie;metamorphose;animagus,9;10;12;13;6,6,13364424014865824247" << endl ;
        employes << "12,Rogue,Severus,lilyevans@always.uk,93400,magie;chimiste;defencesclfdm,9;10;11;6,6,7589970862893609860" << endl ;
        employes << "13,Argus,Rusard,cracmol@missteigne.uk,93400,perseverant;determine;autoritaire,10;6,-1,11750370340924194047" << endl ;
        employes << "14,Dark,Vador,jesuistonpere@obscur.us,66650,force;sith,15;6,9,472000277057206899" << endl ;
        employes << "15,Kenobi,Obiwan,monseulespoir@jedi.us,66655,force;jedi;loyal;courageux,14;6,9,15524097890336655359" << endl ;
        employes << "16,Skywalker,Rey,sithoujedi@kyloren.us,66655,force;jedi,6,-1,12270512390958272206" << endl ;
        employes << "17,Mua,Sissy,fitgens@houuh.fr,98000,sport;danse,6,-1,12073259573310696850" << endl ;
        employes << "18,Inshape,Tibo,daamlesgens@whey,81000,sport,19;6,11,16832789318055077984" << endl ;
        employes << "19,Fitcat,Juju,etcafaitbimbamboum@pshitvroum,81000,sport;danse,18;6,11,5851436495799700541" << endl ;
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

// But : Réaliser une sauvegarde du journal dans le fichier journaltmp.txt
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

// But : Permet de restaurer la sauvegarde du journal (supprime journal.txt puis renomme 
//      journaltmp.txt en journal.txt)
//      Cela permet d'éviter que le journal soit modifié quand on lance le programme de test.
//      On veut en effet que je journal ne conseve que les manipulations réalisés dans l'application
void RestaurerJournal()
{
    remove("journal.txt") ;
    rename("journaltmp.txt","journal.txt") ;
}

// But : Réinitialiser les 3 groupes à leur état d'origine
void ViderGroupes(groupeEntreprises* gE, groupePersonnes* gPe, groupePostes* gP)
{
    // On commence par supprimer les 3 groupes
    node *tmp = gP->poste ;
    poste *posteCourant = (poste*)tmp->data ;
    while (posteCourant!= NULL && tmp != NULL)
    {
        SupprimerPoste(gP,posteCourant->index) ;
        // on passe au poste suivant
        tmp = tmp->next ;
        if(tmp != NULL) posteCourant = (poste*)tmp->data ;
    }

    tmp = gE->entreprise ;
    entreprise *entrepriseCourante = (entreprise*)tmp->data ;
    while (entrepriseCourante!= NULL && tmp != NULL)
    {
        SupprimerEntreprise(gE,entrepriseCourante->index) ;
        // on passe à l'entreprise suivante
        tmp = tmp->next ;
        if(tmp != NULL) entrepriseCourante = (entreprise*)tmp->data ;
    }

    tmp = gPe->personnes ;
    personne *personneCourante = (personne*)tmp->data ;
    while (personneCourante!= NULL && tmp != NULL)
    {
        supprimer_profil(personneCourante->index,gPe) ;
        // on passe à la personne suivante
        tmp = tmp->next ;
        if(tmp != NULL) personneCourante = (personne*)tmp->data ;
    }

    ReinitialiserCSV() ;
}

// But : Réaliser une sauvegarde des fichiers csv
void SauvegardeCSV()
{
    ifstream source1("employes.csv");  // Flux de lecture
    ofstream sauvegarde1("employestmp.txt"); // Flux d'ecriture
    if(source1) // Si le fichier existe bien
    {
        string ligne;
    
        while(getline(source1, ligne)) // On le lis ligne par ligne
        {
                if(sauvegarde1) // Si le lieu de destination existe
                {
                    sauvegarde1 << ligne << endl; // On ecrit dans le fichier de destination
                }                      
                else
                {
                    cout << "ERREUR: Impossible d'ouvrir employestmp.txt." << endl;
                }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir employes.csv." << endl;
    }
    source1.close() ;
    sauvegarde1.close() ;

    ifstream source2("entreprises.csv");  // Flux de lecture
    ofstream sauvegarde2("entreprisestmp.txt"); // Flux d'ecriture
    if(source2) // Si le fichier existe bien
    {
        string ligne;
    
        while(getline(source2, ligne)) // On le lis ligne par ligne
        {
                if(sauvegarde2) // Si le lieu de destination existe
                {
                    sauvegarde2 << ligne << endl; // On ecrit dans le fichier de destination
                }                      
                else
                {
                    cout << "ERREUR: Impossible d'ouvrir entreprisestmp.txt." << endl;
                }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir entreprises.csv." << endl;
    }
    source2.close() ;
    sauvegarde2.close() ;

    ifstream source3("postes.csv");  // Flux de lecture
    ofstream sauvegarde3("postestmp.txt"); // Flux d'ecriture
    if(source3) // Si le fichier existe bien
    {
        string ligne;
    
        while(getline(source3, ligne)) // On le lis ligne par ligne
        {
                if(sauvegarde3) // Si le lieu de destination existe
                {
                    sauvegarde3 << ligne << endl; // On ecrit dans le fichier de destination
                }                      
                else
                {
                    cout << "ERREUR: Impossible d'ouvrir postestmp.txt." << endl;
                }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir entreprises.csv." << endl;
    }
    source3.close() ;
    sauvegarde3.close() ;
}

// But : Permet de restaurer la sauvegarde des fichiers CSV 
//       Cela permet d'éviter que la base de données soit modifié quand on lance le programme de test.
void RestaurerCSV()
{
    remove("employes.csv") ;
    rename("employestmp.txt","employes.csv") ;
    remove("entreprises.csv") ;
    rename("entreprisestmp.txt","entreprises.csv") ;
    remove("postes.csv") ;
    rename("postestmp.txt","postes.csv") ;
}