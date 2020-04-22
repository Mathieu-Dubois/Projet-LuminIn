#include <iostream>
using namespace std ;

#include <regex>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "menu.h"
#include "entreprise.h"
#include "postes.h"
#include "groupe.h"
#include "employe.h"

int MenuPrincipal(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne)
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
            return MenuEntreprise(gEntreprise, gPoste, gPersonne) ;
            break;
        case '2':
            return MenuEmploye(gEntreprise, gPoste, gPersonne) ;
            break;
        case '3':
            return MenuChercheur(gEntreprise, gPoste, gPersonne) ;
            break;
        case 'q':
            return 0 ;
            break;
        default:
            break;
        }

    return 0 ;
}

int MenuEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne)
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
        return SeConnecterEntreprise(gEntreprise, gPoste, gPersonne) ;
        break;
    case '2':
        return CreerEntreprise(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'm':
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int MenuChercheur(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne)
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
        return MenuCreer_Profil(gEntreprise, gPoste, gPersonne);
        break;
    case '2':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '3':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '4':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '5':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'm':
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int MenuEmploye(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne)
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
        return MenuCreer_Profil(gEntreprise, gPoste, gPersonne);
        break;
        
    case '2':
        return MenuModifier_Profil(gEntreprise, gPoste, gPersonne) ;
        break;
    case '3':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '4':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '5':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '6':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'm':
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int A_Implementer(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne)
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
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }
    
    return 0 ;
}

int SeConnecterEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne)
{  
    char choixID(0) ;   // Contient l'id choisi par l'utilisateur
    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl << endl ;
        cout << "Sélectionnez votre id :" << endl ;
        AfficherEntreprises(gEntreprise) ;
        cout << endl << "r. Retourner à la page précédente" << endl ;    
        cout << "m. Menu principal" << endl ;                   
        cout << "q. Quitter l'application" << endl << endl ; 
        cout << "Votre choix : " ;
        cin >> choixID ;
    } while (!ExisteEntreprise(gEntreprise, choixID - 48) && choixID != 'q' && choixID != 'm' && choixID != 'r');

    switch (choixID)
    {
    case 'm':
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0 ;
        break;
    case 'r':
        return MenuEntreprise(gEntreprise, gPoste, gPersonne) ;
        break;
    
    default:
        break;
    }


    return ProfilEntreprise(gEntreprise, gPoste, gPersonne, (int)choixID - 48) ;
    

    return 0;
}

int CreerEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne)
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
        cout << "Code Postal (5 chiffres) : " ;
        cin >> code_postal ;
        if(!regex_match(code_postal, regex("[\\d]{1,5}"))) cout << "Merci de renseigner un code postal valide." << endl ;
    } while (!regex_match(code_postal, regex("[\\d]{5}"))); // Format code postal : 5 chiffres uniquement
    
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
            AjoutEntreprise(gEntreprise, nom, code_postal, courriel) ;
            return MenuEntreprise(gEntreprise, gPoste, gPersonne) ;
            break;
        case 'n':
            return MenuEntreprise(gEntreprise, gPoste, gPersonne) ;
            break;
        default:
            break;
        }
        
    return 0 ;
}

int ProfilEntreprise(groupeEntreprises *gEntreprise, groupePostes *gPoste, groupe *gPersonne, int index)
{
    char choix(0) ;

    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gEntreprise, index)->nom << endl << endl ;
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

    switch (choix)
    {
    case '1':
        return ListeDesPostes(gEntreprise, gPoste, gPersonne, index) ;
        break;
    case '2':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '3':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '4':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '5':
        return ConfirmerSuppressionEntreprise(gEntreprise, gPoste, gPersonne, index) ;
        break;
    case 'm':
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;

}

int ConfirmerSuppressionEntreprise(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne, int index)
{
    char choix(0) ;

    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gEntreprise, index)->nom << endl << endl ;
        cout << "Suppression du profil : " <<
        g_indexEntreprise(gEntreprise, index)->nom << " - " <<
        g_indexEntreprise(gEntreprise, index)->code_postal << " - " <<
        g_indexEntreprise(gEntreprise, index)->courriel << endl << endl ; 
        cout << "Confirmez vous la suppression de ce profil ?" << endl <<
        "Toutes les annonces de postes à pourvoir par l'entreprise " << 
        g_indexEntreprise(gEntreprise, index)->nom <<
        " seront également supprimées." << endl << endl ;
        cout << "o. OUI" << endl ;                            
        cout << "n. NON" << endl << endl ;       
        cout << "Votre choix : " ;
        cin >> choix ;
    } while (choix != 'o' && choix != 'n') ;

    switch (choix)
    {
    case 'o':
        gEntreprise = SupprimerEntreprise(gEntreprise, index) ;
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'n':
        return ProfilEntreprise(gEntreprise, gPoste, gPersonne, index) ;
        break;
    default:
        break;
    }


    return 0 ;
}

