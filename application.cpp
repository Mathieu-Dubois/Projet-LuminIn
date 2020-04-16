#include <iostream>
using namespace std ;

#include "lib/bibliotheques.h"

int main()
{    
    // Création du groupe entreprise d'après "entreprises.csv"
    groupeEntreprises *groupeEntr = NULL ;
    FILE *dbE = fopen("entreprises.csv", "r");
    groupeEntr = g_openEntreprisesCSV(dbE);
    fclose(dbE);
    
    MenuPrincipal(groupeEntr) ;

    return 0 ;
}
