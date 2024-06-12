/*Ajout des bibliothèques*/
#include "./plugins/sprite.h"
#include "./plugins/startMenu.h"
#include "./plugins/carte.h"
#include "./plugins/terminal.h"
#include "./plugins/window_display.h"
#include "./plugins/story_event.h"
#include "./plugins/astar.h"
#include "./plugins/fileprio.h"
#include "./plugins/pouvoir_carte.h"
#include "./define.h"


int main(void) {
    int status = EXIT_FAILURE ;
    SDL_Window* pWindow = NULL ;
    SDL_Renderer* pRenderer = NULL ;
    // SDL_Surface *surfaceSprite =NULL;

    SDL_Texture* texture = NULL ;

    TTF_Font* PTPixel = NULL;
    TTF_Font* GrandPixel = NULL;

    Mix_Music* music = NULL ;
    Mix_Chunk* bumpSound = NULL ;
    Mix_Chunk* resolveSound = NULL ;

    SDL_Event events ;

    if (initALL(&pWindow, &pRenderer, &texture, &PTPixel, &GrandPixel, &music, &bumpSound, &resolveSound) != EXIT_SUCCESS ) {
        quitALL(pWindow, pRenderer, texture, PTPixel, GrandPixel, music, bumpSound, resolveSound) ;
        return EXIT_FAILURE ;
    }

    SDL_Rect destRect;
    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h );

    destRect.w = destRect.w /3;
    destRect.h = destRect.h /4;

    personnage *Kiki = create_personnage();

    Kiki->SpriteWidth = destRect.w;
    Kiki->SpriteHeight = destRect.h;

    Kiki->position_x = (larg_fenetre - destRect.w)/4;
    Kiki->position_y = (haut_fenetre -destRect.h) -16 ;
    Kiki->vitesse_x = 0;
    Kiki->vitesse_y = 0;
    int last_position_x;
    int last_position_y;

    //tableau de la position de départ de kiki dans chaque cartes
    int position_init_carte[NOMBRE_CARTES-1][2] = {
        {272, 512}, // carte 1
        {184, (haut_fenetre - destRect.h) - 48},
        {60, 53}, 
        {(larg_fenetre - destRect.w)/4,(haut_fenetre -destRect.h)/4}
    };

    //initialisation des cartes de base
    int*** cartes = initialiser_carte();
    int*** cartesbis = initialiser_carte_bis();

    //initialisation de la carte
    int **carte = cartes[0];

    //initialisation de la position de la sortie, de la position de kiki et d'un chemin initial
    // position *dst=trouver_destination(carte);
    // position *src=create_position((int)(Kiki->position_x/LARGEUR_TILE),(int)(Kiki->position_y/HAUTEUR_TILE));
    chemin *chemin_trouve=NULL;

    //initialisation de l'emplacement pour pouvoir_carte
    SDL_Rect place_astar_provisoire = {
                            .h = haut_fenetre/2,
                            .w = larg_fenetre/3,
                            .x = haut_fenetre+50,
                            .y = haut_fenetre/4,
    };
    const SDL_Rect* place_astar = &place_astar_provisoire;

    //initialisation compteur pour qu'A* ne se recalcule pas à chaque déplacement
    int compteur_astar = 10;
    int compteur_bump = 0; // compteur de bump dans murs au niv 1 -> arrivée de Tuto
    int compteur_tuto_graou = 0; // compteur énervement Tuto

    //création variable pour pouvoir debug_mod
    int debug_mod=0;

    //création variable pour savoir si on est dans carte 1
    int dans_carte=0;

    //création de la variable pour pouvoir_carte
    int pouvoir_carte=0;

    // variable pour break les for
    int conditionMet=0;

    direction *dir = create_direction();

    Save *sauvegarde = createSave(0, 0, 0, 0, 0); 

    int quit = startMenu(&pWindow, &pRenderer, sauvegarde) ;
    // printf("%d\n", sauvegarde->avancement) ;
    bool load = false ; // définit si une sauvegardde a été chargée dernièrement -> repassée à false immédiatement après 
    if (sauvegarde->avancement!=0) // si aucune sauvegarde n'a été chargée : nouveau jeu avec avancement à 1
        load = true ;

    int vh ; // variable histoire : temporaire pour sauvegarde->avancement

    Mix_PlayMusic(music, -1) ;
    
    int offset =1;
    SDL_Rect spriteRect ; //= {.x = offset*Kiki->SpriteHeight, .y = 0, .w = Kiki->SpriteWidth, .h= Kiki->SpriteHeight};

    while (quit != 1) {         
        Uint32 frameStart = SDL_GetTicks();

        if (load == true) { // si changement de sauvegarde
            dans_carte = sauvegarde->idCarte ;
            carte = cartes[dans_carte] ;
            Kiki->position_x = sauvegarde->x ;
            Kiki->position_y = sauvegarde->y ;
            load = false ;
        }

        while (SDL_PollEvent(&events)) {
            // SDL_Delay(50);
            if (sauvegarde->avancement== 0) { // 1ere cutscene après intro à erreurs SDL
                vh = sauvegarde->avancement ;
                sauvegarde->avancement = call_event(vh, carte, pWindow, pRenderer, events, PTPixel, GrandPixel, spriteRect, destRect, texture);
                if (vh == sauvegarde->avancement){ // si jeu quitté pdt la cutscene
                    quit = 1;
                }
            }
            switch (events.type) {
                case SDL_QUIT :
                    quit = 1 ;
                    break ;
                
                case SDL_KEYDOWN:
                    switch(events.key.keysym.sym){
                        case SDLK_LSHIFT:
                            sauvegarde->x = Kiki->position_x;
                            sauvegarde->y = Kiki->position_y;
                            quit = terminal(pWindow, pRenderer, GrandPixel, sauvegarde, &debug_mod, &pouvoir_carte, &compteur_astar, &load) ;
                            break;
                    } // fin sym

                    switch(events.key.keysym.scancode){
                        case SDL_SCANCODE_T:
                            compteur_tuto_graou = call_tutoriel(sauvegarde->avancement, carte, compteur_tuto_graou, pWindow, pRenderer, GrandPixel, spriteRect, destRect, texture);
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            quit =1;
                            break;
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            dir->up = true;
                            offset += 1;
                            offset %=3;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dir->left = true;
                            offset += 1;
                            offset %=3;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dir->down = true;
                            offset += 1;
                            offset %=3;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dir->right = true;
                            offset += 1;
                            offset %=3;
                            break;
                        default:
                            break;  
                    }
                    break;

                case SDL_KEYUP:
                    offset = 1;
                    switch(events.key.keysym.scancode){
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            dir->up = false;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dir->left = false;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dir->down = false;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dir->right = false;
                            break;
                        default:
                            break;
                    }
                    break;
                }
            }

        Kiki->vitesse_x = 0;
        Kiki->vitesse_y = 0;

        if (dir->up==true && dir->down==false) {
            Kiki->vitesse_y = -vitesse;
        }
        if (dir->down==true && dir->up==false) {
            Kiki->vitesse_y = vitesse;
        }
        if (dir->left==true && dir->right==false) {
            Kiki->vitesse_x = -vitesse;
        }
        if (dir->left==false && dir->right==true) {
             Kiki->vitesse_x = vitesse;
        }
        
        last_position_x=Kiki->position_x;
        last_position_y=Kiki->position_y;
        Kiki->position_x = Kiki->position_x + Kiki->vitesse_x/60;
        Kiki->position_y = Kiki->position_y + Kiki->vitesse_y/60;

        // pour quand kiki arrive au bord, la suite fais en sorte qu'elle ne sorte pas
        if (Kiki->position_x <= 0){
            Kiki->position_x = 0;
        }
        if (Kiki->position_y <= 0){
            Kiki->position_y = 0;
        }
        if (Kiki->position_x >= larg_fenetre -destRect.w){
            Kiki->position_x = larg_fenetre -destRect.w;
        }
        if (Kiki->position_y >= haut_fenetre - destRect.h){
            Kiki->position_y = haut_fenetre - destRect.h;
        }
        
        destRect.x =  Kiki->position_x;
        destRect.y =  Kiki->position_y;

        //pour quand kiki arrive sur un mur
        if (!debug_mod){
            for (int i=0;i<NOMBRE_TILE_HAUTEUR;i++){
                for (int j=0;j<NOMBRE_TILE_LARGEUR;j++){
                    if (carte[i][j]==1 || carte[i][j]==-1){
                        SDL_Rect tile = { .h = LARGEUR_TILE,
                                          .w = HAUTEUR_TILE,
                                          .x = j * LARGEUR_TILE,
                                          .y = i * HAUTEUR_TILE,
                                        };
                        SDL_bool collision = SDL_HasIntersection(&tile,&destRect);
                        if (collision){
                            Mix_PlayChannel(-1, bumpSound, 0);
                            if (sauvegarde->avancement < 3 && dans_carte == 0) { // cutscene explication \map
                                if (compteur_bump >= 40) {
                                    vh = sauvegarde->avancement ;
                                    sauvegarde->avancement = call_event(vh, carte, pWindow, pRenderer, events, PTPixel, GrandPixel, spriteRect, destRect, texture);
                                    if (vh == sauvegarde->avancement){ // si jeu quitté pdt la cutscene
                                        quit = 1;
                                    }
                                }
                                else compteur_bump++ ;
                            }
                            Kiki->position_x=last_position_x;
                            Kiki->position_y=last_position_y;
                        }
                        
                    } else if (carte[i][j]<-1){
                        //interrupteurs qui enlèvent les murs
                        SDL_Rect tile = { .h = LARGEUR_TILE,
                                          .w = HAUTEUR_TILE,
                                          .x = j * LARGEUR_TILE,
                                          .y = i * HAUTEUR_TILE,
                                        };
                        SDL_bool collision = SDL_HasIntersection(&tile,&destRect);
                        if (collision){
                            Mix_PlayChannel(-1, resolveSound, 0);
                            //on a un tableau d'adresses de carte bis et quand on passe sur un interrupteur on change de carte vers une qui a moins de murs (le nombre de l'interrupteur correspond à - son réel chiffre+2)
                            int index = -carte[i][j] -2;
                            carte = *(cartesbis + index);
                        }
                    } else if (carte[i][j]>1){
                        ///interrupteurs de changement de carte
                        SDL_Rect tile = { .h = LARGEUR_TILE,
                                          .w = HAUTEUR_TILE,
                                          .x = j * LARGEUR_TILE,
                                          .y = i * HAUTEUR_TILE,
                                        };
                        SDL_bool collision = SDL_HasIntersection(&tile,&destRect);
                        if (collision){
                            Mix_PlayChannel(-1, resolveSound, 0);
                            
                            //on a un tableau d'adresses de carte et quand on passe sur un interrupteur on change de carte (le chiffre de l'interrupteur correspond au nombre de la carte +2)
                            dans_carte++;
                            sauvegarde->idCarte = dans_carte ;
                            addSalleVisitee(sauvegarde, dans_carte) ;
                            int index = carte[i][j] -1;
                            carte = *(cartes + index);

                            // cutscene nouvelle carte
                            vh = sauvegarde->avancement ;
                            sauvegarde->avancement = call_event(vh, carte, pWindow, pRenderer, events, PTPixel, GrandPixel, spriteRect, destRect, texture);
                            if (vh == sauvegarde->avancement){
                                quit = 1;
                            }

                            Kiki->position_x=position_init_carte[dans_carte-1][0];
                            Kiki->position_y=position_init_carte[dans_carte-1][1];
                            // printf("%d, %d\n", Kiki->position_x, Kiki->position_y);

                            // initialisation pour A*
                            pouvoir_carte=0;
                            compteur_astar=10;
                            free_chemin(chemin_trouve);
                            chemin_trouve=NULL;       
                            conditionMet=1;
                            break;

                        }
                        
                    }
                }
                if(conditionMet){
                    conditionMet=0;
                    break;
                }
            }
            
        } else { // debug_mode
            for (int i=0;i<NOMBRE_TILE_HAUTEUR;i++){
                for (int j=0;j<NOMBRE_TILE_LARGEUR;j++){
                    if (carte[i][j]==-1){
                        SDL_Rect tile = { .h = LARGEUR_TILE,
                                          .w = HAUTEUR_TILE,
                                          .x = j * LARGEUR_TILE,
                                          .y = i * HAUTEUR_TILE,
                                        };
                        SDL_bool collision = SDL_HasIntersection(&tile,&destRect);
                        if (collision){
                            Kiki->position_x=last_position_x;
                            Kiki->position_y=last_position_y;
                        }
                        
                    }
                }
            }
        }
        
        
        destRect.x =  Kiki->position_x;
        destRect.y =  Kiki->position_y;
        //printf("destRect = %d, %d\n", destRect.x, destRect.y);
        // if(test){
        //     printf("test 2: %d, %d\n", Kiki->position_x, Kiki->position_y);
        // }
        

        SDL_Rect spriteRect = {.x = offset*Kiki->SpriteHeight, .y = 0, .w = Kiki->SpriteWidth, .h= Kiki->SpriteHeight};
        // if (test){
        //     printf("test 3: %d, %d\n", Kiki->position_x, Kiki->position_y);
        // }
        

        if (dir->right){
            spriteRect.y=2*Kiki->SpriteWidth;
        }
        if (dir->left){
            spriteRect.y=Kiki->SpriteWidth;
        }
        if (dir->up){
            spriteRect.y= 3*Kiki->SpriteWidth;
        }
        // if (test){
        //     printf("test 4: %d, %d\n", Kiki->position_x, Kiki->position_y);
        // }
        

        SDL_RenderClear(pRenderer);
        if(dans_carte == 0){
            afficher_carte0(pRenderer,carte);
        } else if (dans_carte == 1){
            afficher_carte1(pRenderer, carte);
        } else if (dans_carte == 2){
            afficher_carte2(pRenderer, carte);
        } else if (dans_carte == 3){
            afficher_carte3(pRenderer, carte);
        } else {
            afficher_carte(pRenderer, carte);
        }

        //affichage de A*/pouvoir carte :
        if (pouvoir_carte){
            if(compteur_astar==10){
                // print_map(carte);
                position *src=create_position((int)(Kiki->position_x/LARGEUR_TILE),(int)(Kiki->position_y/HAUTEUR_TILE));
                // print_position(src);
                
                position *dst=trouver_destination(carte);
                // print_position(dst);
                if (dst!=NULL){
                    free_chemin(chemin_trouve);
                    chemin_trouve=astar(src,dst,carte);
                }
                
                compteur_astar=0;
                // print_chemin(chemin_trouve);
                SDL_Texture *texture=pouvoir_astar(pRenderer,carte,chemin_trouve);
                // print_chemin(chemin_trouve);
                SDL_RenderCopy(pRenderer,texture,NULL,place_astar);
                // print_chemin(chemin_trouve);
                SDL_DestroyTexture(texture);
                // print_chemin(chemin_trouve);
                free(src);
                // print_chemin(chemin_trouve);
                free(dst);
                // print_chemin(chemin_trouve);
            } else {
                // if (chemin_trouve==NULL){
                //     printf("test");
                // }
                // print_chemin(chemin_trouve);
                SDL_Texture *texture=pouvoir_astar(pRenderer,carte,chemin_trouve);
                SDL_RenderCopy(pRenderer,texture,NULL,place_astar);
                SDL_DestroyTexture(texture);
                compteur_astar++;
            }
            // print_chemin(chemin_trouve);
        }
        
        SDL_RenderCopy(pRenderer, texture, &spriteRect, &destRect);

        SDL_RenderPresent(pRenderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart; // gère les fps : kiki va a la mm vitesse peu importe l'ordi
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
        
    }
    free(dir);
    // free(dst); free(src);
    free_chemin(chemin_trouve);
    free_cartes(cartes);
    free_cartes_bis(cartesbis);
    sauvegarde->x = Kiki->position_x;
    sauvegarde->y = Kiki->position_y;
    saveGame(sauvegarde) ;
    status = quitALL (pWindow, pRenderer, texture, PTPixel, GrandPixel, music, bumpSound, resolveSound) ;
    return status ; 
}
