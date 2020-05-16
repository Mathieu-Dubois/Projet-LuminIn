#include <iostream>
#include <regex>
#include <string>
using namespace std ;
#include "menu.h"




// But : Affiche le menu principal permettant de s'identifier en tant qu'entreprise ou utisateur
int MenuPrincipal(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|1|2{1}"} ; // On vérifie si l'utilisateur entre q, 1 ou 2
    string choix ;
 
    // Première étape : On demande à l'utilisateur ce qu'il souhaite faire et on vérifie sa saisie
    do
    {
        system("clear") ;
        cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
        cout << "Vous êtes :" << endl ;
        cout << "1. Une entreprise" << endl ;            
        cout << "2. Un utilisateur" << endl << endl ;                                    
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape : On affiche le menu demandé par l'utilisateur
    if(choix == "1") return MenuEntreprise(gE, gP, gPe) ;
    else if(choix == "2") return MenuPersonne(gE, gP, gPe) ;
    else return 0 ;
}

/* ============================================================================================================
||
||                                  PARTIE ENTREPRISE
||
   ============================================================================================================ */

/* But : Affiche le menu permettant à l'utilisateur de :
       - se connecter sur le profil de son entreprise
       - créer le profil de son entreprise               */
int MenuEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m|1|2{1}"} ; // On vérifie si l'utilisateur entre q, m, 1 ou 2
    string choix ;    
   
    // Première étape : On demande à l'utilisateur ce qu'il souhaite faire et on vérifie sa saisie
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
        cout << "1. Se connecter" << endl ; 
        cout << "2. Créer un compte " << endl << endl ;            
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape : On affiche le menu demandé par l'utilisateur
    if(choix == "1") return MenuSeConnecterEntreprise(gE, gP, gPe) ;
    else if(choix == "2") return MenuCreerEntreprise(gE, gP, gPe) ;
    else if(choix == "m") return MenuPrincipal(gE, gP, gPe) ;
    else return 0 ;
}

/* But : Affiche tous les index et nom des entreprises du groupe d'entreprise
et demande à l'utilisateur d'entrer le numéro de son entreprise */
int MenuSeConnecterEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{   
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"m|q|r{1}"} ; // On vérifie si l'utilisateur entre la lettre r, m ou q
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    string choix ;
    int choixE(0) ;

    // Première étape : on affiche index et nom de toutes les entreprises du groupe d'entreprises
    // on vérifie sa saisie en vérifiant si l'entreprise demandée existe dans le groupe
    do
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
            cout << "Sélectionnez votre id :" << endl ;
            AfficherEntreprises(gE) ;
            cout << endl << "r. Retourner à la page précédente" << endl ; 
            cout << "m. Menu principal" << endl ; 
            cout << "q. Quitter l'application" << endl << endl ; 
            cout << "Votre choix : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin,choix) ;
        } while (!regex_match(choix,patternNombre) && !regex_match(choix,patternMenu));
        // Deuxième étape :
        // Si l'utilisateur a saisie m, r ou q, on l'oriente au bon endroit
        if(choix == "m") return MenuPrincipal(gE, gP, gPe) ;
        else if(choix == "r") return MenuEntreprise(gE, gP, gPe) ; 
        else if(choix == "q") return 0 ;
        // Sinon on convertit le string en entier et on regarde si l'entreprise existe
        else choixE = stoi(choix) ;
    } while(!ExisteEntreprise(gE,choixE)) ;

    // Troisième étape : Si l'utilisateur a renseigné un index d'entreprise valide, on affiche le menu de cette entreprise
    journal_ConnexionEntreprise(g_indexEntreprise(gE, choixE)) ;
    return MenuProfilEntreprise(gE, gP, gPe, choixE) ;

    return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de créer le profil de son entreprise
int MenuCreerEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    regex patternNom {"[a-zA-Zéèêëïîôöàâäç'_ ]{1,40}"} ; // Un nom d'entreprise ne doit pas avoir de chiffres
    regex patternCodePostal {"[0-9]{5}"} ; // Un code postal doit contenir 5 chiffres
    regex patternMail {"[\\w\\._%+-]{1,30}@[\\w_]{2,20}\\.[A-Za-z]{2,3}"} ;
    string choix ;

    string nom ;
    string code ;
    string courriel ;
    
    // Première étape : l'utilisateur entre toutes les informations et on vérifie la saisie
    system("clear") ;
    cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
    do
    {
        cout << "\nNom de l'entreprise : " ;
        nom = "" ;
        cin.clear() ;
        getline(cin, nom) ;
        if(!regex_match(nom, patternNom)) cout << "Merci de renseigner un nom valide." << endl ;
    } while (!regex_match(nom, patternNom));

    do
    {
        cout << "\nCode Postal (5 chiffres) : " ;
        code = "" ;
        cin.clear() ;
        getline(cin, code) ;
        if(!regex_match(code, patternCodePostal)) cout << "Merci de renseigner un code postal valide." << endl ;
    } while (!regex_match(code, patternCodePostal));
    
    do
    {
        cout << "\nAdresse mail : " ;
        courriel = "" ;
        cin.clear() ;
        getline(cin, courriel) ;
        if(!regex_match(courriel, patternMail)) cout << "Merci de renseigner une adresse mail valide." << endl ;
    } while (!regex_match(courriel, patternMail));


    // Deuxième étape : on affiche un récapitulatif des informations saisies et on demande une validation
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
        cout << "Nom : " << nom << endl ;
        cout << "Code postal : " << code << endl ;
        cout << "Adresse mail : " << courriel << endl << endl ; 
        cout << "Validez vous ces paramètres ?" << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Troisième étape : Si l'utilisateur à validé, on ajoute son entreprise puis on revient au menu des entreprises
    //                   Si l'utilisateur n'a pas validé, on revient au menu des entreprises
    if(choix == "o")
    {
        // On est obligé de faire des conversions pour coller aux autre fonctions
        int code_postal = stoi(code) ;
        // Conversion string to char*
        size_t size = nom.size() + 1 ;
        char nomE[40] ;
        strncpy(nomE, nom.c_str(), size) ;
        size = courriel.size() + 1 ;
        char courrielE[128]; ;
        strncpy(courrielE, courriel.c_str(), size) ;

        AjoutEntreprise(gE, nomE, code_postal, courrielE) ;
        return MenuEntreprise(gE, gP, gPe) ;
    }
    else if(choix == "n") return MenuEntreprise(gE, gP, gPe) ;
    else return 0 ;

    return 0 ;
}

