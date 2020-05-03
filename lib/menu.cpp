#include <iostream>
using namespace std ;
#include <regex>
#include <string>

#include "menu.h"
#include "entreprise.h"
#include "employe.h"
#include "postes.h"
#include "groupe.h"
#include "journal.h"

// Remarque : Dans chaque menu, choix est un char pour sécuriser la saisie (permet de détecter si l'utilisateur entre une lettre au lieu d'un chiffre)

// But : Affiche le menu principal permettant de s'identifier en tant qu'entreprise ou utisateur
int MenuPrincipal(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    char choix(0) ;
 
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
        cin >> choix ;
    } while ((choix > '2' || choix < '1') && choix != 'q');

    // Deuxième étape : On affiche le menu demandé par l'utilisateur
    switch (choix)
    {
    case '1':
        return MenuEntreprise(gE, gP, gPe) ;
        break;
    case '2':
        return MenuPersonne(gE, gP, gPe) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;
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
    char choix(0) ;     
   
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
        cin >> choix ;
    } while ((choix > '2' || choix < '1') && choix != 'q' && choix != 'm');

    // Deuxième étape : On affiche le menu demandé par l'utilisateur
    switch (choix)
    {
    case '1':
        return MenuSeConnecterEntreprise(gE, gP, gPe) ;
        break;
    case '2':
        return MenuCreerEntreprise(gE, gP, gPe) ;
        break;
    case 'm':
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}

/* But : Affiche tous les index et nom des entreprises du groupe d'entreprise
        et demande à l'utilisateur d'entrer le numéro de son entreprise         */
int MenuSeConnecterEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{  
    // Contiendra l'index d'entreprise entré par l'utilisateur
    char choix(0) ;

    // Première étape : on affiche index et nom de toutes les entreprises du groupe d'entreprises
    //                  on vérifie sa saisie en vérifiant si l'entreprise demandée existe dans le groupe
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
        cin >> choix ;
    } while (!ExisteEntreprise(gE, choix - 48) && choix != 'q' && choix != 'm' && choix != 'r');

    // Deuxième étape : Si l'utilisateur veut finalement changer de menu, on l'oriente vers le bon
    switch (choix)
    {
    case 'm':
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        return 0 ;
        break;
    case 'r':
        return MenuEntreprise(gE, gP, gPe) ;
        break;
    
    default:
        break;
    }

    // Troisième étape : Si l'utilisateur a renseigné un index d'entreprise valide, on affiche le menu de cette entreprise
    journal_ConnexionEntreprise(g_indexEntreprise(gE, (int)choix - 48)) ;
    return MenuProfilEntreprise(gE, gP, gPe, (int)choix - 48) ;
    
    return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de créer le profil de son entreprise
int MenuCreerEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    char nom[40];
    int code_postal ;
    char courriel[128];
    char choix(0) ;

    // Première étape : l'utilisateur entre toutes les informations et on vérifie la saisie
    system("clear") ;
    cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
    do
    {
        cout << "Nom de l'entreprise (sans espaces) : " ;
        cin >> nom ;
        if(!regex_match(nom, regex("[a-zA-Zéèêëïîôö'_]{1,40}"))) cout << "Merci de renseigner un nom valide." << endl ;
    } while (!regex_match(nom, regex("[a-zA-Zéèêëïîôö'_]{1,40}"))); // Format nom entreprise : lettres uniquement (maximum 40)

    do
    {
        cout << "Code Postal (5 chiffres) : " ;
        cin >> code_postal ;
        if(code_postal > 99999 || code_postal < 0) cout << "Merci de renseigner un code postal valide." << endl ;
    } while (code_postal > 99999 || code_postal < 0); // Format code postal : 5 chiffruniquementes 
    
    do
    {
        cout << "Adresse mail : " ;
        cin >> courriel ;
        if(!regex_match(courriel, regex("[\\w._%+-]{1,20}@[\\w._]{2,20}.[A-Za-z]{2,3}"))) cout << "Merci de renseigner une adresse mail valide." << endl ;
    } while (!regex_match(courriel, regex("[\\w._%+-]{1,20}@[\\w._]{2,20}.[A-Za-z]{2,3}"))); // Format d'une adresse mail


    // Deuxième étape : on affiche un récapitulatif des informations saisies et on demande une validation
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
        cout << "Nom : " << nom << endl ;
        cout << "Code postal : " << code_postal << endl ;
        cout << "Adresse mail : " << courriel << endl << endl ; 
        cout << "Validez vous ces paramètres ?" << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        cin >> choix ; 
    } while ((choix != 'o' && choix != 'n')) ;
    
    // Troisième étape : Si l'utilisateur à validé, on ajoute son entreprise puis on revient au menu des entreprises
    //                   Si l'utilisateur n'a pas validé, on revient au menu des entreprises
    switch (choix)
        {
        case 'o':
            AjoutEntreprise(gE, nom, code_postal, courriel) ;
            return MenuEntreprise(gE, gP, gPe) ;
            break;
        case 'n':
            return MenuEntreprise(gE, gP, gPe) ;
            break;
        default:
            break;
        }
        
    return 0 ;
}

