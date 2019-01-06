#include <string>
#include "balle.h"
#include "Window/window.h"

#ifndef __PARTIE_H
#define __PARTIE_H

class Balle;
class Partie{
private:
    std::string nomJoueur;
    int score; //Score au cours de la partie
    int nbBriqueRestante; // nombre de brique qu'il reste à détruire
    int nbBalleRestante; // nombre de balle restante du joueur
    bool finPartie ; // arrête la partie si true
    
    Window *fenetreInfo;
    
    int niveau;
    
    bool erreur;
    
public:
    // Constructeurs
    Partie(std::string joueur, Window &fenetre);
    //Partie(std::string joueur, PopBrique niv);
    
    ~Partie();
    
    // Accesseurs en lecture
    std::string getNomJoueur() const;
    int getScore() const;
    int getNbBriqueRestante() const;
    int getNbBalleRestante() const;
    bool getFinPartie() const;
    bool getErreur() const;
    int getNiveau() const;
    
    void setNbBriqueRestante(int nb);
    void setErreur(bool e);
    void setNiveau(int n);
    
    //Accesseurs en ecriture
    void setFinPartie(bool fin);
    
    void updateInfoPartie();
    
    // Méthode qui affiche un message en fin de partie
    void messageFinPartie();
    
    void messageErreur(std::string message);

    void messageFinNiveau();
    
    // Méthode qui diminue nombre de balle
    void balleSortieTerrain(const Window &fenetre, Balle &b);
    
    // Méthode qui ajoute un score au score de la partie
    void ajouteScore(int s);
    
    
    
    
};

#endif
