#include <iostream>
#include <fstream>
#include <string>
using namespace std ;

int main()
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
        employes << "id,nom,prenom,mail,code-postal,competences,collegues,entreprise" << endl ;
        employes << "1,Mouse,Mickey,mickey@mickeyville.com,77700,comedie;chant;sport,2;3;4;5;6,1" << endl ;
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
        employes << "14,Dark,Vador,jesuistonpere@obscur.us,66650,force;sith,15;6,9" << endl ;
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


    return 0 ;
}





//  **** Journal de l'application LuminIn, le site des pros ****

// 01-05-2020 12:35:02 : Création du Journal
// 01-05-2020 14:34:54 : Ouverture de l'application 
// 01-05-2020 14:34:54 : Fermeture de l'application 
// 01-05-2020 14:52:40 : Ouverture de l'application 
//     01-05-2020 14:53:29 : Création de l'entreprise 6 - Netflix - 15486 - netflixandchill@party.com
// 01-05-2020 14:53:57 : Fermeture de l'application 
// 01-05-2020 15:01:09 : Ouverture de l'application 
//     01-05-2020 15:01:21 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//     01-05-2020 15:01:17 : Déconnexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//     01-05-2020 15:01:31 : Connexion de l'entreprise 6 - Netflix - 15486 - netflixandchill@party.com
//     01-05-2020 15:01:38 : Déconnexion de l'entreprise 6 - Netflix - 15486 - netflixandchill@party.com
//     01-05-2020 15:01:54 : Connexion de l'entreprise 4 - Apple - 54410 - contact@apple.com
//     01-05-2020 15:01:59 : Déconnexion de l'entreprise 4 - Apple - 54410 - contact@apple.com
// 01-05-2020 15:02:01 : Fermeture de l'application 
// 01-05-2020 15:10:03 : Ouverture de l'application 
//     01-05-2020 15:10:14 : Connexion de l'entreprise 6 - Netflix - 15486 - netflixandchill@party.com
//         01-05-2020 15:10:28 : Suppression de l'entreprise 6 - Netflix - 15486 - netflixandchill@party.com
// 01-05-2020 15:10:55 : Fermeture de l'application 
// 01-05-2020 16:39:31 : Ouverture de l'application 
//     01-05-2020 16:39:35 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//         01-05-2020 16:39:42 : Suppression du poste 1 - acteur - 1 - | comedie | gag | 
//         01-05-2020 16:39:42 : Suppression du poste 4 - mascotte_Mickey - 1 - | danse | sport | 
//         01-05-2020 16:39:42 : Suppression de l'entreprise 1 - Disney - 77700 - walt@disney.com
// 01-05-2020 16:40:34 : Fermeture de l'application 
// 01-05-2020 19:10:16 : Ouverture de l'application 
//     01-05-2020 19:10:20 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//         01-05-2020 19:11:55 : Création du poste 5 - artificier - 1 - | diplome_artificier | EtÇaFaitBimBamBoum | 
//     01-05-2020 19:12:17 : Déconnexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
// 01-05-2020 19:13:56 : Fermeture de l'application 
// 01-05-2020 19:22:39 : Ouverture de l'application 
//     01-05-2020 19:22:44 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//         01-05-2020 19:22:47 : Disney a consulté sa liste des postes à pourvoir
//     01-05-2020 19:23:17 : Déconnexion de l'entreprise 1 - Disney - 77700 - walt@disney.com 
// 01-05-2020 19:23:09 : Fermeture de l'application 
// 01-05-2020 19:32:00 : Ouverture de l'application 
//     01-05-2020 19:32:05 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//         01-05-2020 19:32:27 : Disney a fait une recherche par compétence (C++)
//     01-05-2020 19:33:17 : Déconnexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
// 01-05-2020 19:32:45 : Fermeture de l'application 
// 01-05-2020 19:37:52 : Ouverture de l'application 
//     01-05-2020 19:37:55 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//         01-05-2020 19:38:44 : Disney a fait une recherche par compétence et code postal (EtÇaFaitBimBamBoum, 77700)
//     01-05-2020 19:38:17 : Déconnexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
// 01-05-2020 19:38:56 : Fermeture de l'application 
// 01-05-2020 19:49:59 : Ouverture de l'application 
//     01-05-2020 19:50:11 : Connexion de l'entreprise 2 - Google - 75009 - emplois@google.com
//         01-05-2020 19:50:15 : Google a consulté sa liste des postes à pourvoir 
//     01-05-2020 19:50:19 : Déconnexion de l'entreprise 2 - Google - 75009 - emplois@google.com
//     01-05-2020 19:51:49 : Création de l'entreprise 6 - Youtube - 34841 - contactyoutube@gmail.com
//     01-05-2020 19:51:55 : Connexion de l'entreprise 6 - Youtube - 34841 - contactyoutube@gmail.com
//         01-05-2020 19:53:48 : Création du poste 5 - ResponsablePlacementDeProduits - 6 - | marketing | maitriseBureautique | commercial | 
//         01-05-2020 19:54:11 : Youtube a consulté sa liste des postes à pourvoir 
//         01-05-2020 19:54:38 : Youtube a fait une recherche par compétence (marketing)
//         01-05-2020 19:55:11 : Youtube a fait une recherche par compétence et code postal (commercial, 34841)
//     01-05-2020 19:55:28 : Déconnexion de l'entreprise 6 - Youtube - 34841 - contactyoutube@gmail.com
//     01-05-2020 19:55:36 : Connexion de l'entreprise 5 - Doowap - 42754 - bonnebrioche@doowap.com
//         01-05-2020 19:55:42 : Doowap a consulté sa liste des postes à pourvoir 
//     01-05-2020 19:56:03 : Déconnexion de l'entreprise 5 - Doowap - 42754 - bonnebrioche@doowap.com
//     01-05-2020 19:56:17 : Connexion de l'entreprise 6 - Youtube - 34841 - contactyoutube@gmail.com
//         01-05-2020 19:58:11 : Création du poste 6 - Réalisateur - 6 - | Créatif | Sérieux | Passionné | 
//         01-05-2020 19:58:28 : Suppression du poste 6 - Réalisateur - 6 - | Créatif | Sérieux | Passionné | 
//         01-05-2020 19:58:38 : Suppression du poste 5 - ResponsablePlacementDeProduits - 6 - | marketing | maitriseBureautique | commercial | 
//         01-05-2020 19:58:38 : Suppression de l'entreprise 6 - Youtube - 34841 - contactyoutube@gmail.com
//     01-05-2020 19:58:50 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//         01-05-2020 19:58:57 : Disney a consulté sa liste des postes à pourvoir 
//     01-05-2020 19:59:08 : Déconnexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
// 01-05-2020 19:59:14 : Fermeture de l'application 
// 01-05-2020 20:13:38 : Ouverture de l'application 
//     01-05-2020 20:13:42 : Connexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
//         01-05-2020 20:13:54 : Disney a consulté sa liste des postes à pourvoir 
//     01-05-2020 20:14:00 : Déconnexion de l'entreprise 1 - Disney - 77700 - walt@disney.com
// 01-05-2020 20:14:00 : Fermeture de l'application 
