#include <iostream>
using namespace std ;
#include <fstream>
#include <string>

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
        entreprise << "5,Doowap,42754,bonnebrioche@doowap.com" << endl ;
        entreprise.close() ;
    }
    else cout << "ERREUR 1" << endl ;

    ofstream poste("tmp2.csv") ;
    if(poste)
    {
        poste << "id,titre,entreprise,competences" << endl ;
        poste << "1,acteur,1,comedie;gag" << endl ;
        poste << "2,developpeur,2,C;SQL;Python" << endl ;
        poste << "3,briocheur,5,patisserie" << endl ;
        poste << "4,mascotte_Mickey,1,danse;sport" << endl ;
        poste.close() ;
    }
    else cout << "ERREUR 2" << endl ;

    ofstream employes("tmp3.csv") ;
    if(employes)
    {
        employes << "id,nom,prenom,mail,code-postal,competences,collegues,entreprise" << endl ;
        employes << "1,Untel,Michel,m_untel@google.com,13010,C++;Python,,2" << endl ;
        employes << "2,Mouse,Mickey,mickey@mickeyville.gov,77700,comedie,3;5;6,1" << endl ;
        employes << "3,Mouse,Minnie,minnie@mickeyville.gov,77700,comedie;chant,2,1" << endl ;
        employes << "4,Brioche,Theo,theobrioche@doowap.fr,13400,patisserie,5,5" << endl ;
        employes << "5,Scott,Monon,monon@cristalclear.com,54879,chant;abdotransat,4;2,4" << endl ;
        employes << "6,Pas,Fred,cestquilui@invisible.com,54710,sieste,5,1" << endl ;
        employes << "7,Duck,Donald,donal.duck@canardville.gov,77700,comedie;gag,2,-1" << endl ;
        employes << "8,Pignon,Francois,pignouf@gmail.com,75020,C;SQL;Python,,-1" << endl ;
        employes << "9,Lourson,Winnie,winnielourson@potdemiel.com,15932,Anglais;Allemand;Latin;Cuisine;patisserie,2;3;4;5;6,1" ;
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
