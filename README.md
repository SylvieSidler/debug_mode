# \debug_mode

## Sommaire 
- [Présentation générale](#pres)
    - [Téléchargement du jeu](#download)
    - [Lancement du jeu](#launch)
    - [Hidden quest for Mac users](#quest)
- [Presentation du monde](#world)
- [À propos](#about)
    - [Membres de l'équipe](#team)
    - [Origine du projet](#origin)

## Présentation générale <a id="pres"></a>

`\debug_mode` est un jeu vidéo 2D en vue à la 3e personne.

Incarnez Kiki la mygale, et partez à l'aventure pour reconstituer son monde perdu.

![image du menu start de \debug_mode](./IMAGES_README/startMenu_0.png "\debug_mode menu d'accueil") 


## Téléchargement du jeu <a id="download"></a>
Tout d'abord, téléchargez ou clonez ce projet sur votre ordinateur (don't worry there's no bugs... right ?). \
Pour pouvoir lancer le jeu, il vous faudra télécharger les librairies SDL nécessaires. (Oui, pour l'instant c'est manuel mais un jour ça sera automatique avec `make` !)

#### • Linux 
Utilisez apt pour installer chacune des différentes librairies : `sdl2`, `sdl2_image`, `sdl2_ttf` et `sdl2_mixer`.
``` shell
apt-get install lib<sdl2_package>-dev
```

#### • MacOS
Utilisez brew pour installer chacune des différentes librairies : `sdl2`, `sdl2_image`, `sdl2_ttf` et `sdl2_mixer`.
``` shell 
brew install <sdl2_package>
```
(Attention une quête cachée vous attend dans la suite !) 


#### • Windows 
```shell
[ERROR] > Cannot open source file debug_mode
``` 
Oups on dirait que le jeu n'est pas disponible T-T \
Nous vous conseillons de faire un dual-boot (ou mieux : passer sous Linux) et recommencer !


## Lancement du jeu  <a id="launch"></a>

Bravo vous avez réussi la première épreuve : le téléchargement !
Vous pouvez maintenant compiler et lancer le jeu avec `make run`. 

Pour lancer les tests unitaire, lancez `make test`, si des erreurs se produisent dans les tests, elles s'afficheront dans le terminal. 

## ! Si vous utilisez un Mac <a id="quest"></a>
Dans le fichier `GAME/src/define.h`, il faut modifier à la ligne 13 la définition de `FLAGS_RENDERER` par le flag en commentaire.

```C
#define FLAGS_RENDERER  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
```  
devient donc :  
``` c
#define FLAGS_RENDERER SDL_RENDERER_SOFTWARE
```
(Oui, pour l'instant c'est manuel mais un jour ça sera automatique !)

## Présentation du monde <a id="world"></a>

Le monde de Kiki a été détruit par un virus appelé SDL. \
Vous passez en ```debug_mode``` pour l'aider à reconstruire son monde. Il vous faudra ramener les murs, couleurs, etc. tout en mangeant les insectes sur votre route.

![Introduction avec les erreurs rencontrées lors de la programmation du jeu.](./IMAGES_README/cutscene_error.png "Erreurs lors du chargement des Aventures de Kiki") 
\* Toutes les erreures présentes dans l'intro et ce Readme ont été découvertes lors de la création du jeu ! \
Le tutoriel peut etre appelé à n'importe quel instant pour vous aider dans votre quête en appuyant sur la touche T : 

![](./IMAGES_README/Tuto_query.png "Tuto appelé à l'aide]")

## À propos <a id="about"></a>

### Membres de l'équipe <a id="team"></a>
- Olivia AING : <olivia.aing@telecomnancy.eu>
- Chloé BONINN : <chloe.boninn@telecomnancy.eu>
- Lise MANIÈRE : <lise.maniere@telecomnancy.eu>
- Sylvie SIDLER : <sylvie.sidler@telecomnancy.eu>
- Zoé VERNICOS : <zoe.vernicos@telecomnancy.eu>

**Cheffe de Projet** : Olivia Aing\
**Mainteneuse du projet** : Sylvie Sidler

### Origine du projet <a id="origin"></a>
Il s'agit d'un projet de fin de 1ère année à Télécom Nancy : la création d'un jeu vidéo en langage C utilisant la librairie SDL. \
\
*[NdMainteneur]* J'ai choisi de continuer ce projet sur mon temps libre pour essayer d'améliorer la démo initiale en un jeu plus complet.