// But : Affiche le menu avec toutes les fonctionnalités d'une entreprise connectée 
int MenuProfilEntreprise(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    char choix(0) ;

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
        cin >> choix ;
    } while ((choix > '5' || choix < '1') && choix != 'q' && choix != 'm');

    // Deuxième étape : on affiche le menu demandé par l'utilisateur amenant à la fonctionnalité voulue
    switch (choix)
    {
    case '1':
        journal_EntrepriseConsultePostes(g_indexEntreprise(gE, indexE)) ;
        return MenuAfficherPostesDuneEntreprise(gE, gP, gPe, indexE) ;
        break;
    case '2':
        return MenuCreerPoste(gE, gP, gPe, indexE) ;
        break;
    case '3':
        return MenuSupprimerPoste(gE, gP, gPe, indexE) ;
        break;
    case '4':
        return MenuEntrepriseCherchePar(gE, gP, gPe, indexE) ;
        break;
    case '5':
        return MenuConfirmerSuppressionEntreprise(gE, gP, gPe, indexE) ;
        break;
    case 'm':
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;
}

// But : Affiche le menu demandant confirmation à l'utilisateur avant de supprimer le profil de son entreprise
int MenuConfirmerSuppressionEntreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    char choix(0) ;

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
        cin >> choix ;
    } while (choix != 'o' && choix != 'n') ;

    // Etape 2 : Si l'utilisateur confirme on supprime tous les postes à pourvoir de son entreprise, puis on supprime l'entreprise, puis on revient au menu principal
    //           Si l'utilisateur se rétracte, on revient à la page précédente
    switch (choix)
    {
    case 'o':
        gP = SupprimerEntreprise_postes(gP, indexE) ;
        gE = SupprimerEntreprise(gE, indexE) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'n':
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    default:
        break;
    }

    return 0 ;
}

// But : Affiche le menu où l'utilisateur peut voir tous les postes à pourvoir de son entreprise
int MenuAfficherPostesDuneEntreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    char choix(0) ;

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
        cin >> choix ;
    } while (choix != 'q' && choix != 'm' && choix != 'r');

    // Deuxième étape : on affiche le menu demandé par l'utilisateur
    switch (choix)
    {
    case 'r':
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    case 'm':
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de créer un poste à pourvoir
int MenuCreerPoste(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    char titre[128];
    char competence[5][128] = {'\0'} ;
    char choix(0) ;
    char choixComp(0) ;

    // Première étape : l'utilisateur entre toutes les informations et on vérifie la saisie
    system("clear") ;
    cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
    cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
    do
    {
        cout << "Intitulé du poste (sans espaces) : " ;
        cin >> titre ;
        if(!regex_match(titre, regex("[a-zA-Zéèêëïîôö'_]{1,128}"))) cout << "Merci de renseigner un intitulé valide." << endl ;
    } while (!regex_match(titre, regex("[a-zA-Zéèêëïîôö'_]{1,128}"))); // Format intitulé : lettres uniquement (maximum 128)

    // A chaque compétence saisie, on demande à l'utilisateur s'il souhaite rajouter une compétence (5 maximum)
    int compteur(1) ;
    int stop(0) ;
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Compétence n°" << compteur << " (sans espaces) : " ;
        cin >> competence[compteur-1] ;
        choixComp = 0 ;
        if(compteur < 5)
        {
            do
            {   
                cout << endl << "Voulez vous ajouter une autre compétence ?" << endl ;
                cout << "o. OUI" << endl ;
                cout << "n. NON" << endl ;
                cout << "Votre choix : " ;
                cin >> choixComp ;
            } while (choixComp != 'o' && choixComp != 'n');
            if (choixComp == 'n') stop = 1 ;
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
        cout << "Titre : " << titre << endl ;
        for (int i = 0; i < 5; i++)
        {
            if(competence[i][0] != '\0')
            {
                cout << "Compétence n°" << i+1 << " : " << competence[i] << endl ;
            }
        }
        cout << endl << "Validez vous ces paramètres ?" << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        cin >> choix ; 
    } while ((choix != 'o' && choix != 'n')) ;
    
    // Troisième étape : Si l'utilisateur à validé, on ajoute son poste puis on revient à la page précédente
    //                   Si l'utilisateur n'a pas validé, on revient à la page précédente
    switch (choix)
        {
        case 'o':
            AjoutPoste(gP, titre, indexE, competence) ;
            return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
            break;
        case 'n':
            return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
            break;
        default:
            break;
        }
        
    return 0 ;
}

// But : Affiche tous les postes à pourvoir de l'entreprise connectée et demande à l'utilisateur l'index du poste à supprimer
int MenuSupprimerPoste(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    char choix(0) ;

    // Première étape : on affiche tous les postes de l'entreprise et on demande à l'utilisateur l'index du poste à supprimer
    //                  pour vérifier la saisie, on regarde si le poste existe
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Les postes à pourvoir dans votre entreprise : " << endl ;
        AfficherPostesEntreprise(gE, gP, indexE) ;
        cout << endl << "Entrez le numéro du poste que vous voulez supprimer ou r pour revenir à la page précédente : " ;
        cin >> choix ;
    } while (!ExistePosteEntreprise(gP, choix - 48, indexE) && choix != 'r');

    // Deuxième étape : si l'utilisateur entre un numéro, on supprime le poste concerné et on retourne à la page précédente
    //                  si l'utilisateur ne veut plus supprimer de poste, on retourne à la page précédente
    switch (choix)
    {
    case 'r':
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    default:
        gP = SupprimerPoste(gP, choix - 48) ;
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    }

    return 0 ;
}