// But : Affiche le menu avec toutes les fonctionnalités d'une entreprise connectée 
int MenuProfilEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m|1|2|3|4|5{1}"} ; // On vérifie si l'utilisateur entre q, m, 1, 2, 3, 4 ou 5
    string choix ;

    // Première étape : on affiche toutes les fonctionnalités disponibles pour une entreprise connectée
    //                  et on demande à l'utilisateur d'en choisir une (on vérifie sa saisie)
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Consulter les postes à pourvoir de votre entreprise" << endl ; 
        cout << "2. Ajouter un poste à pourvoir" << endl ;
        cout << "3. Supprimer un poste à pourvoir" << endl ;
        cout << "4. Faire une recherche parmi les chercheurs d'emploi" << endl ;
        cout << "5. Supprimer le profil de votre entreprise" << endl << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape : on affiche le menu demandé par l'utilisateur amenant à la fonctionnalité voulue
    if(choix == "1")
    {
        journal_EntrepriseConsultePostes(g_indexEntreprise(gE, indexE)) ;
        return MenuAfficherPostesDuneEntreprise(gE, gP, gPe, indexE) ;
    }
    else if(choix == "2") return MenuCreerPoste(gE, gP, gPe, indexE) ;
    else if(choix == "3") return MenuSupprimerPoste(gE, gP, gPe, indexE) ;
    else if(choix == "4") return MenuEntrepriseCherchePar(gE, gP, gPe, indexE) ;
    else if(choix == "5") return MenuConfirmerSuppressionEntreprise(gE, gP, gPe, indexE) ;
    else if(choix == "m")
    {
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return MenuPrincipal(gE, gP, gPe) ;
    }
    else
    {
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return 0 ;
    }
}

// But : Affiche le menu demandant confirmation à l'utilisateur avant de supprimer le profil de son entreprise
int MenuConfirmerSuppressionEntreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    string choix ;

    // Première étape : on affiche les informations de l'entreprise et on demande confirmation avant de supprimer
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Suppression du profil : " <<
        g_indexEntreprise(gE, indexE)->nom << " - " <<
        g_indexEntreprise(gE, indexE)->code_postal << " - " <<
        g_indexEntreprise(gE, indexE)->courriel << endl << endl ; 
        cout << "Confirmez vous la suppression de ce profil ?" << endl <<
        "Toutes les annonces de postes à pourvoir par l'entreprise " << 
        g_indexEntreprise(gE, indexE)->nom <<
        " seront également supprimées." << endl << endl ;
        cout << "o. OUI" << endl ;                            
        cout << "n. NON" << endl << endl ;       
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Etape 2 : Si l'utilisateur confirme on supprime tous les postes à pourvoir de son entreprise, puis on supprime l'entreprise, puis on revient au menu principal
    //           Si l'utilisateur se rétracte, on revient à la page précédente
    if(choix == "o")
    {
        gP = SupprimerEntreprise_postes(gP, indexE) ;
        gPe = LicencierToutLeMonde(gPe,gE,indexE) ;
        gE = SupprimerEntreprise(gE, indexE) ;
        return MenuPrincipal(gE, gP, gPe) ;
    }
    else if(choix == "n") return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
    else return 0 ;
}

// But : Affiche le menu où l'utilisateur peut voir tous les postes à pourvoir de son entreprise
int MenuAfficherPostesDuneEntreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m|r{1}"} ; // On vérifie si l'utilisateur entre q, m ou r
    string choix ;

    // Première étape : on affiche tous les postes à pourvoir de cette entreprise jusqu'à ce que l'utilisateur décide de changer de menu
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Liste des postes à pourvoir dans votre entreprise :" << endl ;
        AfficherPostesEntreprise(gE, gP, indexE) ;
        cout << endl << "r. Retourner à la page précédente" << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape : on affiche le menu demandé par l'utilisateur
    if(choix == "r") return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
    else if(choix == "m")
    {
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return MenuPrincipal(gE, gP, gPe) ;
    }
    else
    {
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return 0 ;
    }
}

// But : Affiche le menu permettant à l'utilisateur de créer un poste à pourvoir
int MenuCreerPoste(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    regex patternTitre {"[a-zA-Z0-9éèêëïîôöàâäç'_ ]{1,100}"} ; 
    regex patternCompetence {"[a-zA-Zéèêëïîôöàâäç'_]{1,100}"} ;
    string choix ;
    string titre ;
    string competence ;

    char competencePoste[MAX_COMPETENCES][128] = {'\0'} ;

    // Première étape : l'utilisateur entre toutes les informations et on vérifie la saisie
    system("clear") ;
    cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
    cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl ;
    do
    {
        cout << "\nIntitulé du poste : " ;
        titre = "" ;
        cin.clear() ;
        getline(cin, titre) ;
        if(!regex_match(titre, patternTitre)) cout << "Merci de renseigner un intitulé de poste valide." << endl ;
    } while (!regex_match(titre, patternTitre)) ;

    // L'intitulé saisi est valide, on doit le convertir en char* pour s'adapter aux fonctions
    size_t size = titre.size() + 1 ;
    char titrePoste[128];
    strncpy(titrePoste, titre.c_str(), size) ;

    // A chaque compétence saisie, on demande à l'utilisateur s'il souhaite rajouter une compétence (5 maximum)
    int compteur(1) ;
    int stop(0) ;
    do
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
            cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
            cout << "Compétence n°" << compteur << " (sans espaces) : " ;
            competence = "" ;
            cin.clear() ;
            getline(cin, competence) ;
            if(!regex_match(competence, patternCompetence)) cout << "Merci de renseigner une competence valide." << endl ;
        } while(!regex_match(competence, patternCompetence)) ;
        
        // La compétence saisie est valide, on doit la convertir en char* pour s'adapter aux fonctions
        size = competence.size() + 1 ;
        strncpy(competencePoste[compteur-1], competence.c_str(), size) ;

        if(compteur < MAX_COMPETENCES)
        {
            do
            {   
                cout << endl << "\nVoulez vous ajouter une autre compétence ?" << endl ;
                cout << "o. OUI" << endl ;
                cout << "n. NON" << endl ;
                cout << "Votre choix : " ;
                choix = "" ;
                cin.clear() ;
                getline(cin, choix) ;
            } while (!regex_match(choix, patternMenu));
            if (choix == "n") stop = 1 ;
        }
        compteur++ ;
    } while (stop == 0 && compteur < 6);
    
    // Deuxième étape : on affiche un récapitulatif des informations saisies et on demande une validation
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Ajout du poste suivant : " << endl ;
        cout << "Titre : " << titrePoste << endl ;
        for (int i = 0; i < MAX_COMPETENCES; i++)
        {
            if(competencePoste[i][0] != '\0')
            {
                cout << "Compétence n°" << i+1 << " : " << competencePoste[i] << endl ;
            }
        }
        cout << endl << "Validez vous ces paramètres ?" << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin, choix) ;
    } while (!regex_match(choix, patternMenu));
    
    // Troisième étape : Si l'utilisateur à validé, on ajoute son poste puis on revient à la page précédente
    //                   Si l'utilisateur n'a pas validé, on revient à la page précédente
    if(choix == "o")
    {
        AjoutPoste(gP, titrePoste, indexE, competencePoste) ;
            return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
    }
    else return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        
    return 0 ;
}

