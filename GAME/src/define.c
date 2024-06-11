#include "define.h"
#include "./plugins/sounds.h"

//////////////////////////////////////////////////////////// Init & Quit

int initALL(SDL_Window** pWindow, SDL_Renderer** pRenderer, SDL_Texture** texture,
    TTF_Font** PTPixel, TTF_Font** GrandPixel, Mix_Music** music, Mix_Chunk** bumpSound, Mix_Chunk** resolveSound) {

    // SDL_Init
    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Error SDL_Init : %s\n", SDL_GetError()) ;
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE ;
    }
    // SDL_Window
    *pWindow = SDL_CreateWindow("\\debug_mode", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, larg_fenetre, haut_fenetre, 0);
    if (*pWindow==NULL){
        printf("error in creation of SDL window : %s\n", SDL_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // SDL_Renderer
    Uint32 flags2 = FLAGS_RENDERER ;
    *pRenderer = SDL_CreateRenderer(*pWindow, -1, flags2);
    if (*pRenderer==NULL){
        printf("error in creation of SDL renderer : %s\n", SDL_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // SDL_Surface
    SDL_Surface* surfaceSprite = NULL ;
    surfaceSprite = IMG_Load("./GAME/img/sprites/Kiki_sprite_sheet.png");
    if (surfaceSprite==NULL) {
        printf("error in creation of SDL surface : %s\n", SDL_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // SDL_Texture
    SDL_ClearError();
    *texture = SDL_CreateTextureFromSurface(*pRenderer, surfaceSprite);
    SDL_FreeSurface(surfaceSprite);
    if (*texture==NULL) {
        printf("error in creation of SDL texture : %s\n", SDL_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }

    // SDL_Image
    int flags = IMG_INIT_JPG|IMG_INIT_PNG ;
    int initted = IMG_Init(flags) ;
    if ((initted&flags) != flags) {
        fprintf(stderr, "Error IMG_Init : %s\n", IMG_GetError()) ;
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE ;
    }

    // TTF_Init
    if (TTF_Init()==-1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // PTPixel
    *PTPixel = TTF_OpenFont("GAME/img/assets/Puzzle-Tale-Pixel-Regular.ttf",20);
    TTF_SetFontStyle(*PTPixel, TTF_STYLE_NORMAL);
    TTF_SetFontHinting(*PTPixel, TTF_HINTING_NORMAL);
    if(*PTPixel==NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // GrandPixel
    *GrandPixel = TTF_OpenFont("GAME/img/assets/Grand9K-Pixel.ttf",20);
    TTF_SetFontStyle(*GrandPixel, TTF_STYLE_NORMAL);
    TTF_SetFontHinting(*GrandPixel, TTF_HINTING_NORMAL);
    if(*GrandPixel==NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }

    // Mix_Init
    Mix_Init(MIX_INIT_OGG) ;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // music (background music)
    *music = loadBGmusic("overworld") ; 
    if (*music == NULL) {
        printf("There was a problem for the BGmusic ! SDL_mixer Error: %s\n", Mix_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // sound for collisions
    *bumpSound = loadSoundEffect("bump") ;
    if (*bumpSound == NULL) {
        printf("There was a problem with the 'bump' sound effect ! SDL_mixer Error: %s\n", Mix_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    // sound for resolving puzzles
    *resolveSound = loadSoundEffect("resolve") ;
    if (*resolveSound == NULL) {
        printf("There was a problem with the 'resolve' sound effect ! SDL_mixer Error: %s\n", Mix_GetError());
        quitALL(*pWindow, *pRenderer, *texture, *PTPixel, *GrandPixel, *music, *bumpSound, *resolveSound) ;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS ; 
}



int quitALL (SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture,
    TTF_Font* PTPixel, TTF_Font* GrandPixel, Mix_Music* music, Mix_Chunk* bumpSound, Mix_Chunk* resolveSound) {

    if (window != NULL)
        SDL_DestroyWindow(window) ;
    if (renderer != NULL) 
        SDL_DestroyRenderer(renderer);
    if (texture!=NULL)
        SDL_DestroyTexture(texture);
    if (music != NULL) 
        Mix_FreeMusic(music);
    if (bumpSound != NULL) 
        Mix_FreeChunk(bumpSound);
    if (resolveSound != NULL) 
        Mix_FreeChunk(resolveSound);

    // safe to call these functions on NULL 
    TTF_CloseFont(PTPixel);
    TTF_CloseFont(GrandPixel);
    
    TTF_Quit();    
    IMG_Quit() ;
    Mix_CloseAudio() ; // quit SDL_mixer 
    SDL_Quit() ;

    return 0 ;
}