// But : Affiche le menu permettant à une entreprise de chercher un chercheur d'emploi par compétence ou compétence et code postal
int MenuEntrepriseCherchePar(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexE)
{
    char choix(0) ;
    char competence[128] ;
    int code_postal ;

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
        cin >> choix ;
    } while ((choix > '2' || choix < '1') && choix != 'r' && choix != 'q' && choix != 'm');

    // Deuxième étape : on affiche le menu correspondant à la recherche demandé
    switch (choix)
    {
    case '1':
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Saisissez la compétence que vous recherchez : "  ;
        cin >> competence ;
        journal_EntrepriseRechercheCompetence(g_indexEntreprise(gE, indexE), competence) ;
        EntrepriseRechercheParCompetence(gPe, competence) ;
        cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
        cin >> choix ;
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    case '2':
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gE, indexE)->nom << endl << endl ;
        cout << "Saisissez la compétence que vous recherchez : "  ;
        cin >> competence ;
        cout << "Saisissez le code postal que vous recherchez : "  ;
        cin >> code_postal ;
        journal_EntrepriseRechercheCompetenceEtCode(g_indexEntreprise(gE, indexE), competence, code_postal) ;
        EntrepriseRechercheParCompetenceEtCode(gPe, competence, code_postal) ;
        cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
        cin >> choix ;
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    
    case 'r':
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    case 'm':
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;
}





/* ============================================================================================================
||
||                                  PARTIE PERSONNE 
||
   ============================================================================================================ */

// But : Menu pour permettre à un utilisateur de s'identifier 
int MenuPersonne(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    
    char choix(0) ;     
   
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
        cin >> choix ;
    } while ((choix > '2' || choix < '1') && choix != 'q' && choix != 'm');

    // Deuxième étape : On affiche le menu demandé par l'utilisateur
    switch (choix)
    {
    case '1':
        return MenuSeConnecterPersonne(gE,gP,gPe); 
        break;
    case '2':
        return MenuCreerProfil(gE, gP, gPe) ;
        break;
    case 'm':
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;

}

/* But : Affiche tous les index et nom des personnes du groupe de personnes
        et demande à l'utilisateur d'entrer le numéro de son profil         */
int MenuSeConnecterPersonne(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{  
    // Contiendra l'index de personne entré par l'utilisateur
    char choix(0) ;

    // Première étape : on affiche index et nom de toutes les personnes du groupe de personnes
    //                  on vérifie sa saisie en vérifiant si la personne demandée existe dans le groupe
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
        cin >> choix ;
    } while (!ExistePersonne(gPe, choix - 48) && choix != 'q' && choix != 'm' && choix != 'r');

    // Deuxième étape : Si l'utilisateur veut finalement changer de menu, on l'oriente vers le bon
    switch (choix)
    {
    case 'm':
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        return 0 ;
        break;
    case 'r':
        return MenuPersonne(gE, gP, gPe) ;
        break;
    
    default:
        break;
    }

    // Troisième étape : Si l'utilisateur a renseigné un index de personne valide, on affiche le menu de cette personne
    journal_ConnexionPersonne(g_index(gPe, (int)choix - 48)) ;
    return MenuProfilPersonne(gE, gP, gPe, (int)choix - 48) ;
    
    return 0 ;
}