// But : Affiche tous les postes à pourvoir de l'entreprise connectée et demande à l'utilisateur l'index du poste à supprimer
int MenuSupprimerPoste(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"r{1}"} ; // On vérifie si l'utilisateur entre r
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    string choix ;
    int choixP(0) ;

    // Première étape : on affiche tous les postes de l'entreprise et on demande à l'utilisateur l'index du poste à supprimer
    //                  pour vérifier la saisie, on regarde si le poste existe
    do
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
            cout << "Les postes à pourvoir dans votre entreprise : " << endl ;
            AfficherPostesEntreprise(gE, gP, indexE) ;
            cout << endl << "Entrez le numéro du poste que vous voulez supprimer ou r pour revenir à la page précédente : " ;
            cin.clear() ;
            getline(cin,choix) ;
        } while (!regex_match(choix,patternNombre) && !regex_match(choix,patternMenu)) ;
        // Deuxième étape :
        // Si l'utilisateur a saisie r on l'oriente au bon endroit
        if(choix == "r") return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        // Sinon on convertit le string en entier et on regarde si le poste existe
        else choixP = stoi(choix) ;
    } while(!ExistePosteEntreprise(gP, choixP, indexE)) ;
    
    // Quand le poste demandé est bien valide, on le supprime puis on revient au menu des entreprises
    gP = SupprimerPoste(gP, choixP) ;
    return MenuProfilEntreprise(gE, gP, gPe, indexE) ;

    return 0 ;
}

// But : Affiche le menu permettant à une entreprise de chercher un chercheur d'emploi par compétence ou compétence et code postal
int MenuEntrepriseCherchePar(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m|r|1|2{1}"} ; // On vérifie si l'utilisateur entre q, m, r, 1 ou 2
    regex patternCompetence {"[a-zA-Zéèêëïîôöàâäç'_]{1,100}"} ;
    regex patternCodePostal {"[0-9]{5}"} ; // Un code postal doit contenir 5 chiffres
    string choix ;

    // Première étape : on demande à l'utilisateur quelle type de recherche il veut faire
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Faire une recherche par compétence" << endl ; 
        cout << "2. Faire une recherche par compétence et code postal" << endl << endl ;
        cout << "r. Retourner à la page précédente" << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape : on affiche le menu correspondant à la recherche demandé
    if(choix == "1")
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
            cout << "Liste de tous les chercheurs d'emploi ayant une compétence que vous recherchez dans vos postes à pourvoir :" << endl << endl ;
            journal_EntrepriseRecherchePersonneParCompetence(g_indexEntreprise(gE,indexE)) ;
            EntrepriseRecherchePersonneParCompetence(gPe,gP,indexE) ;
            cout << endl ;
            cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while (choix != "p");
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
    }
    else if(choix == "2") 
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
            cout << "Liste de tous les chercheurs d'emploi avec la même adresse que vous" << endl;
            cout << "et ayant une compétence que vous recherchez dans vos postes à pourvoir :" << endl << endl ;
            journal_EntrepriseRecherchePersonneParCompetenceEtCode(g_indexEntreprise(gE,indexE)) ;
            EntrepriseRecherchePersonneParCompetenceEtCode(gPe,gP,g_indexEntreprise(gE,indexE)) ;
            cout << endl ;
            cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while (choix != "p");
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
    }
    else if(choix == "r") return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
    else if(choix == "m")
    {
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return MenuPrincipal(gE, gP, gPe) ;
    }
    else
    {
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return 0 ;
    }
}



/* ============================================================================================================
||
||                                  PARTIE PERSONNE 
||
   ============================================================================================================ */

// But : Menu pour permettre à un utilisateur de s'identifier 
int MenuPersonne(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m|1|2{1}"} ; // On vérifie si l'utilisateur entre q, m, 1, 2 ou 2
    string choix ;    
   
    // Première étape : On demande à l'utilisateur ce qu'il souhaite faire et on vérifie sa saisie
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl << endl ;
        cout << "1. Se connecter" << endl ; 
        cout << "2. Créer un compte " << endl << endl ;            
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape : On affiche le menu demandé par l'utilisateur
    if(choix == "1") return MenuSeConnecterPersonne(gE, gP, gPe) ;
    else if(choix == "2") return MenuCreerProfil(gE, gP, gPe) ;
    else if(choix == "m") return MenuPrincipal(gE, gP, gPe) ;
    else return 0 ;
}

/* But : Affiche tous les index et nom des personnes du groupe de personnes
        et demande à l'utilisateur d'entrer le numéro de son profil         */
int MenuSeConnecterPersonne(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{  
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"m|q|r{1}"} ; // On vérifie si l'utilisateur entre la lettre r, m ou q
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    string choix ;
    int choixPe(0) ;

    // Première étape : on affiche index et nom de toutes les personnes du groupe de personnes
    //                  on vérifie sa saisie en vérifiant si la personne demandée existe dans le groupe
    do
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl << endl ;
            cout << "Sélectionnez votre id :" << endl ;
            AfficherPersonnes(gPe) ;
            cout << endl << "r. Retourner à la page précédente" << endl ;    
            cout << "m. Menu principal" << endl ;                   
            cout << "q. Quitter l'application" << endl << endl ; 
            cout << "Votre choix : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin,choix) ;
        } while (!regex_match(choix,patternNombre) && !regex_match(choix,patternMenu));
        // Deuxième étape :
        // Si l'utilisateur a saisie m, r ou q, on l'oriente au bon endroit
        if(choix == "m") return MenuPrincipal(gE, gP, gPe) ;
        else if(choix == "r") return MenuPersonne(gE, gP, gPe) ; 
        else if(choix == "q") return 0 ;
        // Sinon on convertit le string en entier et on regarde si la personne existe
        else choixPe = stoi(choix) ;
    } while(!ExistePersonne(gPe, choixPe)) ;

    // Troisième étape : Si l'utilisateur a renseigné un index de personne valide, on affiche le menu de cette personne
    journal_ConnexionPersonne(g_index(gPe, choixPe)) ;
    return MenuProfilPersonne(gE, gP, gPe, choixPe) ;
    
    return 0 ;
}

