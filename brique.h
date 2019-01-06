#ifndef __BRIQUE_H
#define __BRIQUE_H

#include "Window/window.h"
#include "balle.h"
#include "partie.h"

class Balle;

class Brique{
private:
    int x, y;
    int size;
    int nbPoint; // ce nombre de point de la brique -> augmente le score de x points une fois la brique détruite, ce nombre de point dépend de la resistance de la brique
    Color couleur; // dépend de la résistance de la brique
    int resist; // il existe 5 niveau de resitance et un niveau de resistance 0 qui signifie disparition de la brique
    
    /*!
     *  \brief Méthode qui modifie la couleur de la brique en fonction de sa resistance
     */
    void updateCouleur();
public:
    /*!
     *  \brief Constructeur sans pararamètre.
     *
     *  Défini une brique de taille 6, de coordonnées (-1,-1) et de resitance 0
     *  Le nombre de point que vaut la brique corresponds à 10 fois sa resitance
     *
     */
    Brique();
    /*!
     *  \brief Constructeur qui défini les coordonnées de la brique en paramètre
     *
     *  Le nombre de point que vaut la brique corresponds à 10 fois sa resitance
     *  \param x : origine x de la brique
     *  \param y : origine y de la brique
     *
     */
    Brique(int x, int y);
    /*!
     *  \brief Constructeur qui défini les coordonnées de la brique et sa resistance en paramètre
     *
     *  Le nombre de point que vaut la brique corresponds à 10 fois sa resitance
     *  \param x : origine x de la brique
     *  \param y : origine y de la brique
     *  \param resist : resitance de la brique
     *
     */
    Brique(int x, int y, int resist);
    /*!
     *  \brief Constructeur qui défini les coordonnées de la brique, sa taille et sa resistance en paramètre
     *
     *  Le nombre de point que vaut la brique corresponds à 10 fois sa resitance
     *  \param x : origine x de la brique
     *  \param y : origine y de la brique
     *  \param size : taille de la brique
     *  \param resist : resitance de la brique
     *
     */
    Brique(int x, int y, int size=6, int resist=1);
    
    //accesseurs lecture
    int getX() const;
    int getY() const;
    int getSize() const;
    int getNbPoint() const;
    Color getCouleur() const;
    int getResist() const;
    
    //accesseurs écriture
    void setX(int x);
    void setY(int y);
    void setResist(int r);
    void setSize(int s);
    
    /*!
     *  \brief Méthode qui initialise la brique sur le terrain
     *
     *  On appel la méthode d'affichage de la brique si sa resistance est différente de 0
     *  \param fenetre : permet d'afficher la brique dans la fenêtre passé en paramètre
     *
     */
    void init(Window &fenetre);
    
    /*!
     *  \brief Méthode qui met à jour les informations sur la brique
     *
     *  Cette méthode permet de changer la direction de la balle si la brique est touchée, de donner le nombre de points de la brique au joueur si sa resitance est égale à 0, de retirer un niveau de resitance à la brique si elle est touchée
     *  \param fenetre : permet d'effacer la brique dans la fenêtre passé en paramètre si elle est détruite
     *  \param b : balle qui change de direction si cette dernière touche la brique
     *  \param part : permet de modifier les infos sur la partie (ajoute du score au joueur lorsque la brique est détruite)
     *
     */
    void update(Window &fenetre, Balle &b, Partie &part);
    
    /*!
     *
     *  \param b : permet de savoir si la balle touche la brique
     *  \return true si la brique est touchée par la balle, false sinon
     *
     */
    bool estTouche(Balle &b);
    
    /*!
     *  \brief Méthode pour l'affichage de la brique
     *  \param fenetre du jeu dans laquelle la balle doit être affichée
     */
    void afficher(Window &fenetre) const;
    /*!
     *  \brief Méthode qui efface la brique
     *  \param fenetre du jeu dans laquelle la balle doit être effacée
     */
    void clear(Window &fenetre) const;
    
};
#endif
