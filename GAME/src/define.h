#ifndef DEFINE_ALL
#define DEFINE_ALL

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FLAGS_RENDERER  SDL_RENDERER_SOFTWARE    // SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC 

#define larg_fenetre 967
#define haut_fenetre 544
#define vitesse 299

#define FPS 60
#define FRAME_DELAY 1000 / FPS

int initALL (SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture,
    TTF_Font** PTPixel, TTF_Font** GrandPixel, Mix_Music** music, Mix_Chunk** bumpSound, Mix_Chunk** resolveSound) ;

int quitALL (SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture,
    TTF_Font* PTPixel, TTF_Font* GrandPixel, Mix_Music* music, Mix_Chunk* bumpSound, Mix_Chunk* resolveSound) ;

#endif
