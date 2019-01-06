#include "partie.h"

// Constructeurs
Partie::Partie(std::string joueur, Window &fenetre) : nomJoueur(joueur), score(0), nbBalleRestante(3), finPartie(false){
    this->fenetreInfo = &fenetre;
    this->erreur=false; // il n'y a pas d'erreur
    this->niveau = 0;
}
//Partie::Partie(std::string joueur, PopBrique niv){}

Partie::~Partie(){
    this->fenetreInfo = NULL; // ne pas delete sinon bug malloc
}

// Accesseurs en lecture
std::string Partie::getNomJoueur() const{           return this->nomJoueur; }
int Partie::getScore() const{              return this->score; }
int Partie::getNbBriqueRestante() const{   return this->nbBriqueRestante;}
int Partie::getNbBalleRestante() const{    return this->nbBalleRestante;}
bool Partie::getFinPartie() const{                  return this->finPartie;}
bool Partie::getErreur() const{            return this->erreur;}
int Partie::getNiveau() const{    return this->niveau;}


void Partie::setErreur(bool e){             this->erreur=e;}
void Partie::setNiveau(int n){          this->niveau = n;}
//Accesseurs en ecriture

void Partie::setNbBriqueRestante(int nb){
    this->nbBriqueRestante = nb;
}

void Partie::setFinPartie(bool fin){
    this->finPartie = fin;
}

void Partie::updateInfoPartie(){
    if(this->erreur == false){ // si il n'y a pas de message d'erreur à afficher on affiche ce message
        if(this->fenetreInfo->getCouleurFenetre() != WRED){
            this->fenetreInfo->setCouleurFenetre(WRED);
        }
        this->fenetreInfo->clear();
        this->fenetreInfo->print(0,0,"Niveau : "+std::to_string(this->niveau),WRED);
        this->fenetreInfo->print(30,0,"Balle  : "+std::to_string(this->nbBalleRestante),WRED);
        this->fenetreInfo->print(55,0,"Score  : "+std::to_string(this->score),WRED);
        if(nbBriqueRestante==0){
            setFinPartie(true);
        }
        
    }
}

void Partie::messageFinPartie(){
    if(this->erreur == false){ // si il n'y a pas de message d'erreur à afficher on affiche ce message
        this->fenetreInfo->clear(); // efface la fenêtre d'info
        this->fenetreInfo->setCouleurFenetre(BWHITE); // change le fond de la fenêtre d'info
        this->fenetreInfo->print(0,"Fin de la partie avec un score de "+std::to_string(this->score)+ " points",BWHITE);
    }
}

void Partie::messageErreur(std::string message){
    this->fenetreInfo->clear(); // efface la fenêtre d'info
    this->fenetreInfo->setCouleurFenetre(BWHITE); // change le fond de la fenêtre d'info
    this->fenetreInfo->print(0,message,BWHITE);
}

void Partie::messageFinNiveau(){
    if(this->erreur == false){ // si il n'y a pas de message d'erreur à afficher on affiche ce message
        this->fenetreInfo->clear(); // efface la fenêtre d'info
        this->fenetreInfo->setCouleurFenetre(BWHITE); // change le fond de la fenêtre d'info
        this->fenetreInfo->print(0,"Appuyez sur 's' pour accéder au niveau suivant.",BWHITE);
    }
}


// Méthode qui diminue nombre de balle
void Partie::balleSortieTerrain(const Window &fenetre, Balle &b){
    if(b.getY() == fenetre.getHauteur()-1){
        b.setRun(false);
        this->nbBalleRestante -=1;
        if(this->nbBalleRestante == 0){
            this->finPartie = true;
        }
    }
}

// Méthode qui ajoute un score au score de la partie
void Partie::ajouteScore(int s){
    this->score+=s;
}


