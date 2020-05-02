#include <iostream>
using namespace std ;
#include <fstream>
#include <ctime>
#include <string.h>

#include "journal.h"

// But : Récupérer la date et l'heure de l'OS (fonction trouvée sur internet)
string AfficherDate()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    string str(buffer);

    return str ;
}

// But : Ajouter une entrée au journal renseignant la date et l'heure de l'ouverture de l'application
void journal_OuvertureApplication()
{ 

    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << AfficherDate() << " : Ouverture de l'application " << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant la date et l'heure de la fermeture de l'application
void journal_FermetureApplication()
{ 

    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << AfficherDate() << " : Fermeture de l'application " << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant les informations de l'entreprise créé
void journal_CreationEntreprise(entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "    " << AfficherDate() << " : Création de l'entreprise " << 
        e->index << " - " << e->nom << " - " << e->code_postal << " - " << e->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant l'entreprise qui s'est connectée
void journal_ConnexionEntreprise(entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "    " << AfficherDate() << " : Connexion de l'entreprise " << 
        e->index << " - " << e->nom << " - " << e->code_postal << " - " << e->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant l'entreprise qui a été supprimée
void journal_SuppressionEntreprise(entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : Suppression de l'entreprise " << 
        e->index << " - " << e->nom << " - " << e->code_postal << " - " << e->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant le poste qui a été supprimé
void journal_SuppressionPoste(poste* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : Suppression du poste " << 
        p->index << " - " << p->titre << " - " << p->entreprise << " - | " ;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if(p->competence[i][j] != '\0') FluxVersJournal << p->competence[i][j] ;
            }
            if(p->competence[i][0] != '\0') FluxVersJournal << " | " ;
        }
        FluxVersJournal << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant les informations du poste créé
void journal_CreationPoste(poste* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : Création du poste " << 
        p->index << " - " << p->titre << " - " << p->entreprise << " - | " ;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if(p->competence[i][j] != '\0') FluxVersJournal << p->competence[i][j] ;
            }
            if(p->competence[i][0] != '\0') FluxVersJournal << " | " ;
        }
        FluxVersJournal << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que l'entreprise connectée à consulté sa liste des postes à pourvoir
void journal_EntrepriseConsultePostes(entreprise* e)
{ 

    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << e->nom << " a consulté sa liste des postes à pourvoir " << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que l'entreprise a effectué une recherche par compétence, et affiche la compétence
void journal_EntrepriseRechercheCompetence(entreprise* e, char competence[128])
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << e->nom << " a fait une recherche par compétence (" << competence << ")" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que l'entreprise a effectué une recherche par compétence et code postal, et affiche la compétence et le code postal
void journal_EntrepriseRechercheCompetenceEtCode(entreprise* e, char competence[128], int code)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << e->nom << " a fait une recherche par compétence et code postal (" << competence << ", " << code <<  ")" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant l'entreprise qui s'est déconnectée
void journal_DeconnexionEntreprise(entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "    " << AfficherDate() << " : Déconnexion de l'entreprise " << 
        e->index << " - " << e->nom << " - " << e->code_postal << " - " << e->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}




/*

journal_DeconnexionEntreprise(g_indexEntreprise(gE, indexE)) ;

*/