#include "casseBrique.h"

using namespace std;

CasseBrique::CasseBrique(std::string nomJ):titre("Casse Brique"), version("version 0"),  anneeLicenceEtudiant("Licence 2"), nomJoueur(nomJ){
    
    // On charge les options disponible
    opts.addOption(Option(HELP_ID, "--help", "-h","Affiche l'aide du programme", Option::AUCUN));
    opts.addOption(Option(VERSION_ID, "--version", "-v","Affiche la version du programme", Option::AUCUN));
    opts.addOption(Option(AUTEUR_ID, "--auteur", "-a","Affiche les noms des auteurs du programme", Option::AUCUN));
    opts.addOption(Option(PLAYER_ID, "--name", "-n","Nom du joueur qui va jouer au jeu", Option::CHAINE));
}


CasseBrique::Choix CasseBrique::parseOptions(int argc, char** argv){
    bool opt_error = false;
    int i = 1;
    while (!opt_error && i < argc) {
        int x = opts.getOptionId(argv[i]);
        switch (x) {
            case HELP_ID:
                cout << "usage " << argv[0] << " [Options]" << endl;
                opts.print();
                return CasseBrique::QUITTER; // sort du programme
            case VERSION_ID:
                cout << "Programme " << argv[0] << " version 0.0.0" << endl;
                return CasseBrique::QUITTER; // sort du programme
            case AUTEUR_ID:
                cout << "Les auteurs du programme " << argv[0] << " :" << endl;
                cout << " Antoine Barbier\n Timoléon Demas\n Matthieu Commins\n Djamel Benameur"<< endl;
                return CasseBrique::QUITTER; // sort du programme
            case PLAYER_ID:
                if(argc == 2){
                    cout << "\n\033[33mCette option n'a pas été reconnue, il manque le nom du joueur\033[0m"<<endl;;
                    opt_error = true;
                    return CasseBrique::QUITTER;
                }else{
                    this->nomJoueur = argv[2];
                    return CasseBrique::AUCUN;
                }

            default:
                if (opts.optionHasArgument(argv[i])) {
                    cout << "L'option " << argv[i] << " a été trouvée.";
                    cout << " Elle attend un argument de type "
                    << Type2String(opts.optionArgumentType(argv[i]));
                    cout << " => " << (++i < argc ? argv[i] : "Erreur");
                } else {
                    cout << "\033[33mCette option n'a pas été reconnue.\033[0m";
                    opt_error = true;
                }
                cout << endl;
            }
        i++;
    }
    if (opt_error) {
        cout << "Usage : " << argv[0] << " [Options]" << endl;
        opts.print();
        terminate();
    }
    return CasseBrique::AUCUN;
}


CasseBrique::Choix CasseBrique::afficheFenetre(std::string nomFichier){
    
    Window fenetre(HAUTEUR,LARGEUR,1,1,' ');
    fenetre.setCouleurBordure(BWHITE);// couleur de la bordure de la fenêtre du jeu
    fenetre.setCouleurFenetre(WRED);
    
    ifstream fichier(nomFichier);
    if ( fichier.is_open() ){ // ce test échoue si le fichier n'est pas ouvert
        string ligne;
        int debutTexte = 3;
        int numLigne = debutTexte;
        int nbLigne = 0;

        
        // affiche le texte dans la fenetre jusqu'a la hauteur max de la fenetre
        debutTexte = (HAUTEUR/2)-(nbLigne/2);
        while(numLigne < HAUTEUR- debutTexte){
            getline(fichier,ligne);
            fenetre.print(numLigne,ligne,fenetre.getCouleurFenetre());
            numLigne++;
        }
        fichier.close();
    } else {
        fenetre.print(HAUTEUR/2,"Erreur d'ouverture du fichier "+nomFichier,fenetre.getCouleurFenetre());
    }
    
    // la suite permet la detection des touches du clavier
    while(true){
        int ch = getch();
        if(ch == 10) // si touche entrer est pressé
            return CasseBrique::MENU; // on retourne au menu
        // detection touche racourcie clavier
        CasseBrique::Choix choixAction = toucheChangementFenetre(ch);
        if(choixAction != CasseBrique::AUCUN){
            return choixAction;
        }
    }
}

CasseBrique::Choix CasseBrique::toucheChangementFenetre(int toucheClavier){
    switch (toucheClavier) {
        case 'q':
        case 'Q':
            return CasseBrique::QUITTER;
            break;
        case 'r': //pour recommencer
            return CasseBrique::RECOMMENCER;
            break;
        case 'm': //pour retourner au menu
            return CasseBrique::MENU;
            break;
        case 'h': //pour afficher l'aide
            return CasseBrique::QUITTER;
            //return CasseBrique::AIDE;
            break;
        case 'j': //pour afficher l'aide
            return CasseBrique::JOUER;
            break;
        default:
            return CasseBrique::AUCUN;
            break;
    }
}



