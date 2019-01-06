#ifndef __SCORESJOUEURS_H
#define __SCORESJOUEURS_H

#include "Window/window.h"
#include "partie.h"
#include <iostream>
#include <fstream>

class ScoresJoueurs{
private:
    /*!
     * \struct <Joueur>
     * \brief Structure qui permet d'avoir les infos d'un joueur : son nom et son score
     */
    struct Joueur{
        std::string nom;
        int score;
    };
    
    std::string nomFichierScoreJoueur; /// nom du fichier qui contient les scores des joueurs
    
    Joueur tabJoueur[500];
    int nbScore; /// nombre de scores dans le tableau statique
    
public:
    /*!
     * \brief Constructeur sans paramètre de la classe.
     *
     * Enregistre le nom du fichier des scores dans l'attribut nomFichierScoreJoueur
     */
    ScoresJoueurs();
    
    /*!
     * \brief Méthode qui lit le fichier des scores et récupère les informations du fichier pour les stocker dans le tableau du scores des joueurs
     */
    void lectureFichierScore();
    
    /*!
     * \brief Méthode qui affiche le score des joueurs dans une fenêtre
     * \param fenetre dans laquelle on souhaite afficher les scores
     * \param nbLigneScore : nombre de ligne du fichier à afficher dans la fenêtre
     * \param centre : Booléen qui permet de modifié l'affichage dans la fenêtre (centré ou non).
     */
    void afficheScores(const Window &fenetre,int nbLigneScore, bool centre);
    
    /*!
     * \brief Méthode qui charge le nom et le score du joueur qui joue actuellement au jeu et on le charge dans le tableau des scores
     * Cette méthode met aussi à jour le meilleur score du joueur (si le score de sa partie est son meilleur score).
     * On trie ensuite le tableau des scores puis on charge le contenu du tableau des scores dans le fichier
     * \param partieJ :  permet de récupérer le score de la partie du joueur
     */
    void chargeScoreJoueurDansFichier(const Partie &partieJ);
};

#endif
