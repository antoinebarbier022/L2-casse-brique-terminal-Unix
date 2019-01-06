#include "popBrique.h"

using namespace std;

PopBrique::PopBrique(const Window &fenetre){
    this->debutTerrainX = 2;
    this->debutTerrainY =2;
    this->tailleTerrainPopHauteur = fenetre.getHauteur()-13;    // on enlève la partie ou il n'y aura pas de brique (au dessus de la raquette)
    this->tailleTerrainPopLargeur = fenetre.getLargeur() - debutTerrainX*2; // on enleve les bordures où il n'y aura pas de brique
}

int PopBrique::getNbBriqueTotal() const{        return this->nbBriqueTotal; }
int PopBrique::getNbBriqueRestante() const{     return this->nbBriqueRestante; }


//void PopBrique::ajouterBrique(Brique &br){}

void PopBrique::generationAuto(){
    this->nbBriqueTotal = 70;
    this->nbBriqueRestante = this->nbBriqueTotal;
    int pointX = debutTerrainX;
    int pointY = debutTerrainY;
    bool finAjoutBrique = false;
    
    // création des briques
    int e=0;
    int tailleBrique = 2;
    while(e<nbBriqueTotal && !finAjoutBrique){
        if(pointX + tailleBrique > this->tailleTerrainPopLargeur){// si la brique ce situe en dehors de la zone
            pointX = debutTerrainX; // on re initialise le x de la zone
            pointY += 2; // on saute une ligne
        }
        if(pointY + 1 >= tailleTerrainPopHauteur + debutTerrainY){ // si la prochaine brique sort de la zone en hauteur (le + 1 est la hauteur de la brique)
            finAjoutBrique = true; // on arrête l'ajout de brique
        }else{ // sinon on créer une brique
            population[e]=Brique(pointX, pointY, tailleBrique, 1 ); // on créer une brique
            this->nbBriqueRestante +=1;
        }
        pointX += tailleBrique+2; // espace entre les brique
        e++;
    }
    this->nbBriqueRestante = this->nbBriqueTotal;
}


void PopBrique::update(Window &fenetre, Balle &b, Partie &part){
    for(int i=0;i<nbBriqueTotal;i++){
        if(population[i].estTouche(b)){ // si la brique est touché
            if(population[i].getResist() ==1){
                this->nbBriqueRestante -=1;
            }
            population[i].update(fenetre,b,part);
        }
    }
    part.setNbBriqueRestante(this->nbBriqueRestante);
    //cout << this->nbBriqueRestante;
}


void PopBrique::afficher(Window &fenetre) const{
    for(int i=0;i<nbBriqueTotal;i++){
        if(population[i].getResist() !=0){
            population[i].afficher(fenetre);
        }else{
            population[i].clear(fenetre);
        }
    }
}



bool PopBrique::collision(int x, int y, int size,Partie &part)
{
    bool res = false;
    int i = 0;
    while(i < nbBriqueTotal && res == false) {
        if(x+size >= population[i].getX() && x <= population[i].getX()+population[i].getSize()) {
            if(y == population[i].getY()) {
                res = true;
                //cerr << "x+size: " << x+size << " population[i].getX(): " << population[i].getX() << " | x: " << x << " getX+getS: " << population[i].getX()+population[i].getSize() << endl;
            }
        }
        i++;
        /*else if(y >= population[i].getY() && y <= population[i].getY()+population[i].getSize())
         res = true;*/
    }
    if(res == true){
        part.setErreur(true);
        part.messageErreur("Impossible de placer la brique de taille "+to_string(size)+" à la position ("+to_string(x)+","+to_string(y)+").");
        
    }
    return res;
}

void PopBrique::nettoyer(string &s)
{
    size_t pos=s.find_first_of("#");
    s=s.substr(0,pos);
    int beg=0,end=s.size()-1;
    while(beg<end+1 && (s[beg]==' ' || s[beg]=='\t' )) beg++;
    while(end>beg-1 && (s[end]==' ' || s[end]=='\t' )) end--;
    s=s.substr(beg,end-beg+1);
}

bool PopBrique::cleValeur(string &s, string &s1, string &s2, Partie &part)
{
    nettoyer(s);
    if (s==string(""))
        return false;
    size_t pos=s.find_first_of(":");
    if (pos==string::npos) {
        part.setErreur(true);
        part.messageErreur("Le fichier est mal formé");
    }
    s1=s.substr(0,pos);
    s2=s.substr(pos+1);
    nettoyer(s1);
    nettoyer(s2);
    return true;
}

bool PopBrique::lireNiveau(string nom_fichier,Partie &part)
{
    this->nbBriqueTotal = 0;
    this->nbBriqueRestante = 0;
    ifstream input(nom_fichier.c_str());
    string cle, valeur;
    if (!input.is_open()) {
        part.setErreur(true);
        part.messageErreur("Le fichier "+nom_fichier+" n'a pas pu être ouvert.");
        return false;
    }
    string line;
    int x, y, res, size;
    size_t pos, num_ligne;
    size_t i = 0;
    while(!input.eof()) {
        getline(input, line);
        if(cleValeur(line, cle, valeur, part)) {
            if(cle == "Taille") {
                size = atoi(valeur.c_str());
            }
            else if(cle == "Position") {
                pos = valeur.find_first_of("x, ");
                if (pos == string::npos || valeur[pos] == '\0') {
                    part.setErreur(true);
                    part.messageErreur("Le fichier est mal formé. Vérifiez la syntaxe de la ligne ");
                    return false;
                }
                else {
                    x = atoi(valeur.substr(0, pos).c_str());
                    y = atoi(valeur.substr(pos+1).c_str());
                    //cerr << "x: " << x << ", y: "<< y << endl;
                }
            }
            else if(cle == "Resistance") {
                res = atoi(valeur.c_str());
                if(nbBriqueTotal == 0) {
                    if(size==1){size=6;}
                    population[i] = Brique(x, y, size, res);
                    nbBriqueTotal++;
                }
                else {
                    if(collision(x, y, size, part) == false) {
                        population[i] = Brique(x, y, size, res);
                        nbBriqueTotal++;
                    }
                }
                x = 0; y = 0; res = 0; size = 0;
                i++;
            }
        }
        num_ligne++;
    }
    input.close();
    nbBriqueRestante = nbBriqueTotal;
    part.setNbBriqueRestante(this->nbBriqueTotal);
    return true;
}