// But : Affiche le menu avec toutes les fonctionnalités d'une personne connectée 
int MenuProfilPersonne(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    char choix(0) ;
    int max = 3 ;

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
        cout << "3. Faire une recherche d'emploi ou de collègue" << endl ;
        if(statut != "Chercheur d'emploi")
        {
            cout << "4. Démissionner de l'entreprise : " << g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)->nom << endl << endl ;
            max = 4 ;
        }
        else cout << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while ((choix > max + 48 || choix < '1') && choix != 'q' && choix != 'm');

    // Deuxième étape : on affiche le menu demandé par l'utilisateur amenant à la fonctionnalité voulue
    switch (choix)
    {
    case '1':
        return MenuModifier_Profil(gE, gP, gPe, indexPe) ;
        break;
    case '2':
        return MenuConfirmerSuppressionPersonne(gE, gP, gPe, indexPe) ;
        break;
    case '3':
        return MenuPersonneCherchePar(gE, gP, gPe, indexPe) ;
        break;
    case '4':
        return MenuConfirmerQuitterEntreprise(gE, gP, gPe, indexPe) ;
        break;
    case 'm':
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de modifier son profil
int MenuModifier_Profil(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{

    char choix(0) ;

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
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 128; j++) cout << g_index(gPe, indexPe)->competence[i][j] ;
            if(g_index(gPe, indexPe)->competence[i][0] != '\0') cout << " | " ;
        }
        cout << endl ;
        cout << "Réseau de collègues :" ;
        int solitude = 1 ;
        for (int i = 1; i < MAX_AMIS; i++)
        {
            if (g_index(gPe, indexPe)->amis[i] != NULL)
            {
               cout << " | " << g_index(gPe, indexPe)->amis[i]->nom << " " << g_index(gPe, indexPe)->amis[i]->prenom ;
               solitude = 0 ;
            }
        }
        if(solitude == 1) cout << " aucun collègue enregistré dans votre réseau" << endl ;
        else cout << " |" ;
        cout << endl << endl;
        cout << "Vous voulez :" << endl ;
        cout << "1. Modifier votre code postal" << endl ;
        cout << "2. Modifier votre adresse mail" << endl ; 
        cout << "3. Ajouter une compétence" << endl ;                              
        cout << "4. Ajouter un collègue" << endl ;
        cout << "5. Supprimer un collègue" << endl ;
        cout << "6. Modifier votre entreprise" << endl << endl ;
        cout << "r. Retourner à la page précédente" << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while ((choix > '6' || choix < '1') && choix != 'q' && choix != 'm' && choix != 'r');

    switch (choix)
    {
    case '1':
        MenuPersonneMod_CodePostal(gE, gP, gPe,indexPe);
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        break;
    case '2':
        A_Implementer(gE, gP, gPe) ;
        break;
    case '3':
        MenuPersonneajouter_Competence(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        break;
    case '4':
        MenuPersonneAjouter_collegue(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        break;
    case '5':
        MenuPersonnesupprimer_collegue(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        break;
    case '6':
        MenuPersonne_mod_entreprise(gE, gP, gPe, indexPe) ;
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        break;
    case 'r':
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        break;
    case 'm':
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        break;
    default:
        break;
    }

    return 0 ;

}

// But : Affiche le menu demandant confirmation à l'utilisateur avant de supprimer son profil
int MenuConfirmerSuppressionPersonne(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    char choix(0) ;

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
        cin >> choix ;
    } while (choix != 'o' && choix != 'n') ;

    // Etape 2 : Si l'utilisateur confirme on supprime son profil, puis on revient au menu principal
    //           Si l'utilisateur se rétracte, on revient à la page précédente
    switch (choix)
    {
    case 'o':
        supprimer_profil(indexPe,gPe) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'n':
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
        break;
    default:
        break;
    }

    return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de créer son profil
int MenuCreerProfil(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    int adresse;
    char competence[5][128]={'\0'};
    int collegue[5]={-1,-1,-1,-1,-1};
    int entreprise;
    char choix(0) ;

    // Première étape : l'utilisateur entre toutes les informations et on vérifie la saisie
    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl << endl ;

    char *nom= new char(25);
    cout << "Saisir votre nom (Max 24 caractères): ";
    cin >> nom ;
    cout << endl ;

    char *prenom= new char(25);
    cout << "Saisir votre prénom (Max 24 caractères): ";
    cin >> prenom ;
    cout << endl ;

    char *courriel= new char(25);
    cout << "Saisir votre adresse mail (Max 24 caractères): ";
    cin >> courriel ;
    cout << endl ;

    cout << "Saisir votre code postal : ";
    cin >> adresse ;
    cout << endl ;

    AfficherEntreprises(gE);
    cout << "Ecrivez l'ID de votre entreprise (-1 si vous êtes en recherche d'emploi): " ;
    cin >> entreprise;
    cout << endl ;

    int i=0;
    char c;
    while(i < 5){
        cout << "Voulez vous ajouter une compétence (o ou n) ? ";
        cin >> c;
        if (c=='O' || c=='o'){
        cout << "Saisir une compétence : ";
        cin >> competence[i];
        i++;
        }
        else if (c=='N' || c=='n')i=5;
    }
    cout << endl ;

    AfficherPersonnes (gPe);
    i=0;
    c='N';
    while(i < 5){
        cout << "Voulez vous ajouter un collègue (o ou n) ?";
        cin >> c;
        if (c=='O' || c=='o'){
        cout << "Saisir l'id d'un de vos (anciens) collègues : ";
        cin >> collegue[i];
        i++;
        }
        else if (c=='N' || c=='n') i=5;
    }

    // Deuxième étape : on affiche un récapitulatif des informations saisies et on demande une validation
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl << endl ;
        cout << endl;
        cout << "Nom : " << nom << endl ;
        cout << "Prenom : " << prenom << endl ;
        cout << "Courriel : " << courriel << endl ;
        cout << "Code Postal : " << adresse << endl ;
        cout << "Entreprise : " << g_indexEntreprise(gE, entreprise)->nom <<endl << endl;
        cout << "Validez vous ces paramètres ?" << endl ;
        cout << "o. OUI" << endl ;
        cout << "n. NON" << endl ;
        cout << "Votre choix : " ;
        cin >> choix ; 
    } while ((choix != 'o' && choix != 'n')) ;
    
    // Troisième étape : Si l'utilisateur à validé, on ajoute son profil puis on revient au menu des personnes
    //                   Si l'utilisateur n'a pas validé, on revient au menu des personnes
    switch (choix)
        {
        case 'o':
            creer_profil(nom,prenom,courriel,adresse,competence,collegue,entreprise,gPe) ;
            return MenuPersonne(gE, gP, gPe) ;
            break;
        case 'n':
            return MenuPersonne(gE, gP, gPe) ;
            break;
        default:
            break;
        }
        
    return 0 ;
}

// But : Affiche le menu demandant confirmation à l'utilisateur avant d'actualiser son statut
int MenuConfirmerQuitterEntreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    char c(0);

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
        cout << "Voulez vous vraiment quitter votre entreprise (o ou n) ? " ;
        cin >> c;
    }while(c!='o' && c!='n');

    // On actualise ou pas son statut en fonction de sa réponse
    if (c=='o')
    {
      journal_QuitterEntreprise(g_index(gPe, indexPe), g_indexEntreprise(gE,g_index(gPe, indexPe)->entreprise)) ;
      quitter_entreprise(indexPe,gPe);
      return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
    } 
    else return MenuProfilPersonne(gE, gP, gPe, indexPe) ;

    return 0 ;
}

