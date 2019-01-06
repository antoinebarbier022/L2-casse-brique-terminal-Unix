#ifndef __BALLE_H
#define __BALLE_H

#include "Window/window.h"
#include "raquette.h"
#include "brique.h"


class Raquette;
class Brique;

class Balle{
public:
    /*!
     * \enum <degree>
     * \brief énumération qui établie les différents angles possibles
     */
    enum degree{
        angleDroit,
        angleIncline,
        angleDiagonale,
        nombreAngle
    };
private:
    int x, y;             /// position de la balle
    degree angle;        /// angle de la balle
    bool haut, droite;  /// direction de la balle
    char caractere;    /// forme de la balle
    Color couleur;    /// couleur de la balle
    bool run;       /// booléen pour savoir si la balle est lancée ou non
    
public:
    /*!
     *  \brief Constructeur sans paramètre.
     *
     *  La balle est imagée par le symbole '@'
     */
    Balle();
    /*!
     *  \brief Constructeur avec le symbole de la balle passé en paramètre
     *
     *  \param caract défini le symbole de la balle
     */
    Balle(char caract);
    /*!
     *  \brief Constructeur avec le symbole et la couleur de la balle passé en paramètre
     *
     *  \param caract défini le symbole de la balle
     *  \param coul défini la couleur de fond de la balle
     */
    Balle(char caract, Color coul);
    
    //accesseurs en lecture
    int getX() const;
    int getY() const;
    degree getAngle() const;
    bool getDirectionHaut() const;
    bool getDirectionDroite() const;
    Color getCouleur() const;
    bool getRun() const;
    
    //accesseurs écriture
    char getCaractere() const;
    void setDirectionHaut(bool h);
    void setDirectionDroite(bool d);
    void setAngle(degree a);
    void setCaractere(char c);
    void setCouleur(Color c);
    void setRun(bool r);
    
    /*!
     *  \brief Méthode qui permet d'initialiser la position de la balle sur le milieu de la raquette
     *
     *  \param fenetre dans laquelle on affiche la balle
     *  \param r est l'objet raquette du jeu
     *
     */
    void init(const Window &fenetre, const Raquette &r);
    
    /*!
     *  \brief Méthode qui permet de lancer la balle
     *
     *  \param toucheClavier correspond à la touche du clavier que le joueur a pressé
     */
    void lancerBalle(int toucheClavier);
    
    /*!
     *  \brief Méthode qui met à jour la nouvelle position de la balle
     *  \param fenetre dans laquelle la balle se situe
     *  \param r est l'objet raquette du jeu
     */
    void update(const Window &fenetre, const Raquette &r);
    
    /*!
     *  \brief Méthode qui change la direction de la balle si elle entre en collision avec une des bordures de la fenêtre
     */
    void direction(const Window &fenetre);
    /*!
     *  \brief Méthode qui change la direction de la balle si elle entre en collision avec une brique
     */
    void direction(const Brique &br);
    /*!
     *  \brief Méthode qui change la direction de la balle si elle entre en collision avec la raquette
     */
    void direction(const Raquette &r);
    
    /*!
     *  \brief Méthode qui change la position de la balle en fonction de la direction et de l'angle
     */
    void deplacement();
    
    
    /*!
     *  \brief Méthode qui affichage la balle
     *  \param fenetre du jeu dans laquelle la balle doit être affichée
     */
    void afficher(const Window &fenetre) const;
    /*!
     *  \brief Méthode qui efface la balle
     *  \param fenetre du jeu dans laquelle la balle doit être effacée
     */
    void clear(const Window &fenetre) const;
    
};
#endif