//fenetre principale du menu
CasseBrique::Choix CasseBrique::menu(){
    Window menu(HAUTEUR,LARGEUR,1,1,' ');
    menu.setCouleurBordure(BWHITE);// couleur de la bordure de la fenêtre du jeu
    menu.setCouleurFenetre(BRED);
    
    Window texteMenu(5,30,LARGEUR/2-15+1,3,' ');
    texteMenu.setCouleurBordure(BRED);
    texteMenu.setCouleurFenetre(BWHITE);
    
    //affichage des info sur le jeu
    texteMenu.print(1,this->titre, BWHITE);
    texteMenu.print(2,this->version, BWHITE);
    texteMenu.print(3,this->anneeLicenceEtudiant, BWHITE);
    
    // affichage des actions
    const int nbAction = 6;
    const int debEmplacementAction = 12;

    string texteAction[nbAction] = {" Jouer "," Voir les scores "," Noms des auteurs "," Aide "," Quitter "};
    for(int i=0;i<nbAction;i++){
        menu.print(debEmplacementAction+i,texteAction[i], WRED);
    }
    
    int i=0;
    int precI=1;
    int ch;
    bool sortiePrg = false; // booleen pour sortir du programme
    while(!sortiePrg){
        ch = getch();
        
        menu.print(debEmplacementAction+precI,texteAction[precI], WRED); // effacer l'affichage de l'ancien option selectionner
        menu.print(debEmplacementAction+i,texteAction[i], BWHITE); // couleur de selection
        
        
        // detect touche du clavier, par exemple si on appuie sur 'q', cela return CasseBrique::QUITTER
        CasseBrique::Choix choixAction = toucheChangementFenetre(ch);
        if(choixAction != CasseBrique::AUCUN){
            return choixAction;
        }
        
        
        switch(ch){
            case KEY_DOWN:
                precI = i;
                i= (i==(nbAction-1) ? 0 : i+1);
                break;
            case KEY_UP:
                precI = i;
                i= (i==0 ? nbAction-1 : i-1);
                break;
                
                //on peut utiliser deux touche pour selectionner le choix
            case ' ': // touche espace
            case 10: // 10 est la touche espace
                switch (i) {
                    case 0: return CasseBrique::JOUER; break; // JOUER
                    case 1: return CasseBrique::VOIRSCORES; break; // VOIR LES SCORES
                    case 2: return CasseBrique::NOMSAUTEURS; break; // Noms des auteurs
                    case 3: return CasseBrique::AIDE; break; // AIDE
                    case 4: return CasseBrique::QUITTER; break; // QUITTER
                    default: break;
                }
                break;
            case 'q':
            case 'Q':
                sortiePrg = true;
                break;
            default:
                break;
        }
    } // pour sortir du menu : touche espace ou touche q
    return CasseBrique::QUITTER;
}