// But : Affiche le menu permettant à une personne de chercher un emploi ou un collègue
int MenuPersonneCherchePar(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    char choix(0) ;
    int a(0) ;
    char erreur[10] = "ERREUR" ;

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
        cin >> choix ;
    } while ((choix > '2' || choix < '1') && choix != 'r' && choix != 'q' && choix != 'm');

    // Deuxième étape : on lui demande encore de préciser quel type de recherche il veut faire
    switch (choix)
    {
    case '1':
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Vous voulez :" << endl ;
            cout << "1. Faire une recherche par compétence" << endl ; 
            cout << "2. Faire une recherche par compétence et code postal" << endl << endl ;
            cout << "r. Retourner sur votre profil" << endl ;
            cout << "m. Retourner au menu principal" << endl ;                       
            cout << "q. Quitter l'application" << endl << endl ;        
            cout << "Votre choix : " ;
            cin >> choix ;
        } while ((choix > '2' || choix < '1') && choix != 'r' && choix != 'q' && choix != 'm');

        // Troisième étape : on affiche le menu correspondant à la recherche demandé
        switch (choix)
        {
        case '1':
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Résultat de la recherche :" << endl ;
            a=recherche_poste_comp(indexPe,gPe,gP,gE);
            journal_PersonneRecherchePosteParCompetence(g_index(gPe, indexPe),erreur ) ;
            if(a==0) cout << "pas de poste avec cette competence" << endl;
            if(a==1) cout << "Au moins un poste avec cet competence" << endl;
            if(a==2) cout << "Problème d'indice non trouvé"<< endl;

            cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
            cin >> choix ;
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
            break;
        case '2':
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Résultat de la recherche :" << endl ;
            a=recherche_poste_postal(indexPe,gPe,gP,gE);
            journal_PersonneRecherchePosteParCompetenceEtCode(g_index(gPe, indexPe), erreur, -1 ) ;
            if(a==0) cout << "pas de poste à cette adresse" << endl;
            if(a==1) cout << "Au moins un poste à cette adresse" << endl;
            if(a==2) cout << "Problème d'indice non trouvé"<< endl;

            cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
            cin >> choix ;
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
            break;
        
        case 'r':
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ; ;
            break;
        case 'm':
            journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
            return MenuPrincipal(gE, gP, gPe) ;
            break;
        case 'q':
            journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
            return 0 ;
            break;
        default:
            break;
        }

        break;
    case '2':
        do
        {
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Profil de : " << g_index(gPe, indexPe)->nom << " " << g_index(gPe, indexPe)->prenom<< endl ;
            cout << "Statut : " << statut << endl << endl ;
            cout << "Vous voulez :" << endl ;
            cout << "1. Faire une recherche par entreprise" << endl ; 
            cout << "2. Faire une recherche par compétence" << endl << endl ;
            cout << "r. Retourner sur votre profil" << endl ;
            cout << "m. Retourner au menu principal" << endl ;                       
            cout << "q. Quitter l'application" << endl << endl ;        
            cout << "Votre choix : " ;
            cin >> choix ;
        } while ((choix > '2' || choix < '1') && choix != 'r' && choix != 'q' && choix != 'm');

        // Troisième étape : on affiche le menu correspondant à la recherche demandé
        switch (choix)
        {
        int col ;
        case '1':
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            AfficherEntreprises(gE);
            cout << endl << "Ecrivez le numéro de l'entreprise : ";
            cin >> col;
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Résultat de la recherche :" << endl ;
            a = recherche_col_par_entre(indexPe,gPe,col);
            journal_PersonneRechercheCollegueParEntreprise(g_index(gPe, indexPe), g_indexEntreprise(gE,col)) ;
            if(a==0) cout << "Pas de collègue dans cette entreprise" << endl;
            if(a==1) cout << "Au moins un de vos collègue travaille dans cette entreprise" << endl;
            if(a==2) cout << "Problème d'indice non trouvé"<< endl;

            cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
            cin >> choix ;
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
            break;
        case '2':
            char comp[128];
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Saisir la compétence recherchée : " ;
            cin >> comp;
            system("clear") ;
            cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
            cout << "Résultat de la recherche :" << endl ;
            a = recherche_col_comp(indexPe,gPe,comp);
            journal_PersonneRechercheCollegueParCompetence(g_index(gPe, indexPe), comp) ;
            if(a==0) cout << "Pas de collègue avec cette compétence" << endl;
            if(a==1) cout << "Au moins un de vos collègue possède cette compétence" << endl;
            if(a==2) cout << "Problème d'indice non trouvé"<< endl;

            cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
            cin >> choix ;
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ;
            break;
        
        case 'r':
            return MenuProfilPersonne(gE, gP, gPe, indexPe) ; ;
            break;
        case 'm':
            journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
            return MenuPrincipal(gE, gP, gPe) ;
            break;
        case 'q':
            journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
            return 0 ;
            break;
        default:
            break;
        }

        break;
    
    case 'r':
        return MenuProfilPersonne(gE, gP, gPe, indexPe) ; ;
        break;
    case 'm':
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        journal_DeconnexionPersonne(g_index(gPe, indexPe)) ;
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;
}