// But : Affiche le menu avec toutes les fonctionnalités d'une personne connectée 
int MenuProfilPersonne(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m|1|2|3{1}"} ; // On vérifie si l'utilisateur entre q, m, 1, 2 ou 3
    string choix ;  

    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    // Première étape : on affiche toutes les fonctionnalités disponibles pour une personne connectée
    //                  et on demande à l'utilisateur d'en choisir une (on vérifie sa saisie)
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Modifier votre profil" << endl ;
        cout << "2. Supprimer votre profil" << endl ;
        cout << "3. Faire une recherche d'emploi ou de collègue" << endl << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape : on affiche le menu demandé par l'utilisateur amenant à la fonctionnalité voulue
    if(choix == "1") return MenuModifier_Profil(gE, gP, gPe, indexPe) ;
    else if(choix == "2") return MenuConfirmerSuppressionPersonne(gE, gP, gPe, indexPe) ;
    else if(choix == "3") return MenuPersonneCherchePar(gE, gP, gPe, indexPe) ;
    else if(choix == "m")
    {
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return MenuPrincipal(gE, gP, gPe) ;
    }
    else 
    {
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return 0 ;
    }
    return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de modifier son profil
int MenuModifier_Profil(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu1 {"q|m|r|1|2|3|4|5|6{1}"} ; // On vérifie si l'utilisateur entre q, m, r, 1, 2, 3, 4, 5 ou 6
    regex patternMenu2 {"q|m|r|1|2|3|4|5|6|7{1}"} ; // On vérifie si l'utilisateur entre q, m, r, 1, 2, 3, 4, 5, 6 ou 7
    string choix ;
    int max = 6 ;

    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }
   
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Résumé de votre profil :" << endl ;
        cout << "Code postal : " << g_index(gPe, indexPe)->adresse << endl ;
        cout << "Adresse mail : " << g_index(gPe, indexPe)->courriel << endl ;
        cout << "Compétences : | " ;
        for (int i = 0; i < MAX_COMPETENCES; i++)
        {
            for (int j = 0; j < 128; j++) cout << g_index(gPe, indexPe)->competence[i][j] ;
            if(g_index(gPe, indexPe)->competence[i][0] != '\0') cout << " | " ;
        }
        cout << endl ;
        cout << "Réseau de collègues :" ;
        int solitude = 1 ;
        for (int i = 0; i < MAX_AMIS; i++)
        {
            if (g_index(gPe, indexPe)->amis[i] != NULL)
            {
               cout << " | " << g_index(gPe, indexPe)->amis[i]->nom << " " << g_index(gPe, indexPe)->amis[i]->prenom ;
               solitude = 0 ;
            }
        }
        if(solitude == 1) cout << " Aucun collègue enregistré dans votre réseau" << endl ;
        else cout << " |" ;
        cout << endl << endl;
        cout << "Vous voulez :" << endl ;
        cout << "1. Modifier votre code postal" << endl ;
        cout << "2. Modifier votre adresse mail" << endl ; 
        cout << "3. Ajouter une compétence" << endl ;                              
        cout << "4. Ajouter un collègue" << endl ;
        cout << "5. Supprimer un collègue" << endl ;
        cout << "6. Modifier votre entreprise" << endl ;
        if(statut != "Chercheur d'emploi")
        {
            cout << "7. Démissionner de l'entreprise : " << g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom << endl << endl ;
            max = 7;
        }
        else cout << endl ;
        cout << "r. Retourner à la page précédente" << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin.clear() ;
        getline(cin,choix) ;
    } while ((!regex_match(choix,patternMenu1) && max == 6 ) || (!regex_match(choix,patternMenu2) && max == 7));

    // On affiche le menu demandé par l'utilisateur
    if(choix == "1")
    {
        MenuPersonneMod_CodePostal(gE, gP, gPe,indexPe);
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
    else if(choix == "2")
    {
        MenuPersonneMod_mail(gE, gP, gPe,indexPe);
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
    else if(choix == "3")
    {
        MenuPersonneajouter_Competence(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
    else if(choix == "4")
    {
        MenuPersonneAjouter_collegue(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
    else if(choix == "5")
    {
        MenuPersonnesupprimer_collegue(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
    else if(choix == "6")
    {
        MenuPersonne_mod_entreprise(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
    else if(choix == "7")
    {
        MenuConfirmerQuitterEntreprise(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    } 
    else if(choix == "r") return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    else if(choix == "m")
    {
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return MenuPrincipal(gE, gP, gPe) ;
    }
    else
    {
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return 0 ;
    }
}

// But : Affiche le menu demandant confirmation à l'utilisateur avant de supprimer son profil
int MenuConfirmerSuppressionPersonne(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    string choix ;

    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    // Première étape : on affiche les informations de la personne et on demande confirmation avant de supprimer
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Suppression du profil : " <<
        g_index(gPe, indexPe)->nom << " - " <<
        g_index(gPe, indexPe)->prenom << " - " <<
        g_index(gPe, indexPe)->adresse << " - " <<
        g_index(gPe, indexPe)->courriel << endl << endl ; 
        cout << "Confirmez vous la suppression de ce profil ?" << endl ;
        cout << "o. OUI" << endl ;                            
        cout << "n. NON" << endl << endl ;       
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Etape 2 : Si l'utilisateur confirme on supprime son profil, puis on revient au menu principal
    //           Si l'utilisateur se rétracte, on revient à la page précédente
    if(choix == "o")
    {
        supprimer_profil(indexPe,gPe) ;
        return MenuPrincipal(gE, gP, gPe) ;
    }
    else if(choix == "n") return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    else return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de créer son profil
int MenuCreerProfil(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    regex patternNom {"[A-Z]{1}[a-zA-Zéèêëïîôöàâäç' ]{1,24}"} ; // Un nom de personne commence par une majucule et peut en contenir (25 caractères max)
    regex patternPrenom {"[A-Z]{1}[a-zéèêëïîôöàâäç']{1,24}"} ; // Un prénom de personne commence par une majucule (25 caractères max)
    regex patternMail {"[\\w\\._%+-]{1,30}@[\\w_]{2,20}\\.[A-Za-z]{2,3}"} ;
    regex patternCodePostal {"[0-9]{5}"} ; // Un code postal doit contenir 5 chiffres
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    regex patternCompetence {"[a-zA-Zéèêëïîôöàâäç'_]{1,100}"} ;
    string choix ;

    string nom ;
    string prenom ;
    string code ;
    string courriel ;
    string entreprise ;
    string competence ;
    string collegue ;
    string competenceResume[MAX_COMPETENCES] ;
    for (int i = 0; i < MAX_COMPETENCES; i++)
    {
        competenceResume[i] = "" ;
    }
    
    char competencePe[MAX_COMPETENCES][128]={'\0'};
    int colleguePe[MAX_AMIS] ;
    for (int i = 0; i < MAX_AMIS; i++)
    {
        colleguePe[i] = -1 ;
    }
    
    int verifCollegue ;
    

    // Première étape : l'utilisateur entre toutes les informations et on vérifie la saisie
    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    do
    {
        cout << "\nSaisir votre nom : " ;
        nom = "" ;
        cin.clear() ;
        getline(cin, nom) ;
        if(!regex_match(nom, patternNom)) cout << "Merci de renseigner un nom valide." << endl ;
    } while (!regex_match(nom, patternNom));
    // Le nom saisie est valide, il faut le convertir en char* pour s'adapter aux autres fonctions
    size_t size = nom.size() + 1 ;
    char nomPe[30] ;
    strncpy(nomPe, nom.c_str(), size) ;

    do
    {
        cout << "\nSaisir votre prénom : " ;
        prenom = "" ;
        cin.clear() ;
        getline(cin, prenom) ;
        if(!regex_match(prenom, patternPrenom)) cout << "Merci de renseigner un nom valide." << endl ;
    } while (!regex_match(prenom, patternPrenom));
    // Le prenom saisie est valide, il faut le convertir en char* pour s'adapter aux autres fonctions
    size = prenom.size() + 1 ;
    char prenomPe[30] ;
    strncpy(prenomPe, prenom.c_str(), size) ;

    do
    {
        cout << "\nAdresse mail : " ;
        courriel = "" ;
        cin.clear() ;
        getline(cin, courriel) ;
        if(!regex_match(courriel, patternMail)) cout << "Merci de renseigner une adresse mail valide." << endl ;
    } while (!regex_match(courriel, patternMail));
    // L'adresse mail saisie est valide, il faut la convertir en char* pour s'adapter aux autres fonctions
    size = courriel.size() + 1 ;
    char courrielPe[128] ;
    strncpy(courrielPe, courriel.c_str(), size) ;

    do
    {
        cout << "\nCode Postal (5 chiffres) : " ;
        code = "" ;
        cin.clear() ;
        getline(cin, code) ;
        if(!regex_match(code, patternCodePostal)) cout << "Merci de renseigner un code postal valide." << endl ;
    } while (!regex_match(code, patternCodePostal));
    // Le code postal saisie est valide, on le convertit en int pour s'adapter aux autre fonctions
    int adresse ;
    adresse = stoi(code) ;
    
    int entreprisePe ;
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "\nEtes vous employé dans une entreprise ? " << endl ;
        cout << "o. OUI, je suis employé dans une entreprise" << endl ;
        cout << "n. NON, je suis en recherche d'emploi" << endl << endl ;
        cout << "Votre choix : " ;
        entreprise = "" ;
        cin.clear() ;
        getline(cin, entreprise) ;
    } while (!regex_match(entreprise, patternMenu));
    if(entreprise == "n") entreprisePe = -1 ;
    else
    {
        do
        {
            do
            {
                system("clear") ;
                cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                cout << "\nSaisir l'identifiant de votre entreprise : " << endl ;
                AfficherEntreprises(gE) ;
                cout << "Votre choix : " ;
                entreprise = "" ;
                cin.clear() ;
                getline(cin, entreprise) ;
            } while (!regex_match(entreprise, patternNombre));
            entreprisePe = stoi(entreprise) ;
        } while(!ExisteEntreprise(gE,entreprisePe)) ;
    }
    
    // A chaque compétence saisie, on demande à l'utilisateur s'il souhaite rajouter une compétence (5 maximum)
    int compteur(1) ;
    int stop(0) ;
    do
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
            cout << "Ajoutons au moins une compétence à votre profil" << endl ;
            cout << "Compétence n°" << compteur << " (sans espaces) : " ;
            competence = "" ;
            cin.clear() ;
            getline(cin, competence) ;
            if(!regex_match(competence, patternCompetence)) cout << "Merci de renseigner une competence valide." << endl ;
        } while(!regex_match(competence, patternCompetence)) ;
        
        // La compétence saisie est valide, on doit la convertir en char* pour s'adapter aux fonctions
        competenceResume[compteur-1] = competence ;
        size = competence.size() + 1 ;
        strncpy(competencePe[compteur-1], competence.c_str(), size) ;

        if(compteur < MAX_COMPETENCES)
        {
            do
            {   
                cout << endl << "\nVoulez vous ajouter une autre compétence ?" << endl ;
                cout << "o. OUI" << endl ;
                cout << "n. NON" << endl ;
                cout << "Votre choix : " ;
                choix = "" ;
                cin.clear() ;
                getline(cin, choix) ;
            } while (!regex_match(choix, patternMenu));
            if (choix == "n") stop = 1 ;
        }
        compteur++ ;
    } while (stop == 0 && compteur < 6);

    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "\nVouslez vous ajouter des personnes à votre réseau de collègues ? " << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl << endl ;
        cout << "Votre choix : " ;
        collegue = "" ;
        cin.clear() ;
        getline(cin, collegue) ;
    } while (!regex_match(collegue, patternMenu));
    if(collegue == "n") ;// Ne rien faire
    else
    {
         // A chaque collegue saisie, on demande à l'utilisateur s'il souhaite rajouter un collegue (5 maximum)
        compteur = 1 ;
        stop = 0 ;
        int dejaCollegue(0) ;
        do
        {
            do
            {
                if (dejaCollegue == 1)
                {
                    dejaCollegue = 0 ;
                    system("clear") ;
                    cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
                    cout << "Ce collègue appartient déjà à votre réseau." << endl ;
                    cout << "Appuyez sur n'importe quelle touche pour saisir un autre collègue :" ;
                    collegue = "" ;
                    cin.clear() ;
                    getline(cin, collegue) ;
                }
                
                do
                {
                    do
                    {
                        system("clear") ;
                        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
                        cout << "Saississez l'identifiant de votre collègue n°" << compteur << endl ;
                        AfficherPersonnes (gPe);
                        cout << endl << endl << "Votre choix : " ;
                        collegue = "" ;
                        cin.clear() ;
                        getline(cin, collegue) ;
                    } while(!regex_match(collegue, patternNombre)) ;
                    // Le nombre saisie est valide, on doit le convertir en int pour s'adapter aux fonctions
                    verifCollegue = stoi(collegue) ;
                } while(!ExistePersonne(gPe,verifCollegue)) ;
                // On vérifie si le collègue n'est pas déjà dans la liste des collègues
                for (int i = 0; i < MAX_AMIS; i++)
                {
                    if (colleguePe[i] == verifCollegue)
                    {
                        dejaCollegue = 1 ;
                    }  
                }
            } while(dejaCollegue == 1) ;
            // Le collègue saisie est enfin valide, on peut l'ajouter au réseau
            colleguePe[compteur-1] = verifCollegue ;

            if(compteur < MAX_AMIS)
            {
                do
                {   
                    cout << endl << "\nVoulez vous ajouter une autre collègue ?" << endl ;
                    cout << "o. OUI" << endl ;
                    cout << "n. NON" << endl ;
                    cout << "Votre choix : " ;
                    choix = "" ;
                    cin.clear() ;
                    getline(cin, choix) ;
                } while (!regex_match(choix, patternMenu));
                if (choix == "n") stop = 1 ;
            }
            compteur++ ;
        } while (stop == 0 && compteur < MAX_AMIS + 1);
    }


    // Deuxième étape : on affiche un récapitulatif des informations saisies et on demande une validation
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl << endl ;
        cout << endl;
        cout << "Nom : " << nomPe << endl ;
        cout << "Prenom : " << prenomPe << endl ;
        cout << "Courriel : " << courrielPe << endl ;
        cout << "Code Postal : " << adresse << endl ;
        if(entreprisePe == -1) cout << "Statut : En recherche d'emploi" << endl ;
        else cout << "Statut : Employé dans l'entreprise " << g_indexEntreprise(gE, entreprisePe)->nom << endl ;
        cout << "Compétences : " ;
        for (int i = 0; i < MAX_COMPETENCES; i++)
        {
            if (competenceResume[i] != "") cout << " | " << competenceResume[i] ;
              
        }
        cout << " |"<< endl ;
        cout << "Collègues : " ;
        for (int i = 0; i < MAX_AMIS; i++)
        {
            if (colleguePe[i] != -1)
            {
                cout << " | " << g_index(gPe, colleguePe[i])->nom << " " << g_index(gPe, colleguePe[i])->prenom ;
            }   
        }
        cout << " |" << endl << endl ;
         
        cout << "Validez vous ces paramètres ?" << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin, choix) ;
    } while (!regex_match(choix, patternMenu));
        
    // Troisième étape : Si l'utilisateur à validé, on ajoute son profil puis on revient au menu des personnes
    //                   Si l'utilisateur n'a pas validé, on revient au menu des personnes
    if(choix == "o")
    {
        creer_profil(nomPe,prenomPe,courrielPe,adresse,competencePe,colleguePe,entreprisePe,gPe) ;
        return MenuPersonne(gE, gP, gPe) ;
    }
    else return MenuPersonne(gE, gP, gPe) ;

    return 0 ;
}

// But : Affiche le menu demandant confirmation à l'utilisateur avant d'actualiser son statut
int MenuConfirmerQuitterEntreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    string choix ;

    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }
   
    // On lui demande confirmation avant d'actualiser son statut
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Voulez vous vraiment quitter votre entreprise ?" << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin, choix) ;
    } while (!regex_match(choix, patternMenu));

    // On actualise ou pas son statut en fonction de sa réponse
    if(choix == "o")
    {
        journal_QuitterEntreprise(g_index(gPe, indexPe), g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)) ;
        quitter_entreprise(indexPe,gPe);
    }
    return 0 ;
}

// But : Affiche le menu permettant à une personne de chercher un emploi ou un collègue
int MenuPersonneCherchePar(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m|r|1|2{1}"} ; // On vérifie si l'utilisateur entre q, m, r, 1 ou 2
    regex patternRecherche {"r|1|2{1}"} ; // On vérifie si l'utilisateur entre r, 1 ou 2
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    string choix ;
    int indexE(0) ;


    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    // Première étape : on demande à l'utilisateur quelle type de recherche il veut faire
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Faire une recherche parmi les postes à pourvoir" << endl ; 
        cout << "2. Faire une recherche parmi votre réseau de collègues" << endl << endl ;
        cout << "r. Retourner à la page précédente" << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    // Deuxième étape :
    // Si l'utilisateur a saisie m, r ou q, on l'oriente au bon endroit
    if(choix == "m")
    {
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return MenuPrincipal(gE, gP, gPe) ;
    } 
    else if(choix == "r") return MenuProfilPersonne(gE, gP, gPe, indexPe) ; 
    else if(choix == "q")
    {
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return 0 ;
    }

    // Si l'utilisateur à choisi 1 ou 2, on lui demande de préciser le type de recherche qu'il veut faire
    else if(choix == "1")
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Vous voulez :" << endl ;
            cout << "1. Faire une recherche par compétence" << endl ; 
            cout << "2. Faire une recherche par compétence et code postal" << endl << endl ;
            cout << "r. Retourner sur votre profil" << endl << endl;
            cout << "Votre choix : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin,choix) ;
        } while (!regex_match(choix,patternRecherche));
        
        // On oriente à nouveau l'utilisateur vers le bon endroit
        if(choix == "1")
        {
            do
            {
                system("clear") ;
                cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                cout << "Liste de tous les postes à pourvoir qui correspondent à vos compétences :" << endl << endl ;
                journal_PersonneRecherchePosteParCompetence(g_index(gPe,indexPe)) ;
                PersonneRecherchePosteParCompetence(g_index(gPe,indexPe), gP, gE) ;
                cout << endl ;
                cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                choix = "" ;
                cin.clear() ;
                getline(cin, choix) ;
            } while (choix != "p");
            
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        }
        else if(choix == "2")
        {
            do
            {
                system("clear") ;
                cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                cout << "Liste de tous les postes à pourvoir avec la même adresse que vous et qui correspondent à vos compétences :" << endl << endl ;
                journal_PersonneRecherchePosteParCompetenceEtCode(g_index(gPe,indexPe)) ;
                PersonneRecherchePosteParCompetenceEtCode(g_index(gPe,indexPe), gP, gE) ;
                cout << endl ;
                cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                choix = "" ;
                cin.clear() ;
                getline(cin, choix) ;
            } while (choix != "p");
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        }
        else return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
    else 
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Vous voulez :" << endl ;
            cout << "1. Faire une recherche par entreprise" << endl ; 
            cout << "2. Faire une recherche par compétence" << endl << endl ;
            cout << "r. Retourner sur votre profil" << endl << endl ;
            cout << "Votre choix : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin,choix) ;
        } while (!regex_match(choix,patternRecherche));

        // On oriente à nouveau l'utilisateur vers le bon endroit
        if(choix == "1")
        {
            do
            {
                do
                {
                    system("clear") ;
                    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                    cout << "Entrez l'index de l'entreprise dans laquelle vous voulez effectuer la recherche :" << endl ;
                    AfficherEntreprises(gE) ;
                    cout << endl ;
                    cout << "Votre choix : " ;
                    choix = "" ;
                    cin.clear() ;
                    getline(cin, choix) ;
                } while (!regex_match(choix,patternNombre));
                // Le nombre saisi est correct, on le convertit
                indexE = stoi(choix) ;
            } while(!ExisteEntreprise(gE, indexE)) ;
            do
            {
                system("clear") ;
                cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                cout << "Liste de tous vos collègues travaillant dans l'entreprise " << g_indexEntreprise(gE,indexE)->nom << " :" << endl << endl ;
                journal_PersonneRechercheCollegueParEntreprise(g_index(gPe,indexPe),g_indexEntreprise(gE,indexE)) ;
                PersonneRechercheCollegueParEntreprise(gPe, indexPe, indexE) ;
                cout << endl ;
                cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                choix = "" ;
                cin.clear() ;
                getline(cin, choix) ;
            } while (choix != "p");
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        }
        else if(choix == "2")
        {
            do
            {
                system("clear") ;
                cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                cout << "Liste de tous vos collègues travaillant dans une entreprise pouvant vous proposer un poste :" << endl << endl ;
                journal_PersonneRechercheCollegueParCompetence(g_index(gPe,indexPe)) ;
                PersonneRechercheCollegueParCompetence(g_index(gPe,indexPe), gE, gP) ;
                cout << endl ;
                cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                choix = "" ;
                cin.clear() ;
                getline(cin, choix) ;
            } while (choix != "p");
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        }
        else return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    }
     
    return 0 ;
    
}

