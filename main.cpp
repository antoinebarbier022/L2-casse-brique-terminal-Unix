#include "Window/window.h"
#include "casseBrique.h"
#include <string>
#include <iostream>
#include <unistd.h>


/*!
 * \file main.cpp
 * \brief Programme principal
*/

using namespace std;

int main(int argc, char** argv){
    
    //Création de l'objet jeu
    CasseBrique jeu;
    
    // initialisation de la variable qui contiendra le choix de l'utilisateur
    // Cette variable sert à la navigation entre les différentes fenêtre du programme
    CasseBrique::Choix choix;
    
    choix = jeu.parseOptions(argc,argv);
    
    startProgramX();
    // on entre dans le menu du jeu
    if( choix != CasseBrique::QUITTER){
        choix = jeu.menu();
    }
    while(choix != CasseBrique::QUITTER){
        // On execute le choix de l'utilisateur
        switch (choix) {
            case CasseBrique::MENU:
                choix = jeu.menu();
                break;
            case CasseBrique::RECOMMENCER:
            case CasseBrique::JOUER: // accède à la fenêtre du jeu
                choix = jeu.jeu();
                break;
            case CasseBrique::VOIRSCORES: // accède aux scores des joueurs
                choix = jeu.afficheFenetre("joueurs-scores.txt");
                break;
            case CasseBrique::NOMSAUTEURS: // accède aux paramètres
                choix = jeu.afficheFenetre("Auteur.txt");
                break;
            case CasseBrique::AIDE: // accède à l'aide du jeu
                choix = jeu.afficheFenetre("Aide.txt");
                break;
            case CasseBrique::QUITTER: // Quitte le jeu
                break;
            default:
                break;
        }
    }
    stopProgramX();
    return 0;
}
