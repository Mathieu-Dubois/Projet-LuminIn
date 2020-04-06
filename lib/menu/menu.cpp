#include <iostream>
using namespace std ;

#include "menu.h"

void MenuPrincipal()
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
            MenuEntreprise() ;
            break;
        case '2':
            MenuEmploye() ;
            break;
        case '3':
            MenuChercheur() ;
            break;
        
        default:
            break;
        }

    return ;
}

void MenuEntreprise()
{
    char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
    do
    {
        system("clear") ;
        cout << " *** Bienvenue sur LuminIN, le site des pros ***" << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Créer le profil de votre entreprise" << endl ;            
        cout << "2. Supprimer le profil de votre entreprise" << endl ;
        cout << "3. Créer le profil d'un poste à pourvoir" << endl ;                            
        cout << "4. Supprimer le profil d'un poste maintenant pourvu" << endl ;
        cout << "5. Faire une recherche parmi les chercheurs d'emploi" << endl << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while ((choix > '5' || choix < '1') && choix != 'q' && choix != 'm');

    switch (choix)
    {
    case '1':
        A_Implementer() ;
        break;
    case '2':
        A_Implementer() ;
        break;
    case '3':
        A_Implementer() ;
        break;
    case '4':
        A_Implementer() ;
        break;
    case '5':
        A_Implementer() ;
        break;
    case 'm':
        MenuPrincipal() ;
        break;
    
    default:
        break;
    }
    
    return ;
}

void MenuChercheur()
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
        A_Implementer() ;
        break;
    case '2':
        A_Implementer() ;
        break;
    case '3':
        A_Implementer() ;
        break;
    case '4':
        A_Implementer() ;
        break;
    case '5':
        A_Implementer() ;
        break;
    case 'm':
        MenuPrincipal() ;
        break;
    
    default:
        break;
    }
    
    return ;
}

void MenuEmploye()
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
        A_Implementer() ;
        break;
    case '2':
        A_Implementer() ;
        break;
    case '3':
        A_Implementer() ;
        break;
    case '4':
        A_Implementer() ;
        break;
    case '5':
        A_Implementer() ;
        break;
    case '6':
        A_Implementer() ;
        break;
    case 'm':
        MenuPrincipal() ;
        break;
    
    default:
        break;
    }
    
    return ;
}





void A_Implementer()
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
        MenuPrincipal() ;
        break;
    
    default:
        break;
    }
    
    return ;
}