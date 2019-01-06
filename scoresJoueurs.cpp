#include "scoresJoueurs.h"


using namespace std;

ScoresJoueurs::ScoresJoueurs():nomFichierScoreJoueur("joueurs-scores.txt"){}

void ScoresJoueurs::lectureFichierScore(){
    ifstream fluxFichierLecture(this->nomFichierScoreJoueur);
    this->nbScore=0;
    string line;
    if(!fluxFichierLecture.is_open()){
        
        fluxFichierLecture.close();
        // on créer le fichier si il y'a un problème
        ofstream fluxFichierEcriture(this->nomFichierScoreJoueur);
        fluxFichierEcriture.close();
        
        ifstream fluxFichierLecture(this->nomFichierScoreJoueur);
        if(!fluxFichierLecture.is_open()){
            cout<<"Erreur lors de l'ouverture du fichier des scores"<<endl;
            
        }else{
            lectureFichierScore(); // si tout marche bien au bout on lance la fonction
        }
    }else{
        while(!fluxFichierLecture.eof()){
            if(!fluxFichierLecture.eof()){
                getline(fluxFichierLecture,line);
                size_t pos = line.find_first_of(" : ");
                this->tabJoueur[this->nbScore].nom = line.substr(0,pos);
                if((this->tabJoueur[this->nbScore].nom).size()>=1){
                    this->tabJoueur[this->nbScore].score = stoi(line.substr(pos+3)); //recupère seulement le nombre
                }
                this->nbScore++;
            }
        }
        fluxFichierLecture.close();
    }
    
}
void ScoresJoueurs::afficheScores(const Window &fenetre,int nbLigneScore, bool centre){
    lectureFichierScore();
    //affichage des meilleurs scores des joueurs
    fenetre.print(0," Meilleurs scores ",BWHITE);
    int imax;
    if(nbLigneScore<this->nbScore){
        imax = nbLigneScore;
    }else{
        imax = this->nbScore;
    }
    
    if(centre){
        for(int i=0;i<=imax;i++){
            if(tabJoueur[i].score !=0){ //verifie si il y a un joueur
                fenetre.print(i+2,this->tabJoueur[i].nom+" : "+to_string(this->tabJoueur[i].score)+" pts",WRED);
            }else{
                fenetre.print(i+2,"...",WRED);
            }
            
        }
    }else{
        for(int i=0;i<imax;i++){
            if(tabJoueur[i].score !=0){ //verifie si il y a un joueur
                fenetre.print(0,i+2,this->tabJoueur[i].nom+" : "+to_string(this->tabJoueur[i].score)+" pts",WRED);
            }else{
                fenetre.print(0,i+2,"...",WRED);
            }
            
        }
    }
    
}

void ScoresJoueurs::chargeScoreJoueurDansFichier(const Partie &partieJ){
    lectureFichierScore();
    fstream fluxFichier("joueurs-scores.txt");
    
    bool trouve = false;
    for(int i=0;i<this->nbScore;i++){
        if(tabJoueur[i].score !=0){
            if(this->tabJoueur[i].nom == partieJ.getNomJoueur()){
                trouve = true;
                if(tabJoueur[i].score <= partieJ.getScore()){
                    this->tabJoueur[i].score = partieJ.getScore();
                }
            }
        }
    }
    if(trouve == false){
        this->tabJoueur[this->nbScore].nom = partieJ.getNomJoueur();
        this->tabJoueur[this->nbScore].score = partieJ.getScore();
        this->nbScore++;
    }
    
    // On trie le tableau des scores des joueurs
    Joueur echange;
    for(int i=0;i<nbScore;i++){
        for(int j=0;j<nbScore;j++){
            if(i!=j){
                if(tabJoueur[i].score> tabJoueur[j].score){
                    echange = tabJoueur[i];
                    tabJoueur[i] = tabJoueur[j];
                    tabJoueur[j] = echange;
                }
            }
        }
    }
    
    //on remplie le fichier avec les scores triées
    for(int i=0;i<nbScore;i++){
        if(tabJoueur[i].score !=0){
            fluxFichier<<this->tabJoueur[i].nom<<" : "<<to_string(this->tabJoueur[i].score)<<endl;
        }
    }
    
    fluxFichier.close();
}