// But : Permet à une personne de modifier son code postal
int MenuPersonneMod_CodePostal(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    regex patternCodePostal {"[0-9]{5}"} ; // Un code postal doit contenir 5 chiffres
    string choix ;
    string code ;

    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi (pour l'affichage)
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
    cout << "Statut : " << statut << endl << endl ;
    do
    {
        cout << "Code postal actuel : " << g_index(gPe, indexPe)->adresse << endl ;
        cout << "Entrez votre nouveau code postal : " ;
        code = "" ;
        cin.clear() ;
        getline(cin, code) ;
        if(!regex_match(code, patternCodePostal)) cout << "Merci de renseigner un code postal valide" << endl << endl ;
    } while (!regex_match(code, patternCodePostal));

    // Le nouveau code postal est valide, on demande confirmation
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Ancien code postal : " << g_index(gPe, indexPe)->adresse << endl ;
        cout << "Nouveau code postal : " << code << endl << endl ;
        cout << "Validez vous ce changement ? " << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin, choix) ;
    } while (!regex_match(choix, patternMenu));
    
    if(choix == "o")
    {
        int newadr = stoi(code) ;
        journal_PersonneMod_CodePostal(g_index(gPe, indexPe),g_index(gPe, indexPe)->adresse, newadr) ;
        modifier_adresse(indexPe,gPe,newadr) ;
    }

    return 0;
}

