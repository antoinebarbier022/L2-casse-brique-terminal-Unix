#include "raquette.h"


Raquette::Raquette(const Window &fenetre){
    this->size = 10;
    this->x = fenetre.getLargeur()/2 - this->size/2;
    this->y = fenetre.getHauteur()-2; //on place la Raquette à deux cases au dessus du bas de la fenêtre
    this->couleur = fenetre.getCouleurBordure();
}
Raquette::Raquette(const Window &fenetre, int size){
    this->size = size;
    this->x = fenetre.getLargeur()/2 - this->size/2;
    this->y = fenetre.getHauteur()-3; //on place la Raquette à deux cases au dessus du bas de la fenêtre
    this->couleur = fenetre.getCouleurBordure();
}
    
//accesseurs lecture
int Raquette::getX() const {    return this->x; }
int Raquette::getY() const {    return this->y; }
int Raquette::getSize() const { return this->size; }

//accesseurs écriture
void Raquette::setX(int x){      this->x = x; }
void Raquette::setY(int y){      this->y = y; }
void Raquette::setSize(int s){   this->size = s; }

void Raquette::update(const Window &fenetre, int toucheClavier){
    switch (toucheClavier) {
        case KEY_RIGHT:
            clear(fenetre);
            moveRight(5,fenetre); // 5 est le nombre de case déplacer dans la direction
            afficher(fenetre);
            break;
        case KEY_LEFT:
            clear(fenetre);
            moveLeft(5,fenetre); // 5 est le nombre de case déplacer dans la direction
            afficher(fenetre);
            break;
        default:
            break;
    }
}

void Raquette::changeBalleAngle(Balle &b) const{
    //Avant de changer l'angle, on change la direction de la balle en fonction de si elle à toucher la partie droite ou gauche de la raquette
    //on regarde si la balle est sur la raquette
    if((b.getY() == this->y-1) && (b.getX() >= this->x && b.getX() <= this->x+this->size)){
        //si la balle est dans la moitié gauche de la raquette
        if(b.getX() <= this->x + this->size/2){
            b.setDirectionDroite(false); // la balle se dirige vers la gauche
        }else{
            b.setDirectionDroite(true); // la balle se dirige vers la droite
        }
    }
    
    int div = 3;
    /*
    if(this->size > 10){
        div = 5;
        div = 3;
    }else{
        div = 3;
    }*/
    int part = this->size/div; // raquette découpé en 6 partie
    if((b.getY() == this->y-1) && (b.getX() >= this->x && b.getX() <= this->x+this->size )){
        if(b.getX() <= this->x + part){ //première partie de la raquette
            b.setAngle(rand()%2 ? Balle::angleIncline : Balle::angleDiagonale);
        }else if( (b.getX() >= this->x + part) && (b.getX() <= this->x + part*2)){ //milieu de la raquette
            b.setAngle(rand()%2 ? Balle::angleIncline : Balle::angleDroit);
        }else{//3eme partie de la raquette
            b.setAngle(rand()%2 ? Balle::angleIncline : Balle::angleDiagonale);
        }
    }
}

//méthodes pour le déplacement de la Raquette
void Raquette::moveLeft(int speed, const Window &fenetre){
    if(this->x > 0){
        this->x -= speed;
        
        if(this->x <= 0){
            this->x = 0;
        }
    }
}
void Raquette::moveRight(int speed, const Window &fenetre){
    if(this->x + this->size < fenetre.getLargeur()){
        this->x += speed;
        // on revérifit tout de suite si la position x n'est pas en dehors de la fenêtre
        if(this->x + this->size > fenetre.getLargeur()){
            this->x =fenetre.getLargeur() - this->size;
        }
    }
}

void Raquette::clear(const Window &fenetre) const{
    for(int i=0;i<this->size;i++){
        fenetre.print(this->x+i,this->y,' ');
    }
}

void Raquette::afficher(const Window &fenetre) const{
    for(int i=0;i<this->size;i++){
        fenetre.print(this->x+i,this->y,' ',this->couleur);
    }
}

