# \debug_mode

## Présentation générale

`\debug_mode` est un jeu vidéo 2D en vue à la 3e personne.

Incarnez Kiki l'araignée, et partez à l'aventure pour reconstituer son monde perdu.

![image du menu start de \debug_mode](./IMAGES_README/startMenu_0.png "\debug_mode menu d'accueil") 


## Téléchargement du jeu 
Tout d'abord, téléchargez ou clonez ce projet sur votre ordinateur (promis il n'y a pas d'insectes... n'est-ce pas ?). 
Pour pouvoir lancer le jeu, il vous faudra téléchargez les librairies sdl nécessaires :

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
ERROR
``` 

Oups on dirait que le jeu n'est pas disponible T-T \
Nous pous conseillons de faire un dualboot (ou mieux : passer sous Linux) et recommencer !


## Lancement du jeu

Bravo vous avez réussi la première épreuve : le téléchargement !
Vous pouvez maintenant compiler et lancer le jeu avec `make run`. 

Pour lancer les tests unitaire, lancez `make test`, si des erreurs se produisent dans les tests, elles s'afficheront dans le terminal. 

### ! Si vous utilisez un Mac 
Voici votre ordre de mission "side_quest" : 
Dans le fichier `GAME/src/main.c`, il faut modifier à la première ligne la définition de `FLAGS_RENDERER` par le flag en commentaire.

```C
#define FLAGS_RENDERER  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
```  
devient donc :  
``` c
#define FLAGS_RENDERER SDL_RENDERER_SOFTWARE
```

## Presentation du monde 

Le monde de Kiki a été détruit par un virus appelé SDL. Vous passez donc en ```debug_mode```pour l'aider à reconstruire son monde.
Il vous faudra ramener les murs, couleurs, etc. tout en mengeant les insectes sur votre route.

![Introduction avec les erreurs rencontrées lors de la programmation du jeu.](./IMAGES_README/cutscene_error.png "Erreurs lors du chargement des Aventures de Kiki") 
\* Toutes les erreures présentes dans l'intro et ce Readme ont été découvertes lors de la création du jeu ! \
Le tutoriel peut etre appelé à n'importe quel instant pour vous aider dans votre quête en appuyant sur la touche T : 

![](./IMAGES_README/Tuto_query.png "Tuto appelé à l'aide]")

## About

**Membres du groupe :**
- Olivia AING <<olivia.aing@telecomnancy.eu>> 
- Chloé BONINN <<chloe.boninn@telecomnancy.eu>>
- Lise MANIÈRE <<lise.maniere@telecomnancy.eu>>
- Sylvie SIDLER <<sylvie.sidler@telecomnancy.eu>>
- Zoé VERNICOS <<zoe.vernicos@telecomnancy.eu>>


