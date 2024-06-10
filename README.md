# \debug_mode

## Présentation générale

`\debug_mode` est un jeu vidéo 2D en vue à la 3e personne.

Incarnez Kiki l'araignée, et partez à l'aventure pour reconstituer son monde perdu.


![image du menu start de \debug_mode](./IMAGES_README/startMenu_0.png "\debug_mode start menu")

## Lancement du jeu 
Pour lancer le jeu, clonez ou télécharger ce projet sur votre ordinateur.
Vous pouvez maintenant compiler et lancer le jeu avec `make run` ou simplement le compiler avec `make`. 

Pour lancer les tests unitaire, lancez `make test`, si des erreurs se produisent dans les tests, elles s'afficheront dans le terminal. 

#### ! Si vous utilisez un Mac 
Dans le fichier `GAME/src/main.c`, il faut modifier à la première ligne la définition de `FLAGS_RENDERER` par le flag en commentaire : 

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

Le tutoriel peut etre appelé à n'importe quel instant pour vous aider dans votre quête en appuyant sur la touche T : 

![](./IMAGES_README/Tuto_query.png "Tuto appelé à l'aide]")

## About

**Membres du groupe :**
- Olivia AING <<olivia.aing@telecomnancy.eu>> 
- Chloé BONINN <<chloe.boninn@telecomnancy.eu>>
- Lise MANIÈRE <<lise.maniere@telecomnancy.eu>>
- Sylvie SIDLER <<sylvie.sidler@telecomnancy.eu>>
- Zoé VERNICOS <<zoe.vernicos@telecomnancy.eu>>

