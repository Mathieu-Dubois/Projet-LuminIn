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



