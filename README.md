# Projet Casse Brique 
----------------

**Groupe : 17**

**Fin du projet : 6 janvier 2019**

L’objectif de ce projet est la réalisation d’un « Casse Briques » en C++, permettant à un utilisateur (humain) de jouer dans un terminal Unix.

Un casse-briques se présente sous la forme d’un terrain (généralement une zone rectangulaire) sur lequel sont placées des briques (représentées par des rectangles), une raquette (symbolisée par une barre horizontale) et une balle. Les briques sont positionnées dans la partie haute du terrain et la raquette est positionnée en bas du terrain. Celle-ci peut être déplacée latéralement (par l’utilisateur), sans toutefois jamais sortir du terrain. La balle est initialement accolée sur le dessus de la raquette et une fois lancée (action de l’utilisateur), elle se déplace en ligne droite jusqu’à rencontrer un obstacle (bords gauche, supérieur et droit du terrain, une brique ou la raquette). La balle rebondit alors, ce qui change son orientation (et éventuellement sa vitesse). Si la balle rebondit sur une brique, la brique est abîmée et finit par se désagrèger (disparaître). Si la balle arrive au bord inférieur du terrain, alors celle-ci sort du terrain et est perdue.
L’objectif est donc de détruire toutes les briques, et cela avec un nombre de balles fini. Si le joueur n’a plus de balle, la partie est perdue. Lorsqu’il n’y a plus de brique sur un terrain, alors un nouveau terrain est proposé (qui peut-être plus compliqué – ou pas). Le score du joueur est calculé par rapport au nombre de briques démolies sur l’ensemble de la partie.

## Installation
----------------


> <u>Prérequis :</u> Assurez vous que la bibliothèque ncurses soit installé sur votre machine.
> Si ce n'est pas le cas, executez la commande suivande dans votre terminal pour l'installer 
>
> ```
>sudo apt-get install libncurses5-dev 
>```

Executez ensuite la commande suivante afin de créer l'executable du projet : 
```
make
```
> **Remarque :** si jamais une erreur est affiché, executez une nouvelle fois la commande

Une fois l'executable créé, vous pouvez lancer le programme :
```
./Casse-brique
```


## Les options
----------------

Les différentes options qu'il est possible passer dans le programme sont les suivantes : 

--help (-h) 	        Affiche l'aide du programme

--version (-v) 	        Affiche la version du programme 

--auteur (-a) 	        Affiche les noms des auteurs du programme 

--name (-n) <chaîne>	Nom du joueur qui va jouer au jeu 

```
./Casse-brique [option]
```


> **<u>Remarque :</u>** Si le nom du joueur n'est pas spécifié, le nom du joueur est par défault : player

## Auteurs
----------------

Le groupe est composé de : Timoléon Demas, Djamel Benameur, Matthieu Commins, Antoine Barbier