#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

//Inclusão do ficheiro com as constantes de preprocessamento
#include "Defines.h"
#include "Menus.h"

//Declaração das funções relativas à parte gráfica
void InitEverything(int, int, TTF_Font **, SDL_Window **, SDL_Renderer **, TTF_Font ** );
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int, int );
SDL_Renderer* CreateRenderer(int, int, SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
void RenderMapa(SDL_Renderer *);
void RenderLogo(SDL_Renderer *);
void RenderBikeStation(SDL_Renderer *);
void RenderNomes(SDL_Renderer *, TTF_Font *);
void RenderDias(SDL_Renderer *, TTF_Font *);
void RenderBox1(SDL_Renderer *, int x, int y);
void RenderBox2(SDL_Renderer *, int x, int y);
void RenderCaixas(SDL_Renderer *, int [SHORTSTR]);
void SelecaoDias(SDL_Event, int[SHORTSTR], int *);
void RenderInfEstacao(SDL_Renderer *, TTF_Font *, int, int, NoEstacao*);
void SelecaoViagem(SDL_Event, int *, int *);
void ConverteCoordenadas(double, double, int *, int *);
void RenderNRotas(SDL_Renderer *, TTF_Font *, long int nrotas);
void SelectRotas(SDL_Event, long int *);
void EscolheEstacao(SDL_Event, NoEstacao *, NoEstacao **);
void CorrecaoNRotas(NoRota *, long int *);
void LimpaRotas(NoRota **, NoRota **);
void DesenhaRotas(SDL_Renderer *, NoRota *, NoEstacao *, long int);
void PartidasChegadas(NoEstacao *, NoRota **, NoRota **, int, int);
