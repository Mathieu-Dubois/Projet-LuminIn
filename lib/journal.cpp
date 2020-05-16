#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std ;
#include "journal.h"

/* ============================================================================================================
||
||                                 JOURNAL PARTIE GENERALE 
||
   ============================================================================================================ */

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


/* ============================================================================================================
||
||                                 JOURNAL PARTIE ENTREPRISE 
||
   ============================================================================================================ */

// But : Ajouter une entrée au journal renseignant les informations de l'entreprise créée
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
        for (int i = 0; i < MAX_COMPETENCES; i++)
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
        for (int i = 0; i < MAX_COMPETENCES; i++)
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

// But : Ajouter une entrée au journal renseignant que l'entreprise a effectué une recherche
//       de personne par compétence
void journal_EntrepriseRecherchePersonneParCompetence(entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << e->nom << " a fait une recherche de personne par compétence" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que l'entreprise a effectué une recherche
//       de personne par compétence et code postal
void journal_EntrepriseRecherchePersonneParCompetenceEtCode(entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << e->nom << " a fait une recherche de personne par compétence et code postal" << endl ;
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


/* ============================================================================================================
||
||                                 JOURNAL PARTIE PERSONNE 
||
  ============================================================================================================ */

//  But : Ajouter une entrée au journal renseignant la personne qui s'est connectée
void journal_ConnexionPersonne(personne* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "    " << AfficherDate() << " : Connexion du compte " << 
        p->index << " - " << p->nom << "  " << p->prenom << " - " << p->adresse << " - " << p->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant la personne qui s'est déconnectée
void journal_DeconnexionPersonne(personne* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "    " << AfficherDate() << " : Déconnexion du compte " << 
        p->index << " - " << p->nom << "  " << p->prenom << " - " << p->adresse << " - " << p->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant les informations de la personne créée
void journal_CreationPersonne(personne* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "    " << AfficherDate() << " : Création du compte " << 
        p->index << " - " << p->nom << " " << p->prenom << " - " << p->adresse << " - " << p->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant la personne qui a été supprimée
void journal_SuppressionPersonne(personne* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : Suppression du profil  " << 
        p->index << " - " << p->nom << " " << p->prenom << " - " << p->adresse << " - " << p->courriel << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a quitté son entreprise
void journal_QuitterEntreprise(personne* p, entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " <<  p->nom << " " << p->prenom << " quitte l'entreprise " << e->nom << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a modifié son code postal
void journal_PersonneMod_CodePostal(personne* p, int code_postal, int new_code_postal)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom << " a modifié son code postal (" 
        << code_postal << " -> " << new_code_postal << ")" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a ajouté une compétence à son profil
void journal_Personneajouter_Competence(personne* p, char competence[128])
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate()  << " : " << p->nom << " " << p->prenom << " a ajouté une compétence à son profil (" 
        << competence << ")" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a changé d'entreprise
void journal_Personne_mod_entreprise(personne* p, entreprise* e, entreprise*  new_e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        if(p->entreprise == -1 && new_e == NULL) ; // On ne fait rien
        else if(new_e == NULL)  // On indique que la personne quitte son entreprise
        {
            journal_QuitterEntreprise(p,e) ;
        }
        else if(p->entreprise == -1) // On indique que la personne rejoint une entreprise
        {
            FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom << " a rejoint l'entreprise "
            << new_e->nom << endl ;
        }
        else  // On indique que la personne change d'entreprise
        {
            journal_QuitterEntreprise(p,e) ;
            FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom << " a rejoint l'entreprise "
            << new_e->nom << endl ;
        }
        
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a ajouté un collègue à son réseau
void journal_PersonneAjouter_Collegue(personne* p, personne* np)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate()  << " : " << p->nom << " " << p->prenom << " a ajouté " <<
        np->nom << " " << np->prenom << " à son réseau de collègue" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a supprimé un collègue de son réseau
void journal_PersonneSupprimer_Collegue(personne* p, personne* np)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate()  << " : " << p->nom << " " << p->prenom << " a supprimé " <<
        np->nom << " " << np->prenom << " de son réseau de collègue" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche de poste par compétence
void journal_PersonneRecherchePosteParCompetence(personne* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom << " a fait une recherche de poste par compétence" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche
//       de poste par compétence et code 
void journal_PersonneRecherchePosteParCompetenceEtCode(personne* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom 
        << " a fait une recherche de poste par compétence et code postal" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche de collègue par compétence
void journal_PersonneRechercheCollegueParCompetence(personne* p)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom << " a fait une recherche de collègue par compétence" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a effectué une recherche de collègue par entreprise
void journal_PersonneRechercheCollegueParEntreprise(personne* p, entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom << " a fait une recherche de collègue par entreprise (" << e->nom << ")" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne a modifié son adresse mail
void journal_Personne_modifier_mail(personne* p, char mail[128], char newmail[128] )
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "        " << AfficherDate() << " : " << p->nom << " " << p->prenom << " a modifié son adresse mail (" 
        << mail << " -> " << newmail << ")" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la personne est apparu dans le résultat d'une recherche 
void journal_PosteApparuRecherche(poste* p, entreprise* e)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "            " << AfficherDate() << " : " << p->titre << " pourvu par " << e->nom ;
        FluxVersJournal << " est apparu dans le résultat de la recherche" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que le poste est apparu dans le résultat d'une recherche 
void journal_PersonneApparuRecherche(personne* pe)
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "            " << AfficherDate() << " : " << pe->nom << " " << pe->prenom << " est apparu dans le résultat de la recherche" << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}

// But : Ajouter une entrée au journal renseignant que la recherche n'a pas donné de résultat 
void journal_RechercheSansResultat()
{ 
    ofstream FluxVersJournal("journal.txt", ios::app) ;
    if(FluxVersJournal)
    {
        FluxVersJournal << "            " << AfficherDate() << " : La recherche n'a pas donné de résultat"  << endl ;
    }
    else
    {
        cout << "Erreur : Impossible d'accéder au journal" << endl ;
    }
    FluxVersJournal.close() ;
}