// But : Permet à une personne de modifier son adresse mail
int MenuPersonneMod_mail(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    regex patternMail {"[\\w\\._%+-]{1,30}@[\\w_]{2,20}\\.[A-Za-z]{2,3}"} ;
    string choix ;
    string mail ;

    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi (pour l'affichage)
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
    cout << "Statut : " << statut << endl << endl ;
    do
    {
        cout << "Adresse mail actuelle : " << g_index(gPe, indexPe)->courriel << endl ;
        cout << "Entrez votre nouvelle adresse mail : " ;
        mail = "" ;
        cin.clear() ;
        getline(cin, mail) ;
        if(!regex_match(mail, patternMail)) cout << "Merci de renseigner une adresse mail valide" << endl << endl ;
    } while (!regex_match(mail, patternMail));

    // La nouvelle adresse mail est valide, on demande confirmation
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Ancienne adresse mail : " << g_index(gPe, indexPe)->courriel << endl ;
        cout << "Nouvelle adresse mail : " << mail << endl << endl ;
        cout << "Validez vous ce changement ? " << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin, choix) ;
    } while (!regex_match(choix, patternMenu));
    
    if(choix == "o")
    {
        size_t size = mail.size() + 1 ;
        char newmail[128] ;
        strncpy(newmail, mail.c_str(), size) ;
        // Il faut faire l'entrée du journal correspondant à la modification d'adresse mail
        // journal_PersonneMod_CodePostal(g_index(gPe, indexPe),g_index(gPe, indexPe)->adresse, newadr) ;
        journal_Personne_modifier_mail(g_index(gPe, indexPe), g_index(gPe, indexPe)->courriel, newmail) ;
        modifier_mail(indexPe,gPe,newmail);
    }

    return 0;
    
}

