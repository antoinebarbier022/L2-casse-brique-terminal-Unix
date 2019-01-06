#include "balle.h"

// constructeur
Balle::Balle(): x(0),y(0),angle(angleDiagonale), haut(true), droite(true),caractere('@'), couleur(WBLACK), run(false){}

Balle::Balle(char caract): x(0),y(0),angle(angleDiagonale), haut(true), droite(true),caractere(caract), couleur(WBLACK), run(false){}

Balle::Balle(char caract, Color coul): x(0),y(0),angle(angleDiagonale), haut(true), droite(true),caractere(caract), couleur(coul), run(false){}

// accesseur en lecture
int Balle::getX() const {               return this->x; }
int Balle::getY() const{                return this->y; }
Balle::degree Balle::getAngle() const { return this->angle; }
bool Balle::getDirectionHaut() const{   return this->haut;}
bool Balle::getDirectionDroite() const{ return this->droite;}
char Balle::getCaractere() const{     return this->caractere; }
Color Balle::getCouleur() const{      return this->couleur; }
bool Balle::getRun() const{           return this->run; }

//accesseur écriture
void Balle::setDirectionHaut(bool h){   this->haut = h; }
void Balle::setDirectionDroite(bool d){ this->droite = d; }
void Balle::setAngle(degree a){         this->angle = a; }
void Balle::setCaractere(char c){       this->caractere = c; }
void Balle::setCouleur(Color c){        this->couleur = c; }
void Balle::setRun(bool r){             this->run = r; }


void Balle::init(const Window &fenetre,const Raquette &r){
    clear(fenetre);
    this->x = r.getX()+r.getSize()/2; // au milieu de la raquette
    this->y = r.getY()-1; // sur la ligne au dessus de la raquette
    afficher(fenetre);
}

void Balle::lancerBalle(int toucheClavier){
    if(toucheClavier == ' '){
        this->run = true;
    }
}

void Balle::update(const Window &fenetre, const Raquette &r){
    
    // changement de direction
    direction(fenetre);
    direction(r);
    //change angle de la balle
    r.changeBalleAngle(*this);
    // on efface l'ancienne position de la balle dans la fenetre
    clear(fenetre);
    // changement de position en fonction de la direction
    deplacement();
    // on affiche la nouvelle position de la balle dans la fenetre
    afficher(fenetre);
}

void Balle::direction(const Window &fenetre){
    //on change la direction de la balle si :
    if(this->x >= fenetre.getLargeur()-1){ // si touche bord droit
        this->droite = false;
    }
    if(this->x <= 0){ // si la balle se situe contre le bord gauche de la fenêtre
        this->droite = true;
    }
    if(this->y >= fenetre.getHauteur()-1){ // si la balle se situe contre le bord en bas de la fenêtre
        this->haut = true;
    }
    if(this->y <= 0){ // si la balle se situe contre le bord en haut de la fenêtre
        this->haut = false;
    }
}


void Balle::direction(const Brique &br){
    if(this->x == br.getX()-1 && this->y == br.getY()){ // si la balle se situe à gauche d'un obstacle
        if(this->angle != Balle::angleDroit){ // correction d'un bug : quand la balle va tout droit vers le haut et qu'elle passe à coté d'une brique elle lui enlève 1 de resitance, il faut corrigé ça avec la condition là
            this->droite = false;
        }
    }else if(this->x == br.getX()+br.getSize() && this->y == br.getY()){ // si la balle se situe à droite d'un obstacle
        if(this->angle != Balle::angleDroit){// correction d'un bug : quand la balle va tout droit vers le haut et qu'elle passe à coté d'une brique elle lui enlève 1 de resitance, il faut corrigé ça avec la condition là
            this->droite = true;
        }
    }else if(this->y == br.getY() - 1 && (this->x > br.getX() - 1 && this->x < br.getX() + br.getSize() )){ // si la balle se situe au dessus d'un obstacle
        this->haut = true;
    }else if(this->y == br.getY() + 1 && (this->x > br.getX() - 1 && this->x < br.getX() + br.getSize() )){ // si la balle se situe en dessous d'un obstacle
        this->haut = false;
    }else if(this->haut && this->droite && (this->x == br.getX()-1 && this->y == br.getY() + 1)){
        this->haut = false;
        this->droite = false;
    }else if(!this->haut && this->droite && (this->x == br.getX()-1 && this->y == br.getY() - 1)){
        this->haut = true;
        this->droite = false;
    }else if(this->haut && !this->droite && (this->x == br.getX() + br.getSize() && this->y == br.getY() + 1)){
        this->haut = false;
        this->droite = true;
    }else if(!this->haut && !this->droite && (this->x == br.getX() + br.getSize() && this->y == br.getY() - 1)){
        this->haut = true;
        this->droite = true;
    }
    // cas particulier
    // si l'angle de la balle est en diagonal alors il faut effectué d'autre test car elle se déplace de 2 cases vers la gauche ou la droite et non une case
    if(this->angle == angleDiagonale){
        if(this->haut && this->droite && (this->x == (br.getX()-1 || br.getX()-2 ) && this->y == br.getY() + 1)){
            this->haut = false;
            this->droite = false;
        }else if(!this->haut && this->droite && (this->x == (br.getX()-1 || br.getX()-2) && this->y == br.getY() - 1)){
            this->haut = true;
            this->droite = false;
        }else if(this->haut && !this->droite && (this->x == (br.getX() + br.getSize() || br.getX() + br.getSize()+1) && this->y == br.getY() + 1)){
            this->haut = false;
            this->droite = true;
        }else if(!this->haut && !this->droite && (this->x == (br.getX() + br.getSize() || br.getX() + br.getSize()+1) && this->y == br.getY() - 1)){
            this->haut = true;
            this->droite = true;
        }
    }

    
}

void Balle::direction(const Raquette &r){
    if(this->y == r.getY() - 1 && (this->x >= r.getX() - 1 && this->x <= r.getX() + r.getSize() )){
        this->haut = true;
    }else if(this->y == r.getY() + 1 && (this->x >= r.getX() - 1 && this->x <= r.getX() + r.getSize() )){
        this->haut = false;
    }else if(this->x == r.getX() - 1 && this->y == r.getY() ){
        this->droite = false;
    }else if(this->x == r.getX() + r.getSize() && this->y == r.getY() ){
        this->droite = true;
    }
}

void Balle::deplacement(){
    int ang;
    switch(this->angle){
        case angleDroit:
            ang = 0; // on déplace x de 0 donc le déplacement est verticale
            break;
        case angleIncline:
            ang = 1;
            break;
        case angleDiagonale:
            ang = 2;
            break;
        default:
            ang = 1;
    }
    //on change les coordonnées de la balle en fonction des infos de directions
    if(this->droite && this->haut){         // si direction => en haut à droite
        this->x+=ang; this->y--;
    }else if(!this->droite && !this->haut){ // si direction => en bas à gauche
        this->x-=ang; this->y++;
    }else if(!this->droite && this->haut){  // si direction => en haut à gauche
        this->x-=ang; this->y--;
    }else{                          // si direction => en bas à droite
        this->x+=ang; this->y++;
    }
}

//methodes d'affichage sur le jeu
void Balle::afficher(const Window &fenetre) const{
    fenetre.print(this->x,this->y,this->caractere, this->couleur);
}

void Balle::clear(const Window &fenetre) const{
    fenetre.print(this->x,this->y,' ');
}
