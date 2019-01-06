#include "brique.h"

Brique::Brique(): x(-1), y(-1), size(6), resist(0){
    this->nbPoint = resist*10;
    updateCouleur();
}
Brique::Brique(int x, int y): x(x), y(y), size(6), resist(1){
    this->nbPoint = resist*10;
    updateCouleur();
}
Brique::Brique(int x, int y, int resist): x(x), y(y), size(6), resist(resist){
    this->nbPoint = resist*10;
    updateCouleur();
}
Brique::Brique(int x, int y, int size, int resist): x(x), y(y), size(size), resist(resist){
    this->nbPoint = resist*10;
    updateCouleur();
}

//accesseurs lecture
int Brique::getX() const{        return this->x; }
int Brique::getY() const{        return this->y; }
int Brique::getSize() const{     return this->size; }
Color Brique::getCouleur() const{   return this->couleur; }
int Brique::getResist() const{   return this->resist; }

//accesseurs écriture
void Brique::setX(int x){
    this->x = x;
}
void Brique::setY(int y){
    this->y = y;
}
void Brique::setResist(int r){
    this->resist = r;
}
void Brique::setSize(int s){
    this->size = s;
}


void Brique::init(Window &fenetre){
    if(this->resist !=0){
        afficher(fenetre);
    }
}

// met à jour la couleur de la brique en fonction de sa resistance
void Brique::updateCouleur(){
    switch (this->resist){
        case 1: this->couleur = WCYAN;
            break;
        case 2: this->couleur = WYELLOW;
            break;
        case 3: this->couleur = WGREEN;
            break;
        case 4: this->couleur = BMAGENTA;
            break;
        case 5: this->couleur = BBLUE;
            break;
        default:
            this->couleur = WBLACK;
            break;
    }
}

void Brique::update(Window &fenetre, Balle &b, Partie &part){
    if(this->resist != 0){
        if(estTouche(b)){ //si la brique est toucher par la balle
            b.direction(*this); //change direction de la balle en fonction de la brique
            this->resist -=1; //perd de la resitance
            updateCouleur();
            // on donne le score seulement quand la brique est detruite
            if(this->resist==0){
                part.ajouteScore(this->nbPoint);
            }
        }
    }else{
        clear(fenetre);  // la balle est morte et doit disparaitre
        // elle augmente le score du nombre de point indiquer
    }
    afficher(fenetre);
}

// renvoie vrai si la brique est toucher par la balle
bool Brique::estTouche(Balle &b){
    if(b.getX()==this->x-1 && b.getY()==this->y){ // si la balle se situe à gauche d'un obstacle
        if(b.getAngle() != Balle::angleDroit){ // correction d'un bug : quand la balle va tout droit vers le haut et qu'elle passe à coté d'une brique elle lui enlève 1 de resitance, il faut corrigé ça avec la condition là
            return true;
        }
    }else if(b.getX()==this->x+this->size && b.getY()==this->y){ // si la balle se situe à droite d'un obstacle
        if(b.getAngle() != Balle::angleDroit){// correction d'un bug : quand la balle va tout droit vers le haut et qu'elle passe à coté d'une brique elle lui enlève 1 de resitance, il faut corrigé ça avec la condition là
            return true;
        }
    }else if(b.getY() == this->y - 1 && (b.getX() > this->x - 1 && b.getX() < this->x + this->size)){ // si la balle se situe au dessus d'un obstacle
        return true;
    }else if(b.getY() == this->y + 1 && (b.getX() > this->x - 1 && b.getX() < this->x + this->size)){ // si la balle se situe en dessous d'un obstacle
        return true;
    }else if(b.getDirectionHaut() && b.getDirectionDroite() && (b.getX()==this->x-1 && b.getY()==this->y+1)){
        return true;
    }else if(!b.getDirectionHaut() && b.getDirectionDroite() && (b.getX()==this->x-1 && b.getY()==this->y-1)){
        return true;
    }else if(b.getDirectionHaut() && !b.getDirectionDroite() && (b.getX()==this->x+this->size && b.getY()==this->y+1)){
        return true;
    }else if(!b.getDirectionHaut() && !b.getDirectionDroite() && (b.getX()==this->x+this->size && b.getY()==this->y-1)){
        return true;
    }
    return false;
}
             
 void Brique::afficher(Window &fenetre) const{
     for(int i=0;i<this->size;i++){
        fenetre.print(this->x+i,this->y,' ',this->couleur);
     }
 }

 void Brique::clear(Window &fenetre) const{
     for(int i=0;i<this->size;i++){
         fenetre.print(this->x+i,this->y,' ');
     }
 }
             
             

