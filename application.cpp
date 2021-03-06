#include <iostream>
using namespace std ;

#include "lib/bibliotheques.h"

int main()
{   
    journal_OuvertureApplication() ;

    // Création du groupe d'entreprises
    groupeEntreprises *gE = NULL;
    {
        FILE *dbE = NULL ;
        dbE = fopen("entreprises.csv", "r");
        gE = g_openEntreprisesCSV(dbE);
        fclose(dbE);
    }
    
    // Création du groupe de postes
    groupePostes *gP = NULL ;
    {
        FILE *dbP = NULL ;
        dbP = fopen("postes.csv", "r");
        gP = g_openPostesCSV(dbP);
        fclose(dbP);
    }

    // Création du groupe de personnes
    groupePersonnes *gPe = NULL ;
    {
        FILE *dbPe = NULL ;
        dbPe = fopen("employes.csv", "r");
        gPe = g_open(dbPe);
        fclose(dbPe);
    }

    MenuPrincipal(gE, gP, gPe) ;

    // cout << "TEST DE HACHAGE" << endl << endl ;
    // string clair = "" ;
    // cout << "Le mot de passe : " ;
    // cin >> clair ;
    // size_t chiffre = std::hash<std::string>{}(clair) ;
    // cout << "Le clair est '" << clair << "' et le chiffré est :   " << chiffre << endl ;
   

    journal_FermetureApplication() ;

    return 0 ;
}
