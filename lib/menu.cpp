#include <iostream>
using namespace std ;
#include <regex>

#include "menu.h"
#include "entreprise.h"
#include "employe.h"
#include "postes.h"
#include "groupe.h"

// Remarque : Dans chaque menu, choix est un char pour sécuriser la saisie (permet de détecter si l'utilisateur entre une lettre au lieu d'un chiffre)

// But : Affiche le menu principal permettant de s'identifier en tant qu'entreprise ou utisateur
int MenuPrincipal(groupeEntreprises *gE, groupePostes *gP, groupe *gPe)
{
    char choix(0) ;
 
    // Première étape : On demande à l'utilisateur ce qu'il souhaite faire et on vérifie sa saisie
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

    // Deuxième étape : On affiche le menu demandé par l'utilisateur
    switch (choix)
    {
    case '1':
        return MenuEntreprise(gE, gP, gPe) ;
        break;
    case '2':
        return MenuEmploye(gE, gP, gPe) ;
        break;
    case '3':
        return MenuChercheur(gE, gP, gPe) ;
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
int MenuEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe)
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
int MenuSeConnecterEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe)
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
    return MenuProfilEntreprise(gE, gP, gPe, (int)choix - 48) ;
    
    return 0 ;
}

// But : Affiche le menu permettant à l'utilisateur de créer le profil de son entreprise
int MenuCreerEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe)
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
int MenuProfilEntreprise(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE)
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

// But : Affiche le menu demandant confirmation à l'utilisateur avant de supprimer le profil de son entreprise
int MenuConfirmerSuppressionEntreprise(groupeEntreprises* gE, groupePostes *gP, groupe *gPe, int indexE)
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
int MenuAfficherPostesDuneEntreprise(groupeEntreprises* gE, groupePostes *gP, groupe *gPe, int indexE)
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

// But : Affiche le menu permettant à l'utilisateur de créer un poste à pourvoir
int MenuCreerPoste(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE)
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
int MenuSupprimerPoste(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE)
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
int MenuEntrepriseCherchePar(groupeEntreprises *gE, groupePostes *gP, groupe *gPe, int indexE)
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
        EntrepriseRechercheParCompetenceEtCode(gPe, competence, code_postal) ;
        cout << endl << "Appuyez sur n'importe quelle touche pour revenir sur votre profil : " ;
        cin >> choix ;
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
        break;
    
    case 'r':
        return MenuProfilEntreprise(gE, gP, gPe, indexE) ;
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

    printemployes (gPersonne);

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
    return 0;
}

