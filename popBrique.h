#ifndef __POPBRIQUE_H
#define __POPBRIQUE_H

#include "Window/window.h"
#include "brique.h"
#include "balle.h"
#include "partie.h"
#include <iostream>
#include <fstream>
#include <exception>

#define NMAX 80

class PopBrique{
private:
    Brique population[NMAX]; /// tableau statique de la population de brique
    int nbBriqueTotal;      /// nombre total de brique dans la partie
    int nbBriqueRestante;   /// nombre de brique qui reste à détruire pour finir le niveau
    
    int debutTerrainX, debutTerrainY;
    int tailleTerrainPopHauteur, tailleTerrainPopLargeur;
public:
    /*!
     *  \brief Constructeur qui définie la zone où les briques pourront être positionné
     *
     *  \param fenetre : permet de récupérer la hauteur et la largeur de la zone de jeu
     */
    PopBrique(const Window &fenetre);
    
    //méthodes
    int getNbBriqueTotal() const;
    int getNbBriqueRestante() const;
    
    /*!
     *  \brief Méthode qui permet de générer une population de brique automatique : pour les tests
     */
    void generationAuto();
    

    /*!
     *  \brief Méthode qui permet de mettre à jour la population de brique
     *
     *  \param fenetre : permet la mise à jour de l'affiche des briques si elles sont touchées
     *  \param b : Balle du jeu
     *  \param part : permet de mettre à jour le nombre de brique restante
     */
    void update(Window &fenetre, Balle &b, Partie &part);
    
    /*!
     *  \brief Méthode qui affiche la population de brique
     *
     *  \param fenetre : fenêtre où la population de brique doit être affiché
     */
    void afficher(Window &fenetre) const;
    
    /*!
     *  \brief Méthode qui lit un fichier de configuration
     *
     *  \param nom_fichier : nom du fichier de configuration
     *  \param part : permet de sortir les messages d'erreurs
     */
    bool lireNiveau(std::string nom_fichier,Partie &part);
    
    /*!
     *  \brief Méthode qui extrait la clef et la valeur d'une chaine de caractères
     *
     *  \param s : chaine de caractères
     *  \param s1 : clef
     *  \param s2 : valeur
     *  \param part : permet de sortir les messages d'erreurs
     */
    bool cleValeur(std::string &s, std::string &s1, std::string &s2,Partie &part);
    
    /*!
     *  \brief Méthode qui nettoie une chaine de caractères
     *  Cette méthode permet d'ignorer les commentaires qui peuvent être présent dans le fichier de configuration
     *
     *  \param s : chaine de caractères
     */
    void nettoyer(std::string &s);
    
    /*!
     *  \brief Méthode qui empêche le positionnement d'une brique sur un emplacement déja occupé par une brique
     *
     *  \param x : position x d'origine
     *  \param y : position y d'origine
     *  \param size : taille de la brique
     *  \param part : permet de sortir les messages d'erreurs
     
     */
    bool collision(int x, int y, int size, Partie &part);
    
};

#endif