// But : Permet à une personne de modifier son code postal
int MenuPersonneMod_CodePostal(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    int newadr;

    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    cout << "Changement de votre code postal" << endl << endl ;

    cout << "Quel est votre nouveau code postal ? : " ;
    cin >> newadr;

    journal_PersonneMod_CodePostal(g_index(gPe, indexPe),g_index(gPe, indexPe)->adresse, newadr) ;
    modifier_adresse(indexPe,gPe,newadr);

    char choix(0) ;
    cout << "Opération effectuée avec succès" << endl;
    cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
    cin >> choix ;

    return 0;

}

// But : Permet à une personne de modifier son entreprise (si il change ou quitte son emploi)
int MenuPersonne_mod_entreprise(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    int newent;

    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    cout << "Changement de votre entreprise" << endl << endl ;

    AfficherEntreprises(gE);
    cout << "Saisir l'ID de votre nouvelle entreprise : " << endl;
    cin >> newent;
    cout << "Votre statut entreprise a été mise à jour" << endl;

    if(g_index(gPe, indexPe)->entreprise == -1 && newent == -1) ; // On ne fait rien
    else if(newent == -1) journal_Personne_mod_entreprise(g_index(gPe, indexPe), g_indexEntreprise(gE,g_index(gPe,indexPe)->entreprise), NULL) ;
    else journal_Personne_mod_entreprise(g_index(gPe, indexPe), g_indexEntreprise(gE,g_index(gPe,indexPe)->entreprise),g_indexEntreprise(gE,newent)) ;

    rejoindre_entreprise(indexPe,gPe,newent); //ou modifier entreprise ?

    char choix(0) ;
    cout << "Opération effectuée avec succès" << endl;
    cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
    cin >> choix ;

    return 0;
}

// But : Permet à une personne d'ajouter une compétence à son profil
int MenuPersonneajouter_Competence(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    char comp[128];

    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    cout << "Ajout d'une nouvelle compétence" << endl << endl ;
    cout << "Saisir votre nouvelle compétence : " ;
    cin >> comp;

    int a = ajouter_competence(indexPe,gPe,comp);

    if(a==1) cout << "Vous avez déjà cette compétence" << endl;
    if(a==2) cout << "Vous avez déjà le nombre maximal de compétences" << endl;
    if(a==3) cout << "Désolé, votre ID n'est pas répertorié" << endl;
    if(a==0) 
    {
        cout << "Opération effectuée avec succès" << endl;
        journal_Personneajouter_Competence(g_index(gPe, indexPe), comp) ;
    }
    char choix(0) ;
    cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
    cin >> choix ;

    return 0 ;
}