int ListeDesPostes(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne, int index)
{
    char choix(0) ;

    do
    {
        system("clear") ;
        cout << "* * * * * * * * * ENTREPRISE * * * * * * * * *" << endl ;
        cout << "Profil de : " << g_indexEntreprise(gEntreprise, index)->nom << endl << endl ;
        cout << "Liste des postes à pourvoir dans votre entreprise :" << endl ;
        AfficherPostesEntreprise(gEntreprise, gPoste, index) ;
        cout << endl << "r. Retourner à la page précédente" << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while (choix != 'q' && choix != 'm' && choix != 'r');

    switch (choix)
    {
    case 'r':
        return ProfilEntreprise(gEntreprise, gPoste, gPersonne, index) ;
        break;
    case 'm':
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0 ;
        break;
    default:
        break;
    }

    return 0 ;
}

int MenuCreer_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){

    
    int adresse;
    char competence[5][128]={'\0'};
    int collegue[5]={-1,-1,-1,-1,-1};
    int entreprise;
        
    char *nom= new char(25);
    cout << "Saisir votre Nom (Max 24 caractères): ";
    cin >> nom ;
    

    char *prenom= new char(25);
    cout << "Saisir votre prenom (Max 24 caractères): ";
    cin >> prenom ;
    

    char *courriel= new char(25);
    cout << "Saisir votre email (Max 24 caractères): ";
    cin >> courriel ;
    

    cout << "Saisir votre code postal : ";
    cin >> adresse ;

    AfficherEntreprises(gEntreprise);
    cout << "Ecrivez l'ID de votre entreprise (-1 sinon): ";
    cin >> entreprise;
    
    int i=0;
    char c;
    while(i < 5){
        cout << "Voulez vous ajouter une compétence (O ou N) ?";
        cin >> c;
        if (c=='O' || c=='o'){
        cout << "Saisir une compétence : ";
        cin >> competence[i];
        i++;
        }
        else if (c=='N' || c=='n')i=5;
    }

    //print de la table employes
    if (gPersonne->personnes == NULL) cout << "Aucune personnes enregistrée" << endl ;
    else
    {
        node *tmp = gPersonne->personnes ;
        personne *e = (personne*)tmp->data ;
        while (e!= NULL && tmp != NULL)
        {
            // cout << e->index << " - " << e->nom << " - " << e->code_postal << " - " << e->courriel << endl ;
            cout << e->index << " - " << e->nom  << endl ;
            tmp = tmp->next ;
            if(tmp != NULL) e = (personne*)tmp->data ;
            
        }
    }

    i=0;
    c='N';
    while(i < 5){
        cout << "Voulez vous ajouter un collegue (O ou N) ?";
        cin >> c;
        if (c=='O' || c=='o'){
        cout << "Saisir l'id d'un de vos anciens collegues : ";
        cin >> collegue[i];
        i++;
        }
        else if (c=='N' || c=='n') i=5;
    }


    cout << endl;
    cout << "Recapitulatif" << endl;
    cout << "Nom : " << nom << endl ;
    cout << "Prenom : " << prenom << endl ;
    cout << "Courriel : " << courriel << endl ;
    cout << "Code Postal : " << adresse << endl ;
    cout << "ID entreprise :" << entreprise <<endl;

    creer_profil(nom,prenom,courriel,adresse,competence,collegue,entreprise,gPersonne);
    return 1;
}



int MenuModifier_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){

 char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
    do
    {
        system("clear") ;
        cout << " ** Vous souhaitez actuellement modifier votre profil **" << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Ajouter une compétence" << endl ;            
        cout << "2. Supprimer une compétence" << endl ;
        cout << "3. Changer d'adresse email" << endl ;                            
        cout << "4. Mettre à jour/changer d'entreprises" << endl ;
        cout << "5. Ajouter un collégue" << endl ;
        cout << "6. Supprimer un collégue" << endl << endl ;
        cout << "m. Retourner au menu principal" << endl ;                       
        cout << "q. Quitter l'application" << endl << endl ;        
        cout << "Votre choix : " ;
        cin >> choix ;
    } while ((choix > '6' || choix < '1') && choix != 'q' && choix != 'm');

    switch (choix)
    {
    case '1':
        return A_Implementer(gEntreprise, gPoste, gPersonne);
        break;
        
    case '2':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '3':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '4':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '5':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '6':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'm':
        return MenuPrincipal(gEntreprise, gPoste, gPersonne) ;
        break;
    case 'q':
        return 0;
        break;
    default:
        break;
    }
    
    return 0 ;

}