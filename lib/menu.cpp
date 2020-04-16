#include <iostream>
using namespace std ;

#include <regex>

#include "menu.h"
#include "entreprise.h"

int MenuPrincipal(groupeEntreprises *groupeEntr)
{
    char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
 
        do
        {
            system("clear") ;
            cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
            cout << "Vous êtes :" << endl ;
            cout << "1. Une entreprise" << endl ;            
            cout << "2. Un employé" << endl ;                           
            cout << "3. À la recherche d'un emploi" << endl << endl ;           
            cout << "q. Quitter l'application" << endl << endl ;        
            cout << "Votre choix : " ;
            cin >> choix ;
        } while ((choix > '3' || choix < '1') && choix != 'q');

        switch (choix)
        {
        case '1':
            return MenuEntreprise(groupeEntr) ;
            break;
        case '2':
            return MenuEmploye(groupeEntr) ;
            break;
        case '3':
            return MenuChercheur(groupeEntr) ;
            break;
        case 'q':
            return 0 ;
            break;
        default:
            break;
        }

    return 0 ;
}

int MenuEntreprise(groupeEntreprises *groupeEntr)
{
    char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
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

    switch (choix)
    {
    case '1':
        return SeConnecterEntreprise(groupeEntr) ;
        break;
    case '2':
        return CreerEntreprise(groupeEntr) ;
        break;
    case 'm':
        return MenuPrincipal(groupeEntr) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int MenuChercheur(groupeEntreprises *groupeEntr)
{
    char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
    do
    {
        system("clear") ;
        cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Créer votre profil" << endl ;            
        cout << "2. Modifier votre profil" << endl ;
        cout << "3. Supprimer votre profil" << endl ;                            
        cout << "4. Mettre à jour votre statut (passer employé) !!!! ça je crois que c'est pas un menu, ça se fait automatiquement quand une entreprise l'embauche" << endl ;
        cout << "5. Chercher un emploi grâce à vos collègues" << endl << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while ((choix > '5' || choix < '1') && choix != 'q' && choix != 'm');

    switch (choix)
    {
    case '1':
        return A_Implementer(groupeEntr) ;
        break;
    case '2':
        return A_Implementer(groupeEntr) ;
        break;
    case '3':
        return A_Implementer(groupeEntr) ;
        break;
    case '4':
        return A_Implementer(groupeEntr) ;
        break;
    case '5':
        return A_Implementer(groupeEntr) ;
        break;
    case 'm':
        return MenuPrincipal(groupeEntr) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int MenuEmploye(groupeEntreprises *groupeEntr)
{
    char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
    do
    {
        system("clear") ;
        cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Créer votre profil" << endl ;            
        cout << "2. Modifier votre profil" << endl ;
        cout << "3. Supprimer votre profil" << endl ;                            
        cout << "4. Mettre à jour votre statut (passer en recherche d'emploi) !!!! ça je crois que c'est pas un menu, ça se fait automatiquement quand une entreprise le vire" << endl ;
        cout << "5. Chercher un emploi qui correspond à votre profil" << endl ;
        cout << "6. Chercher un emploi grâce à vos collègues" << endl << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while ((choix > '6' || choix < '1') && choix != 'q' && choix != 'm');

    switch (choix)
    {
    case '1':
        return A_Implementer(groupeEntr) ;
        break;
    case '2':
        return A_Implementer(groupeEntr) ;
        break;
    case '3':
        return A_Implementer(groupeEntr) ;
        break;
    case '4':
        return A_Implementer(groupeEntr) ;
        break;
    case '5':
        return A_Implementer(groupeEntr) ;
        break;
    case '6':
        return A_Implementer(groupeEntr) ;
        break;
    case 'm':
        return MenuPrincipal(groupeEntr) ;
        break;
    case 'q':
        return 0;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int A_Implementer(groupeEntreprises *groupeEntr)
{
    char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
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
        return MenuPrincipal(groupeEntr) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int SeConnecterEntreprise(groupeEntreprises *groupeEntr)
{  

    int taille(0) ; // Contient la taille du groupe entreprise
    taille = gEntreprise_size(groupeEntr) ;
    char choixID(0) ;   // Contient l'id choisi par l'utilisateur
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
        cout << "Sélectionnez votre id :" << endl ;
        AfficherEntreprises(groupeEntr) ;
        cout << endl << "r. Retourner à la page précédente" << endl ;    
        cout << "m. Menu principal" << endl ;                   
        cout << "q. Quitter l'application" << endl << endl ; 
        cout << "Votre choix : " ;
        cin >> choixID ;
    } while ((choixID > taille + 48 || choixID < '1') && choixID != 'q' && choixID != 'm' && choixID != 'r');  

    switch (choixID)
    {
    case 'm':
        return MenuPrincipal(groupeEntr) ;
        break;
    case 'q':
        return 0 ;
        break;
    case 'r':
        return MenuEntreprise(groupeEntr) ;
        break;
    
    default:
        break;
    }

    cout << "choix : " << choixID ;  
    cout << "taille :" << taille ;
    cout << "coucou" << endl ;

    return 0;
}

int CreerEntreprise(groupeEntreprises *groupeEntr)
{
    char nom[40];
    char code_postal[10] ;
    char courriel[128];
    char choix(0) ;

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
        cout << "Code Postal : " ;
        cin >> code_postal ;
        if(!regex_match(code_postal, regex("[\\d]{1,5}"))) cout << "Merci de renseigner un code postal valide." << endl ;
    } while (!regex_match(code_postal, regex("[\\d]{1,5}"))); // Format code postal : chiffres uniquement (jusqu'a 5)
    
    do
    {
        cout << "Adresse mail : " ;
        cin >> courriel ;
        if(!regex_match(courriel, regex("[\\w._%+-]{1,20}@[\\w._]{2,20}.[A-Za-z]{2,3}"))) cout << "Merci de renseigner une adresse mail valide." << endl ;
    } while (!regex_match(courriel, regex("[\\w._%+-]{1,20}@[\\w._]{2,20}.[A-Za-z]{2,3}"))); // Format d'une adresse mail

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
    
    switch (choix)
        {
        case 'o':
            AjoutEntreprise(groupeEntr, nom, code_postal, courriel) ;
            return MenuEntreprise(groupeEntr) ;
            break;
        case 'n':
            return MenuEntreprise(groupeEntr) ;
            break;
        default:
            break;
        }
        

  

    return 0 ;
}