// But : Permet à une personne d'ajouter un collègue à son profil
int MenuPersonneAjouter_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    int col;

    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    cout << "Ajout d'un collègue au réseau" << endl << endl ;

    AfficherPersonnes(gPe);

    cout << endl << "Ecrivez l'ID correspondant au collègue à ajouter à votre réseau : " ;
    cin >> col;

    int a= ajouter_collegue(indexPe,gPe,col);

    if(a==1) cout << "Ce collègue fait déjà partie de votre réseau" << endl;
    if(a==2) cout << "Cette personne n'est pas dans la même entreprise que vous" << endl;
    if(a==3) cout << "Désolé, cet ID n'est pas répertorié" << endl;
    if(a==4) cout << "Désolé, vous avez atteint le nombre maximum de collègues" << endl;
    if(a==0) 
    {
        cout << "Operation effectué avec succès" << endl;
        journal_PersonneAjouter_Collegue(g_index(gPe, indexPe), g_index(gPe, col)) ;
    }

    char choix(0) ;
    cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
    cin >> choix ;

    return 0;

}

// But : Permet à une personne de supprimer un collègue de son profil
int MenuPersonnesupprimer_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int indexPe)
{
    int col;

    system("clear") ;
    cout << "* * * * * * * * * UTILISATEUR * * * * * * * * *" << endl ;
    cout << "Suppression d'un collègue du réseau" << endl << endl ;

    AfficherPersonnes(gPe);

    cout << endl << "Ecrivez l'ID correspondant au collègue à retirer de votre réseau : " ;
    cin >> col;

    int a= supprimer_collegue(indexPe,gPe,col);


    if(a==1) cout << "Désolé, cette personne ne fait pas partie de votre réseau" << endl;
    if(a==2) cout << "Désolé, cette identifiant n'est pas attribué" << endl;
    if(a==0)
    {
        cout << "Opération effectué avec succès" << endl;
        journal_PersonneSupprimer_Collegue(g_index(gPe, indexPe), g_index(gPe, col)) ;
    }

    char choix(0) ;
    cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
    cin >> choix ;

    return 0;

}






