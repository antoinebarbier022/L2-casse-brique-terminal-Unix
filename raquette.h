#ifndef __RAQUETTE_H
#define __RAQUETTE_H

#include "Window/window.h"
#include "balle.h"

class Balle;

class Raquette{
private:
    int x, y;
    int size;
    Color couleur;
    
public:
    /*!
     * \brief La brique est initialisé au milieu de la fenêtre avec une couleur et une taille par défaut.
     *  La couleur par défaut est la couleur de la bordure de la fenêtre du jeu.
     *  La taille  par est égale à 10
     *  \param fenetre : fenêtre dans laquelle affiche la raquette
     */
    Raquette(const Window &fenetre);
    /*!
     * \brief La brique est initialisé au milieu de la fenêtre avec une couleur et une taille par défaut.
     *  La couleur par défaut est la couleur de la bordure de la fenêtre du jeu.
     *  \param fenetre : fenêtre dans laquelle affiche la raquette
     *  \param size : taille de la raquette
     */
    Raquette(const Window &fenetre, int size);
    
    /*!
     * \brief accesseurs en lecture de l'attribut x
    */
    int getX() const;
    /*!
     * \brief accesseurs en lecture de l'attribut y
     */
    int getY() const;
    /*!
     * \brief accesseurs en lecture de l'attribut size
     */
    int getSize() const;
    
    /*!
     * \brief accesseurs en écriture de l'attribut x
     * \param x : position x origine raquette
     */
    void setX(int x);
    /*!
     * \brief accesseurs en écriture de l'attribut y
    * \param y : position y origine raquette
     */
    void setY(int y);
    /*!
     * \brief accesseurs en écriture de l'attribut size
     * \param s : taille de la raquette
     */
    void setSize(int s);
    
    
    /*!
     * \brief Méthode qui met à jour l'emplacement de la raquette
     * \param fenetre : fenêtre dans laquelle affiche la raquette
     * \param toucheClavier : touche du clavier
     * \brief déplacement de la raquette à droite ou à gauche si la touche du clavier en paramètre correspond bien à celles du déplacement
     */
    void update(const Window &fenetre, int toucheClavier);
    
    /*!
     * \brief Méthode qui permet de changer la direction et l'angle de la balle en fonction de l'endroit d'impact entre cette dernière et la raquette.
     * \param b : balle
     */
    void changeBalleAngle(Balle &b) const;
    
    /*!
     * \brief Méthode qui permet de déplacer la raquette à gauche
     * \param speed : le paramètre speed est le nombre de case de déplacement de la raquette
     * \param fenetre : fenêtre dans laquelle affiche la raquette
     */
    void moveLeft(int speed, const Window &fenetre);

    /*!
     * \brief Méthode qui permet de déplacer la raquette à droite
     * \param speed : le paramètre speed est le nombre de case de déplacement de la raquette
     * \param fenetre : fenêtre dans laquelle affiche la raquette
     */
    void moveRight(int speed, const Window &fenetre);
    
    /*!
     * \brief Méthode qui permet d'afficher la raquette dans la fenêtre
     * \param fenetre : fenêtre dans laquelle affiche la raquette
     */
    void afficher(const Window &fenetre) const;
    
    /*!
     * \brief Méthode qui permet d'effacer la raquette de la fenêtre
     * \param fenetre : fenêtre dans laquelle affiche la raquette
     */
    void clear(const Window &fenetre) const;
    
};
#endif