int MenuModifier_Profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){

 char choix(0) ;     // choix est un char et non un int pour empêcher la saisie d'une lettre (autre que q)
   
    do
    {
        system("clear") ;
        cout << " ** Vous souhaitez actuellement modifier votre profil **" << endl << endl ;
        cout << "Vous voulez :" << endl ;
        cout << "1. Ajouter une compétence" << endl ;            
        cout << "2. Modifier votre code postal" << endl ;
        cout << "3. Changer d'adresse email" << endl ;                            
        cout << "4. rejoindre une entreprise" << endl ;
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
        return Menuajouter_Competence(gEntreprise, gPoste, gPersonne);
        break;
        
    case '2':
        return MenuMod_Adresse(gEntreprise, gPoste, gPersonne) ;
        break;
    case '3':
        return A_Implementer(gEntreprise, gPoste, gPersonne) ;
        break;
    case '4':
        return Menu_mod_entreprise(gEntreprise, gPoste, gPersonne) ;
        break;
    case '5':
        return Menuajouter_collegue(gEntreprise, gPoste, gPersonne) ;
        break;
    case '6':
        return Menusupprimer_collegue(gEntreprise, gPoste, gPersonne) ;
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
    
    return 0;

}

int MenuMod_Adresse(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){

    int newadr,id;

    //print de la table employes
    printemployes (gPersonne);

    cout << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    cout << "Ecrivez votre nouveau code postal : " << endl;
    cin >> newadr;

    modifier_adresse(id,gPersonne,newadr);

    return 0;

}

int Menu_mod_entreprise(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){
    
    int newent,id;

    //print de la table employes
    printemployes (gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl << endl;
    cin >> id;

    AfficherEntreprises(gEntreprise);

    cout << "Saisir l'ID de votre nouvelle entreprise : " << endl;
    cin >> newent;

    cout << "Votre statut entreprise a été mise à jour" << endl;

    rejoindre_entreprise(id,gPersonne,newent); //ou modifier entreprise ?

    return 0;
}


int Menuajouter_Competence(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){

    char comp[128];
    int id;

    //print de la table employes
    printemployes (gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    cout << "Saisir votre nouvelle compétence : " << endl;
    cin >> comp;

    int a = ajouter_competence(id,gPersonne,comp);

    if(a==1) cout << "vous avez déja cette compétence" << endl;
    if(a==2) cout << "vous avez déja le nombre maximal de compétence" << endl;
    if(a==3) cout << "Désolé, votre ID n'est pas répertorié" << endl;
    if(a==0) cout << "Operation effectué avec succès" << endl;

    return 0;

}

int Menuquitter_entreprise(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){


    int id;

    //print de la table employes
    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    quitter_entreprise(id,gPersonne);

    return 0;

}

void printemployes (groupe *gPersonne)
{
 if (gPersonne->personnes == NULL) cout << "Aucune personnes enregistrée" << endl ;
    else
    {
        node *tmp = gPersonne->personnes ;
        personne *e = (personne*)tmp->data ;
        while (e!= NULL && tmp != NULL)
        {
            cout << e->index << " - " << e->nom << " - "  << " - " << e->courriel << " - " << e->entreprise << endl ;
            tmp = tmp->next ;
            if(tmp != NULL) e = (personne*)tmp->data ;
            
        }
    }
}

int Menusupprimer_profil(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne)
{

    int id;

    //print de la table employes
    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    supprimer_profil(id,gPersonne);

    cout << endl << "Votre compte a été supprimé. " << endl;

    return 0;

}

int Menuajouter_collegue(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne)
{

    int id,col;

    //print de la table employes
    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre nouveau collègue : " << endl;
    cin >> col;

    int a= ajouter_collegue(id,gPersonne,col);

    if(a==1) cout << "Ce collègue est déja dans votre liste" << endl;
    if(a==2) cout << "Cet personne n'est pas dans la même entreprise que vous" << endl;
    if(a==3) cout << "Désolé, cet ID n'est pas répertorié" << endl;
    if(a==4) cout << "Désolé, vous avez atteint le nombre maximum de collègues" << endl;
    if(a==0) cout << "Operation effectué avec succès" << endl;

    return 0;

}

int Menusupprimer_collegue(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne)
{

    int id,col;

    //print de la table employes
    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre ancien collègue : " << endl;
    cin >> col;

    int a= supprimer_collegue(id,gPersonne,col);


    if(a==1) cout << "Désolé, Cet personne n'est déja plus votre collègues" << endl;
    if(a==2) cout << "Désolé, Cet personne n'est pas enregistré dans la BDD" << endl;
    if(a==0) cout << "Operation effectué avec succès" << endl;

    return 0;

}

int Menu_emploi(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){
    
    int id,choix,a;

    //print de la table employes
    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    cout << "Vous voulez :" << endl; 
    cout<< "(1) Chercher un poste selon par code postal "<<endl;
    cout<< "(2) Chercher un poste selon vos compétence"<<endl;
    cin >> choix ;

    if(choix==1){
        a=recherche_poste_postal(id,gPersonne,gPoste,gEntreprise);
        
        if(a==0) cout << "pas de poste à cette adresse" << endl;
        if(a==1) cout << "Au moins un poste à cette adresse" << endl;
        if(a==2) cout << "Problème d'indice non trouvé"<< endl;

    }
    if(choix==2){
        a=recherche_poste_comp(id,gPersonne,gPoste,gEntreprise);
        
        if(a==0) cout << "pas de poste avec cette competence" << endl;
        if(a==1) cout << "Au moins un poste avec cet competence" << endl;
        if(a==2) cout << "Problème d'indice non trouvé"<< endl;
    }
    return 0;
}
        

int Menu_emploi_collegue(groupeEntreprises* gEntreprise, groupePostes *gPoste, groupe *gPersonne){
    int id,col,choix;

    //print de la table employes
    printemployes(gPersonne);

    cout << endl << "Ecrivez l'ID correspondant à votre identité : " << endl;
    cin >> id;

    cout << "Vous voulez :" << endl; 
    cout<< "(1) Chercher un collègue qui posséde une compétence spécifique "<<endl;
    cout<< "(2) Chercher une entreprise dans laquel travail un collègue"<<endl;
    cin >> choix ;

    if (choix==1){
        char comp[128];

        cout << "Saisir la compétence recherché : " << endl;
        cin >> comp;

        int a = recherche_col_comp(id,gPersonne,comp);
        if(a==0) cout << "pas de collégue avec cet compétence" << endl;
        if(a==1) cout << "Au moins un de vos collègue posséde cette compétence" << endl;
        if(a==2) cout << "Problème d'indice non trouvé"<< endl;
    }

    if (choix==2){
        AfficherEntreprises(gEntreprise);

        cout << endl << "Ecrivez l'ID correspondant à l'entreprise: " << endl;
        cin >> col;

        int a = recherche_col_par_entre(id,gPersonne,col);

        if(a==0) cout << "pas de collégue dans cet entreprise" << endl;
        if(a==1) cout << "Au moins un de vos collègue travaille dans cette entreprise" << endl;
        if(a==2) cout << "Problème d'indice non trouvé"<< endl;
    }   
    
    return 0;
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
        return MenuModifier_Profil(gEntreprise, gPoste, gPersonne) ;
        break;
    case '3':
        return Menusupprimer_profil(gEntreprise, gPoste, gPersonne) ;
        break;
   case '5':
        return Menu_emploi(gEntreprise, gPoste, gPersonne) ;
        break;
    case '6':
        return Menu_emploi_collegue(gEntreprise, gPoste, gPersonne) ;
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
    
    return MenuChercheur(gEntreprise,gPoste,gPersonne) ;
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
        cout << "4. Mettre à jour votre statut (passer en recherche d'emploi)" << endl ;
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
        return Menusupprimer_profil(gEntreprise, gPoste, gPersonne) ;
        break;
    case '4':
        return Menuquitter_entreprise(gEntreprise, gPoste, gPersonne) ;
        break;
    case '5':
        return Menu_emploi(gEntreprise, gPoste, gPersonne) ;
        break;
    case '6':
        return Menu_emploi_collegue(gEntreprise, gPoste, gPersonne) ;
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
    
    return MenuEmploye(gEntreprise,gPoste,gPersonne) ;
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
