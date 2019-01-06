#ifndef __CASSEBRIQUE_H
#define __CASSEBRIQUE_H

#include "Window/window.h"
#include "balle.h"
#include "raquette.h"
#include "brique.h"
#include "popBrique.h"
#include "partie.h"
#include "scoresJoueurs.h"
#include "tabOptions.h"

#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

// dimension de la fenetre de l'app
#define HAUTEUR 23
#define LARGEUR 91

#define HELP_ID          1
#define VERSION_ID       2
#define AUTEUR_ID        3
#define PLAYER_ID        4


class CasseBrique{
public:
    enum Choix{
        MENU,
        JOUER,
        RECOMMENCER,
        NOMSAUTEURS,
        VOIRSCORES,
        PARAMETRES,
        AIDE,
        QUITTER,
        AUCUN
    };
    
private:
    std::string titre;          /// titre du jeu
    std::string version;        /// version du jeu
    std::string anneeLicenceEtudiant;
    
    std::string nomJoueur;  /// nom du joueur qui joue au jeu
    
    TabOptions opts; /// tableau qui contient les options
    
public:
    /*!
     *  \brief Constructeur
     *
     *  \param nomJ nom du joueur en paramètre
     */
    CasseBrique(std::string nomJ="Player");
    
    /*!
     *  \brief Analyse des options
     *
     *  Methode qui analyse les options passées au programme s'il y en a
     * Si une option est passée au programme alors on execute cette option et la méthode retourne le choix QUITTER
     * sinon la méthode renvoie le choix AUCUN
     *
     *
     *  \return La constante qui correspond au choix de l'utilisateur
     */
    Choix parseOptions(int argc, char** argv);
    
    
    /*!
     *  \brief Méthode qui affiche une fenêtre avec le texte d'un fichier passée en paramètre de la fonction
     *
     *  \param nomFichier Nom du fichier que l'on souhaite afficher dans la fenêtre
     *
     *  \return La constante qui correspond au choix de l'utilisateur
     *
     */
    Choix afficheFenetre(std::string nomFichier);
    
    
    /*!
     *  \brief Méthode qui en fonction de la touche clavier pressée, renvoie un choix
     *
     *  \param toucheClavier Méthode qui prend en paramètre une touche clavier
     *
     *  \return La constante qui correspond au choix de l'utilisateur
     */
    Choix toucheChangementFenetre(int toucheClavier);
    
    /*!
     *  \brief Méthode qui affiche le menu et une liste permettant à l'utilisateur de choisir son action. Une fois qu'il a selectionné l'action, la méthode renvoie le choix de l'utilisateur
     *
     *  \return La constante qui correspond au choix de l'utilisateur
     */
    Choix menu();
    
    /*!
     *  \brief Méthode qui execute la fenetre du jeu. Dans cette fenetre, il y a tout le déroulement du jeu
     *
     *  \return La constante qui correspond au choix de l'utilisateur
     */
    Choix jeu();
    
};

#endif