// But : Permet à une personne de modifier son entreprise (si il change ou quitte son emploi)
int MenuPersonne_mod_entreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    string choix ;
    int newEntreprise ;

    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi (pour l'affichage)
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    do
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Merci de renseigner l'identifiant de votre nouvelle entreprise" << endl ;
            AfficherEntreprises(gE) ;
            choix = "" ;
            cin.clear() ;
            cout << "Votre choix : " ;
            getline(cin, choix) ;
        } while (!regex_match(choix, patternNombre));

        // Si le nombre saisie est correct, on vérifie qu'il correspond bien à l'id d'une entreprise
        newEntreprise = stoi(choix) ;
    } while(!ExisteEntreprise(gE,newEntreprise)) ;

    // On vérifie que la nouvelle entreprise n'est pas la même que l'ancienne entreprise
    if(newEntreprise == g_index(gPe, indexPe)->entreprise)
    {
        do 
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Vous êtes déjà employé dans l'entreprise " << g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom << endl << endl ;
            cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while( choix != "p") ;

        return 0 ;
    }

    // La nouvelle entreprise est valide, on demande confirmation
    else
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Nouvelle entreprise : " << g_indexEntreprise(gE,newEntreprise)->nom << endl << endl ;
            cout << "Validez vous ce changement ? " << endl ;
            cout << "o. OUI" << endl ;
            cout << "n. NON" << endl ;
            cout << "Votre choix : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while (!regex_match(choix, patternMenu));
        
        if(choix == "o")
        {
            journal_Personne_mod_entreprise(g_index(gPe, indexPe), g_indexEntreprise(gE,g_index(gPe,indexPe)->entreprise),g_indexEntreprise(gE,newEntreprise)) ;
            modifier_entreprise(indexPe,gPe,newEntreprise);
        }
    }
    
    return 0 ;

}

// But : Permet à une personne d'ajouter une compétence à son profil
int MenuPersonneajouter_Competence(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternCompetence {"[a-zA-Zéèêëïîôöàâäç'_]{1,100}"} ;
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    string choix ;
    string competence ;
    
    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi (pour l'affichage)
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    // On compte le nombre de compétence de cette personne
    // Si elle a déjà le nombre de compétence maximum, on lui dit
    int compteurDeCompetence(0) ;
    for (int i = 0; i < MAX_COMPETENCES; i++) if(g_index(gPe, indexPe)->competence[i][0] != '\0') compteurDeCompetence++ ;
    if(compteurDeCompetence == MAX_COMPETENCES)
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Votre profil compte déjà le nombre maximum de compétences. " << endl << endl ;
            cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while (choix != "p");
    }
    else
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Compétences : | " ;
        for (int i = 0; i < MAX_COMPETENCES; i++)
        {
            for (int j = 0; j < 128; j++) cout << g_index(gPe, indexPe)->competence[i][j] ;
            if(g_index(gPe, indexPe)->competence[i][0] != '\0') cout << " | " ;
        }
        cout << endl ;
        do
        {
            cout << "\nEntrez votre nouvelle compétence : " ;
            competence = "" ;
            cin.clear() ;
            getline(cin, competence) ;
        } while (!regex_match(competence, patternCompetence));

        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Compétence à ajouter : " << competence << endl << endl ;
            cout << "Validez vous ce changement ? " << endl ;
            cout << "o. OUI" << endl ;
            cout << "n. NON" << endl ;
            cout << "Votre choix : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while (!regex_match(choix, patternMenu));

        if (choix == "o")
        {
            // La compétence saisie est valide, on doit la convetir en char* pour s'adapter aux autres fonctions 
            size_t size = competence.size() + 1 ;
            char newCompetence[50] ;
            strncpy(newCompetence, competence.c_str(), size) ;

            int a = ajouter_competence(indexPe,gPe,newCompetence);

            if(a == 1)
            {
                do
                {
                    system("clear") ;
                    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                    cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
                    cout << "Statut : " << statut << endl << endl ;
                    cout << "Cette compétence est déjà dans votre liste de compétences. " << endl << endl ;
                    cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                    choix = "" ;
                    cin.clear() ;
                    getline(cin, choix) ;
                } while (choix != "p");
            }
            if(a == 0) journal_Personneajouter_Competence(g_index(gPe, indexPe), newCompetence) ;
        }
        
    }
    
    return 0 ;
}