// But : Si une fonctionnalité présente dans le menu n'est pas encore implémentée
int A_Implementer(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe)
{
    char choix(0) ;    
   
    do
    {
        system("clear") ;
        cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
        cout << "Fonctionnalité non implémentée pour le moment:" << endl ;
        cout << "m. Retour au menu principal" << endl ;                     
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while (choix != 'm' && choix != 'q');

    switch (choix)
    {
    case 'm':
        return MenuPrincipal(gE, gP, gPe) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}




/* *****************************          CIMETIERRE          ******************************************************************* */
 

// int MenuChercheur(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int id)
// {


//     char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
//     do
//     {
//         system("clear") ;
//         cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
//         cout << "Vous voulez :" << endl ;         
//         cout << "1. Modifier votre profil" << endl ;
//         cout << "2. Supprimer votre profil" << endl ;                            
//         cout << "3. Mettre à jour votre statut (passer employé) !!!! ça je crois que c'est pas un menu, ça se fait automatiquement quand une entreprise l'embauche" << endl ;
//         cout << "4. Chercher un emploi grâce à vos collègues" << endl << endl ;
//         cout << "m. Retourner au menu principal" << endl ;                       
//         cout << "q. Quitter l'application" << endl << endl ;        
//         cout << "Votre choix : " ;
//         cin >> choix ;
//     } while ((choix > '5' || choix < '1') && choix != 'q' && choix != 'm');

//     switch (choix)
//     {
//     case '1':
//         MenuModifier_Profil(gE, gP, gPe,id) ;
//         break;
//     case '2':
//         Menusupprimer_profil(gE, gP, gPe,id) ;
//         break;
//    case '3':
//         Menu_emploi(gE, gP, gPe,id) ;
//         break;
//     case '4':
//         Menu_emploi_collegue(gE, gP, gPe,id) ;
//         break;
//     case 'm':
//         return MenuPrincipal(gE, gP, gPe) ;
//         break;
//     case 'q':
//         return 0 ;
//         break;
//     default:
//         break;
//     }

//     char c;
//     do{
//         cout << "Voulez vous rester connecté ou aller au menu principal (C ou P) ?" <<endl;
//         cin >> c;
//     }while(c!='C' && c!='P');

//    // if(c=='C') return CheckStatut(gE, gP, gPe, id);
//     if (c=='P') return MenuPrincipal(gE, gP, gPe);   

//     return 0;
// }

// int MenuEmploye(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe, int id)
// {
//     char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)

//     do
//     {
//         system("clear") ;
//         cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
//         cout << "Vous voulez :" << endl ;         
//         cout << "1. Modifier votre profil" << endl ;
//         cout << "2. Supprimer votre profil" << endl ;                            
//         cout << "3. Mettre à jour votre statut (passer en recherche d'emploi)" << endl ;
//         cout << "4. Chercher un emploi qui correspond à votre profil" << endl ;
//         cout << "5. Chercher un emploi grâce à vos collègues" << endl << endl ;
//         cout << "m. Retourner au menu principal" << endl ;                       
//         cout << "q. Quitter l'application" << endl << endl ;        
//         cout << "Votre choix : " ;
//         cin >> choix ;
//     } while ((choix > '6' || choix < '1') && choix != 'q' && choix != 'm');

//     switch (choix)
//     {
//     case '1':
//         MenuModifier_Profil(gE, gP, gPe,id) ;
//         break;
//     case '2':
//         Menusupprimer_profil(gE, gP, gPe, id) ;
//         break;
//     case '3':
//         Menuquitter_entreprise(gE, gP, gPe,id) ;
//         break;
//     case '4':
//         Menu_emploi(gE, gP, gPe,id) ;
//         break;
//     case '5':
//         Menu_emploi_collegue(gE, gP, gPe, id) ;
//         break;
//     case 'm':
//         return MenuPrincipal(gE, gP, gPe) ;
//         break;
//     case 'q':
//         return 0;
//         break;
//     default:
//         break;
//     }
    
//     char c;
//     do{
//         cout << "Voulez vous rester connecté ou aller au menu principal (C ou P) ?" <<endl;
//         cin >> c;
//     }while(c!='C' && c!='P');

// //    if(c=='C') return CheckStatut(gE, gP, gPe,id);
//     if (c=='P') return MenuPrincipal(gE, gP, gPe);   

//     return 0;
// }




// int CheckStatut(groupeEntreprises *gE, groupePostes *gP, groupePersonnes *gPe,int id){
//     node *temp = gPe->personnes;
//     personne*tmpami;
//     int trouve = 0;
//     while(temp != NULL && trouve ==0){
//         tmpami = (personne*)(temp->data);
//         if (tmpami->index == id){                               //Quand on atteint la personne souhaitée
//             if (tmpami->entreprise == -1) return MenuChercheur(gE,gP,gPe,id);   //Si la personne est sans emploi, menu sans emploi
//             else {
//                 return MenuEmploye(gE,gP,gPe,id);
//             }
//             trouve = 1;
//             }
//         else if (trouve == 0){
//             temp = temp->next;
//         }
//     }
//     if (trouve == 0){
//         cout << endl << "Cet identifiant n'est pas répertorié" << endl;
//     }
//     return 0;
// } 


// int Menu_emploi(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id){
    
//     int choix,a;

//     cout << "Vous voulez :" << endl; 
//     cout<< "(1) Chercher un poste selon par code postal "<<endl;
//     cout<< "(2) Chercher un poste selon vos compétences"<<endl;
//     cin >> choix ;

//     if(choix==1){
//         a=recherche_poste_postal(id,gPe,gP,gE);
        
//         if(a==0) cout << "pas de poste à cette adresse" << endl;
//         if(a==1) cout << "Au moins un poste à cette adresse" << endl;
//         if(a==2) cout << "Problème d'indice non trouvé"<< endl;

//     }
//     if(choix==2){
//         a=recherche_poste_comp(id,gPe,gP,gE);
        
//         if(a==0) cout << "pas de poste avec cette competence" << endl;
//         if(a==1) cout << "Au moins un poste avec cet competence" << endl;
//         if(a==2) cout << "Problème d'indice non trouvé"<< endl;
//     }
//     return 0;
// }

// int Menu_emploi_collegue(groupeEntreprises* gE, groupePostes *gP, groupePersonnes *gPe, int id){
//     int col,choix;

//     cout << "Vous voulez :" << endl; 
//     cout<< "(1) Chercher un collègue qui posséde une compétence spécifique "<<endl;
//     cout<< "(2) Chercher une entreprise dans laquel travail un collègue"<<endl;
//     cin >> choix ;

//     if (choix==1){
//         char comp[128];

//         cout << "Saisir la compétence recherché : " << endl;
//         cin >> comp;

//         int a = recherche_col_comp(id,gPe,comp);
//         if(a==0) cout << "pas de collégue avec cet compétence" << endl;
//         if(a==1) cout << "Au moins un de vos collègue posséde cette compétence" << endl;
//         if(a==2) cout << "Problème d'indice non trouvé"<< endl;
//     }

//     if (choix==2){
//         AfficherEntreprises(gE);

//         cout << endl << "Ecrivez l'ID correspondant à l'entreprise: " << endl;
//         cin >> col;

//         int a = recherche_col_par_entre(id,gPe,col);

//         if(a==0) cout << "pas de collégue dans cet entreprise" << endl;
//         if(a==1) cout << "Au moins un de vos collègue travaille dans cette entreprise" << endl;
//         if(a==2) cout << "Problème d'indice non trouvé"<< endl;
//     }   
    
//     return 0;
// }

