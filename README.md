![](https://github.com/Theo-PASQUIER/DevCommeLesPros-2020-Projet/workflows/Test%20master/badge.svg)

# Manuel de l'utilisateur

Bienvenue sur le manuel de l'utilisateur de l'application __LuminIn__ réalisé par Schmitt Manon, Dubois Mathieu et Pasquier Théo.
Ce manuel vous apprendra à utiliser cette application tout en profitant pleinement de toutes ses fonctionnalités.  
Bonne lecture ! ;-) 

# Table des matières
- [Ouverture et fermeture de l'application](#Ouverture-et-fermeture-de-lapplication)
- [Modes de connexion](#Modes-de-connexion)
    - [Mode entreprise](#Mode-entreprise)
    - [Mode utilisateur](#Mode-utilisateur)
- [Création d'un profil d'entreprise](#Création-dun-profil-dentreprise)
- [Création d'un profil d'utilisateur](#Création-dun-profil-dutilisateur)
- [Fonctionalités disponibles pour une entreprise](#Fonctionalités-disponibles-pour-une-entreprise)
    - [Consulter les postes à pourvoir de votre entreprise](#Consulter-les-postes-à-pourvoir-de-votre-entreprise)
    - [Ajouter un poste à pourvoir](#Ajouter-un-poste-à-pourvoir)
    - [Supprimer un poste à pourvoir](#Supprimer-un-poste-à-pourvoir)
    - [Faire une recherche parmi les chercheurs d'emploi](#[Faire-une-recherche-parmi-les-chercheurs-demploi)
    - [Supprimer le profil de votre entreprise](#Supprimer-le-profil-de-votre-entreprise)  
- [Fonctionalités disponibles pour un utilisateur](#Fonctionalités-disponibles-pour-un-utilisateur)
    - [Modifier votre profil](#Modifier-votre-profil)
    - [Supprimer votre profil](#Supprimer-votre-profil)
    - [Faire une recherche d'emploi ou de collègue](#Faire-une-recherche-demploi-ou-de-collègue)
- [Administration et maintenance de l'application](#Administration-et-maintenance-de-l-application)
    - [Journal](#Journal)
    - [Réglages des paramètres](#Réglages-des-paramètres)
    - [Commandes console](#Commandes-console)
    - [Programme de test](#Programme-de-test)


# Ouverture et fermeture de l'application

Pour lancer l'application, entrez la commande __make application__ dans un terminal. Vous arriverez dans le menu principal.  
Quand vous voudrez quitter l'application, si vous êtes dans un menu qui vous le propose, appuyez sur la touche __q__ de votre clavier.  
A chaque utilisation, toutes les actions que vous effectuez seront enregistrées et disponibles lors des futures utilisations.  

# Modes de connexion

L'application __LuminIn__ propose deux modes de connexion. Un mode __entreprise__ qui permet à l'utilisateur qui s'y connecte de gérer son entreprise en proposant des postes à pourvoir ou en faisant des recherches de personnes en recherche d'emploi. Le second mode __utilisateur__ permet à un utilisatur, qu'il soit employé dans une entreprise ou actuellement en recherche d'emploi, de gérer son profil, son réseau de collègues, ou encore de faire des recherches de postes à pourvoir ou de collègues.

## Mode entreprise

Si vous choisissez d'utiliser l'application en mode entreprise, vous arriverez sur le __menu entreprise__. Vous aurez alors deux possibilités :  
* Vous connecter à votre profil si votre entreprise est déjà enregistrée dans l'application.  
* Créer le profil de votre entreprise si vous êtes un nouvel utilisateur et que votre entreprise n'est pas encore enregistrée dans l'application.

## Mode utilisateur

Si vous choisissez d'utiliser l'application en mode utilisateur, vous arriverez sur le __menu utilisateur__. Vous aurez alors deux possibilités :  
* Vous connecter à votre profil si vous avez déjà créé un compte sur l'application.  
* Créer votre profil si vous utilisez l'application pour la première fois.  

# Création d'un profil d'entreprise

Pour créer le profil d'une entreprise, vous aurez besoin de renseigner :
* Le nom de l'entreprise : 40 caractères maximum, ne doit pas contenir de chiffre et le premier caractère ne doit pas être un caractère accentué.
* Un code postal : 5 chiffres
* Une adresse mail  
* Un mot de passe : minimum 8 caractères et maximum 20. Majuscules et minuscules autorisés, ainsi que quelques caractères spéciaux.

Si vous ne respectez pas ces indications, une nouvelle saisie vous sera demandée.

# Création d'un profil d'utilisateur

Pour créer le profil d'un utilisateur, vous aurez besoin de renseigner : 
* Le nom de l'utilisateur : 25 caractères maximum, ne peut pas contenir de chiffre et le premier caractère ne doit pas être un caractère accentué. Une seule majuscule autorisé; pour le premier caractère.
* Le prénom de l'utilisateur : 25 caractères maximum, ne peut pas contenir de chiffre et le premier caractère ne doit pas être un caractère accentué.
* Une adresse mail
* Un code postal : 5 chiffres
* Un mot de passe : minimum 8 caractères et maximum 20. Majuscules et minuscules autorisés, ainsi que quelques caractères spéciaux.
* L'index de votre entreprise si vous êtes un employé (pas d'inquiétude si vous ne vous souvenez plus de l'identifiant de votre entreprise, ils seront tous affichés)
* Vos compétences (jusqu'à 5\* maximum) : uniquement des lettres minuscules et des chiffres. Pas de caractères accentué.
* Si vous le voulez, l'index de vos collègues pour commencer à former votre réseau\*\*  

Si vous ne respectez pas ces indications, une nouvelle saisie vous sera demandée.  
  
\* Vous devez saisir au minimim 1 compétence. Le nombre maximum de compétences peut être modifié par l'administrateur de l'application. Le maximum par défaut est 5 compétences.  
\*\* L'administrateur de l'application peut choisir la taille maximale d'un réseau de collègues. Le maximum par défaut est 99 collègues. L'application peut également supporter jusqu'à 100 profils enregistrés simultanément (également modifiable par l'administrateur).

# Fonctionalités disponibles pour une entreprise

Si vous utilisez l'application en mode entreprise, une fois sur votre profil, vous aurez accès aux fonctionalités présentés ci-dessous.  

## Consulter les postes à pourvoir de votre entreprise

Ce menu vous permet de visualiser l'ensemble des postes à pourvoir de votre entreprise sous forme de liste. Pour chaque poste vous verrez : son index dans la base de données, son titre, ainsi que les compétences requises pour chaque poste. Si votre entreprise ne possède pas de poste à pourvoir, cette section sera vide. Si vous ajoutez ou supprimez des postes, la liste sera automatiquement mise à jour sans aucune action de votre part.  

## Ajouter un poste à pourvoir

Ce menu vous permet d'ajouter un poste à pourvoir par votre entreprise. Vous aurez besoin de renseigner :
* Le titre du poste : 40 caractères maximum, avec possibilités d'inclure des chiffres. Le premier caractère ne peut être accentué
* Les compétences requises pour le poste (jusqu'à 5\* maximum). Uniquement des lettres minuscules et des chiffres. Pas de caractères accentué.

Si vous ne respectez pas ces indications, une nouvelle saisie vous sera demandée.  
  
\* Vous devez saisir au minimim 1 compétence. Le nombre maximum de compétences peut être modifié par l'administrateur de l'application. Le maximum par défaut est 5 compétences. 

## Supprimer un poste à pourvoir

Ce menu vous permet de supprimer un poste à pourvoir de votre entreprise. Vous devrez renseigner l'index du poste que vous voulez supprimer.

## Faire une recherche parmi les chercheurs d'emploi

Ce menu vous permet d'effectuer une recherche parmi tous les chercheurs d'emploi. Il y a deux types de recherche disponible :
* Recherche par compétences : Cette recherche va comparer les compétences de tous les chercheurs d'emploi avec les compétences requises dans vos postes à pourvoir. Si le profil d'un chercheur d'emploi correspond à l'un de vos postes, ses coordonnées seront affichées.  
* Recherche par compétences et par code postal : Cette recherche va comparer les compétences de tous les chercheurs d'emploi avec les compétences requises dans vos postes à pourvoir. Si le profil d'un chercheur d'emploi correspond à l'un de vos postes et que son code postal est identique à celui de votre entreprise, ses coordonnées seront affichées.

## Supprimer le profil de votre entreprise

Ce menu vous permet de supprimer le profil de votre entreprise de l'application. Si vous supprimez votre profil, tous les postes à pourvoir par votre entreprise seront également supprimés. Toutes les personnes employés dans votre entreprises passeront automatiquement en chercheur d'emploi.  
Attention la suppression de votre profil est irréversible.

# Fonctionalités disponibles pour un utilisateur

Si vous utilisez l'application en mode utilisateur, une fois sur votre profil, vous aurez accès aux fonctionalités présentés ci-dessous.  

## Modifier votre profil

Ce menu vous permet à tout moment de modifier toutes les informations de votre profil. Vous pouvez ainsi :  
* Modifier votre code postal
* Modifier votre adresse mail
* Ajouter une compétence (jusqu'à 5\* maximum). Uniquement des lettres minuscules et des chiffres. Pas de caractères accentué.
* Ajouter un collègue à votre réseau. Vous devrez saisir son index. Les index de toutes les personnes enregistrés et qui ne font pas partie de votre réseau seront affichés.
* Supprimer un collègue de votre réseau. Vous devrez saisir son index. L'index de tous vos collègues seront affichés.
* Modifier votre entreprise. Vous devrez saisir son index. L'index de toutes les entreprises seront affichés.
* Démissioner de votre entreprise. Cette option ne sera disponible uniquement si vous êtes employé dans une entreprise. Si vous choisissez de démissionner, votre profil passera automatiquement en chercheur d'emploi.  

\* Le nombre maximum de compétences peut être modifié par l'administrateur de l'application. Le maximum par défaut est 5 compétences.  

## Supprimer votre profil

Ce menu vous permet de supprimer votre profil de l'application. Si vous supprimez votre profil, vous serez effacé du réseau de tout vos collègues.  
Attention la suppression de votre profil est irréversible.

## Faire une recherche d'emploi ou de collègue

Ce menu vous permet d'effectuer deux types de recherches. Des recherches de postes à pourvoir et des recherches de collègues.
* Recherche de postes par compétence : Cette recherche va comparer vos compétences avec tous les postes à pourvoir. Pour chaque poste correspondant à votre profil et vos compétences, seront affichés : le titre du poste, l'entreprise qui le propose ainsi que les coordonnées de l'entreprise.
* Recherche de postes par compétence et code postal : Cette recherche va comparer vos compétences avec tous les postes à pourvoir. Pour chaque poste correspondant à votre profil et vos compétences, si l'entreprise qui le propose a le même code postal que vous, seront affichés : le titre du poste, l'entreprise qui le propose ainsi que les coordonnées de l'entreprise.
* Recherche de collègue par entreprise : Affiche tous les collègues de votre réseau qui travaillent dans une entreprise. Vous devrez saisir l'index de l'entreprise dans laquelle vous voulez effectuer la recherche. Tous les index des entreprises seront affichés.
* Recherche de collègue par compétence : Cette recherche affichera les coordonnées de tous vos collègues travaillant actuellement dans une entreprise pouvant vous proposer un poste.

# Administration et maintenance de l'application

## Journal

Toutes les actions effectuées dans l'application sont sauvegardées dans le fichier __journal.txt__. Afin de mieux se repérer dans le journal, un système d'indentation a été mis en place. Il est ainsi plus facile de repérer les actions effectuées lors d'une seule utilisation de l'application. La date et l'heure de chaque action est également enregistré.

## Réglages des paramètres

L'administrateur de l'application peut choisir de modifier le nombre de compétences maximum qu'une personne peut enregistrer dans son profil. De même, il est également possible de modifier le nombre de collègues maximum qu'une personne peut avoir dans son réseau. Pour cela, il suffit de modifier la valeur des macros __MAX_AMIS__ et __MAX_COMPETENCES__ dans le fichier __bibliotheques.h__.

## Commandes console

* __make clean__ : supprime le dossier build contenant tous les fichiers objets et les exécutables
* __make application__ : lance l'application
* __make check__ : lance le programme de test
* __make reset__ : réinitialise les fichiers csv à leur état d'origine  (tel qu'ils ont été distribué initilament)

## Programme de test

Il existe un deuxième programme exécutable qui est un programme de test des fonctions internes à l'application. A chaque fois que ce programme est lancé, une sauvegarde du journal ainsi que des fichiers csv est effectuée, puis restituée à la fin de l'exécution. Cela permet d'éviter de modifier le journal et la base de donnée si l'on veut effectuer des tests. De plus, quand le programme de test s'exécute, il utilise la base de donnée "modele", celle qui est enregistrée quand on utilise la commande "make reset".  

Remarque : L'application livrée est une démonstration. Les fichiers csv sont pré-remplis. Le mot de passe d'une entreprise est son nom suivie de sont index (Disney1). Le mot de passe d'une personne est son prénom suivie de son index (Tigrou6).
  