CasseBrique::Choix CasseBrique::jeu(){
    //chevauchement des bordures des fenêtres
    Window fenInfoDroite(HAUTEUR,20,LARGEUR - 18,1,' '); // fenetre info de droite
    Window fenInfoPartie(1,LARGEUR-fenInfoDroite.getLargeur(),1,1,' '); // fenetre info situer au dessus du jeu
    Window fenetreJeu(HAUTEUR-2,LARGEUR- fenInfoDroite.getLargeur(),1,3,' ');
    
    fenetreJeu.setCouleurBordure(BRED);    // couleur de la bordure de la fenêtre du jeu
    fenetreJeu.setCouleurFenetre(BWHITE); // couleur de la fenêtre du jeu
    
    fenInfoDroite.setCouleurBordure(fenetreJeu.getCouleurBordure());
    fenInfoDroite.setCouleurFenetre(fenetreJeu.getCouleurBordure());
    
    fenInfoPartie.setCouleurBordure(fenetreJeu.getCouleurBordure());
    fenInfoPartie.setCouleurFenetre(fenetreJeu.getCouleurBordure());
    
    // Texte d'information
    fenInfoDroite.print(fenInfoDroite.getHauteur()-5,"Menu  : 'm'",WRED);
    fenInfoDroite.print(fenInfoDroite.getHauteur()-4,"Recommencer  : 'r'",WRED);
    
    //affiche le top 5 des meilleurs joueurs dans la fenetre droite
    ScoresJoueurs scores;
    scores.afficheScores(fenInfoDroite,5, false); //pas centré dans la fenetre
    
    
    Balle balle('@');                    //création de la balle
    Raquette raquette(fenetreJeu, 20);  //création de la raquette
    int vitesseRaquette = 5;
    
    Partie partie(this->nomJoueur, fenInfoPartie); // on créer une partie
    
    PopBrique terrain(fenetreJeu);
    


    //terrain.generationAuto();
    
    bool finPartie;
    int ch;
    int nbNiveau = 5;
    partie.setNiveau(0);
    string niveau = "Niveaux/niveau";
    
    int temps = 90000;
    // début de la boucle du jeu
    while(partie.getNiveau() < nbNiveau) {
        finPartie = false;
        balle.init(fenetreJeu,raquette);
        niveau.append(std::to_string(partie.getNiveau()));
        niveau.append(".cfg");

        terrain.lireNiveau(niveau,partie);
        terrain.afficher(fenetreJeu); //affichage de la terrain
        balle.setRun(false);
        while(!finPartie) {
            ch = getch();
            if(balle.getAngle()==Balle::angleDiagonale){
                temps = 130000;
            }else{
                temps = 90000;
            }
            usleep(temps); // pause dans la boucle pour permettre de voir l'affichage de la balle
            
            
            // lance la balle si la touche correspond au lancer de balle
            if(partie.getErreur() == false){ // si pas d'erreur on lance la balle
                balle.lancerBalle(ch);
            }
            
            // Mise à jour des informations de la partie dans la fenêtre en haut du jeu
            // la balle, le score, le niveau
            partie.updateInfoPartie();
            // si le nombre de balle est égale à 0 : on remet à 0 le score et le nombre de balle et on affiche le message de fin
            if(!balle.getRun()){ // si la balle n'est pas lancé
                //on affiche la raquette sur le terrain
                raquette.afficher(fenetreJeu);
                 // la balle est initialisé sur la raquette
                balle.init(fenetreJeu,raquette);
            }else{
                // l'appel de la méthode suivante permet de detecter si la balle sort du terrain, alors pour la balle : run = false
                partie.balleSortieTerrain(fenetreJeu, balle);
                // mise à jour de la population de briques
                // si jamais la balle touche une brique elle change de sens
                terrain.update(fenetreJeu, balle, partie);
                // mise à jour de la balle
                // detection bordure de la fenêtre, de la raquette ...
                // efface l'ancienne position et affiche la nouvelle
                balle.update(fenetreJeu, raquette);
            }
            
            //modification de la position de la raquette
            //récupère la touche appuyé au clavier
            raquette.update(fenetreJeu,ch);
            
            // si jamais la balle c'est arrété, on l'initialise tout de suite sur la raquette car le usleep qui arrive après causerai un mauvaise affichage
            if(!balle.getRun()){
                balle.init(fenetreJeu, raquette);
            }
            
            //Si une touche du clavier à été appuyer : on entre dans le switch et on return l'action voulut
            // detect touche du clavier, par exemple si on appuie sur 'q', cela return CasseBrique::QUITTER
            CasseBrique::Choix choixAction = toucheChangementFenetre(ch);
            if(choixAction != CasseBrique::AUCUN){
                scores.chargeScoreJoueurDansFichier(partie); //charge score joueur dans le fichier
                return choixAction;
            }

            if(partie.getFinPartie()){
                //iNiveau++;
                partie.setNiveau(partie.getNiveau()+1);
                partie.setNiveau(partie.getNiveau());
                if(terrain.getNbBriqueRestante() == 0 && partie.getNiveau() < nbNiveau) {
                    partie.messageFinNiveau();
                    while(ch != 'q' || ch  != 's'){
                        ch = getch();
                    // detect touche du clavier, par exemple si on appuie sur 'q', cela return CasseBrique::QUITTER
                        if(ch == 'q') {
                            CasseBrique::Choix choixAction = toucheChangementFenetre(ch);
                            if(choixAction != CasseBrique::AUCUN){
                                return choixAction;
                            }
                        }
                        if(ch == 's') {
                         break;
                        }
                    }
                }
                else if(partie.getNiveau() == nbNiveau) {
                    partie.messageFinPartie();
                    finPartie = true;
                    while((ch = getch()) != 'q') {
                        CasseBrique::Choix choixAction = toucheChangementFenetre(ch);
                        if(choixAction != CasseBrique::AUCUN)
                            return choixAction;
                    }
                }
                else {
                    partie.messageFinPartie(); //affiche le message de fin de partie
                    while(ch != 'q' || ch != 's'){
                        ch = getch();
                        // detect touche du clavier, par exemple si on appuie sur 'q', cela return CasseBrique::QUITTER
                        if(ch == 'q') {
                            CasseBrique::Choix choixAction = toucheChangementFenetre(ch);
                            if(choixAction != CasseBrique::AUCUN){
                                return choixAction;
                            }
                        }
                        if(ch == 's') {
                            break;
                        }
                    }
                }
                niveau = "Niveaux/niveau";
                finPartie = true;
                partie.setFinPartie(false);
            }
        }
    }
    scores.chargeScoreJoueurDansFichier(partie);
    return CasseBrique::QUITTER; //quitter le jeu
}