// But : Permet à une personne d'ajouter un collègue à son profil
int MenuPersonneAjouter_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    string choix ;
    string collegue ;
    int idCollegue(0) ;
    
    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi (pour l'affichage)
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    // On compte le nombre d'amis de cette personne
    // Si elle a déjà le nombre d'amis maximum, on lui dit
    int compteurCollegue(0) ;
    for (int i = 0; i < MAX_AMIS; i++) if(g_index(gPe, indexPe)->amis[i] != NULL) compteurCollegue++ ;
    if(compteurCollegue == MAX_AMIS)
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Votre profil compte déjà le nombre maximum de collègues. " << endl << endl ;
            cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while (choix != "p");
    }
    else
    {
        do
        {
            do
            {
                system("clear") ;
                cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
                cout << "Statut : " << statut << endl << endl ;
                cout << "Réseau de collègues : " ;
                for (int i = 0; i < MAX_AMIS; i++)
                {
                    if (g_index(gPe, indexPe)->amis[i] != NULL)
                    {
                    cout << " | " << g_index(gPe, indexPe)->amis[i]->nom << " " << g_index(gPe, indexPe)->amis[i]->prenom ;
                    }
                }
                cout << endl ;
                cout << "\nEntrez l'identifiant de votre collègue : " << endl ;
                AfficherPersonnes(gPe);
                cout << endl << "Votre choix : " ;
                collegue = "" ;
                cin.clear() ;
                getline(cin, collegue) ;
            } while (!regex_match(collegue, patternNombre));
            idCollegue = stoi(collegue) ;
        } while(!ExistePersonne(gPe,idCollegue)) ;

        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Collègue à ajouter : " << g_index(gPe, idCollegue)->nom << " " << g_index(gPe, idCollegue)->prenom<< endl ;
            cout << "Validez vous ce changement ? " << endl ;
            cout << "o. OUI" << endl ;
            cout << "n. NON" << endl ;
            cout << "Votre choix : " ;
            choix = "" ;
            cin.clear() ;
            getline(cin, choix) ;
        } while (!regex_match(choix, patternMenu));

        if (choix == "o")
        {
            int a = ajouter_collegue(indexPe,gPe,idCollegue);

            if(a == 1)
            {
                do
                {
                    system("clear") ;
                    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                    cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
                    cout << "Statut : " << statut << endl << endl ;
                    cout << "Ce collègue est déjà dans votre réseau. " << endl << endl ;
                    cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                    choix = "" ;
                    cin.clear() ;
                    getline(cin, choix) ;
                } while (choix != "p");
            }
            if(a == 2)
            {
                do
                {
                    system("clear") ;
                    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                    cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
                    cout << "Statut : " << statut << endl << endl ;
                    cout << "Cette personne n'est pas dans la même entreprise que vous [A CORRIGER ?]" << endl << endl;
                    cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                    choix = "" ;
                    cin.clear() ;
                    getline(cin, choix) ;
                } while (choix != "p");
            }
            if(a == 5)
            {
                do
                {
                    system("clear") ;
                    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                    cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
                    cout << "Statut : " << statut << endl << endl ;
                    cout << "Vous ne pouvez pas vous ajouter vous même à votre réseau" << endl << endl;
                    cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                    choix = "" ;
                    cin.clear() ;
                    getline(cin, choix) ;
                } while (choix != "p");
            }
            

            if(a == 0) journal_PersonneAjouter_Collegue(g_index(gPe, indexPe), g_index(gPe, idCollegue)) ;
        }
        
    }
    
    return 0 ;

}

// But : Permet à une personne de supprimer un collègue de son profil
int MenuPersonnesupprimer_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternNombre {"[1-9]([0-9]*)"} ; // On vérifie si l'utilisateur entre un nombre < 0
    regex patternMenu {"o|n{1}"} ; // On vérifie si l'utilisateur entre o ou n
    string choix ;
    string collegue ;
    int idCollegue(0) ;
    
    // On commence par regarder si cette personne est un employé ou un chercheur d'emploi (pour l'affichage)
    std::string statut = "" ;
    if(g_index(gPe, indexPe)->entreprise == -1) statut = "Chercheur d'emploi" ;
    else
    {
        statut = "Employé chez " ;
        statut += g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom ;
    }

    do
    {
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Réseau de collègues : " ;
            for (int i = 0; i < MAX_AMIS; i++)
            {
                if (g_index(gPe, indexPe)->amis[i] != NULL)
                {
                cout << " | " << g_index(gPe, indexPe)->amis[i]->nom << " " << g_index(gPe, indexPe)->amis[i]->prenom ;
                }
            }
            cout << endl ;
            cout << "\nEntrez l'identifiant du collègue que vous voulez supprimer : " << endl ;
            AfficherAmis(gPe, indexPe);
            cout << endl << "Votre choix : " ;
            collegue = "" ;
            cin.clear() ;
            getline(cin, collegue) ;
        } while (!regex_match(collegue, patternNombre));
        idCollegue = stoi(collegue) ;
    } while(!ExistePersonne(gPe,idCollegue)) ;

    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
        cout << "Statut : " << statut << endl << endl ;
        cout << "Collègue à supprimer : " << g_index(gPe, idCollegue)->nom << " " << g_index(gPe, idCollegue)->prenom<< endl ;
        cout << "Validez vous ce changement ? " << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin, choix) ;
    } while (!regex_match(choix, patternMenu));

    if (choix == "o")
    {
        int a = supprimer_collegue(indexPe,gPe,idCollegue);

        if(a == 1)
        {
            do
            {
                system("clear") ;
                cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
                cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
                cout << "Statut : " << statut << endl << endl ;
                cout << "Cette personne ne fait pas partie de votre réseau. " << endl << endl ;
                cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
                choix = "" ;
                cin.clear() ;
                getline(cin, choix) ;
            } while (choix != "p");
        }
        if(a == 0) journal_PersonneSupprimer_Collegue(g_index(gPe, indexPe), g_index(gPe, idCollegue)) ;
    }

    return 0 ;
}






// But : Si une fonctionnalité présente dans le menu n'est pas encore implémentée
int A_Implementer(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    // Définitions des ER nécessaires à la saisie sécurisée
    regex patternMenu {"q|m{1}"} ; // On vérifie si l'utilisateur entre q ou m
    string choix ;
    do
    {
        system("clear") ;
        cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
        cout << "Fonctionnalité non implémentée pour le moment:" << endl ;
        cout << "m. Retour au menu principal" << endl ;                     
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        choix = "" ;
        cin.clear() ;
        getline(cin,choix) ;
    } while (!regex_match(choix,patternMenu));

    if(choix == "m") return MenuPrincipal(gE, gP, gPe) ;
    else return 0 ;
}


// do
// {
//     system("clear") ;
//     cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
//     cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
//     cout << "Statut : " << statut << endl << endl ;
//     cout << "Cette personne ne fait pas partie de votre réseau. " << endl << endl ;
//     cout << "Appuyez sur la touche \"p\" pour retourner sur votre profil : " ;
//     choix = "" ;
//     cin.clear() ;
//     getline(cin, choix) ;
// } while (choix != "p");