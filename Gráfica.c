#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Gráfica.h"



/**
 * InitEverything: Initializes the SDL2 library and all graphical components:
 * font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with the table background and IST logo
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 */
void InitEverything(int width, int height, TTF_Font **_font,
  SDL_Window** _window, SDL_Renderer** _renderer, TTF_Font **_font2)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);


    // this opens (loads) a font file and sets a size
    *_font = TTF_OpenFont(".//Fontes//FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // inicialização da font usada para as estatísticas presentes na janela
    *_font2 = TTF_OpenFont(".//Fontes//Demonized.ttf", 24);
    if(!* _font2)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    // Para alterar o título da janela basta mudar a linha a baixo
    window = SDL_CreateWindow( "BikeStation", WINDOW_POSX, WINDOW_POSY, width,
    height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}

/** RenderMapa: Função que faz render do mapa de Boston na janela
* \param _renderer renderer to handle all rendering in a window
*/
void RenderMapa( SDL_Renderer *_renderer)
{
    SDL_Texture *Text_Mapa;
    SDL_Surface *Img_Mapa;
    SDL_Rect boardPos;


    Img_Mapa = SDL_LoadBMP("mapaBoston.bmp");
    if(Img_Mapa == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Zona do ecrã onde é impressa a imagem
    boardPos.x = 0;
    boardPos.y = 0;
    boardPos.w = Img_Mapa -> w;
    boardPos.h = Img_Mapa -> h;

    // Cria uma textura e faz render da mesma no ecrã
    SDL_RenderClear(_renderer);
    Text_Mapa = SDL_CreateTextureFromSurface(_renderer, Img_Mapa);
    SDL_RenderCopy(_renderer, Text_Mapa, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Mapa);
    SDL_FreeSurface(Img_Mapa);
}

/** RenderLogo: Função que faz render do logo do IST na janela
* \param _renderer renderer to handle all rendering in a window
*/
void RenderLogo( SDL_Renderer *_renderer)
{
    SDL_Texture *Text_Logo;
    SDL_Surface *Img_Logo;
    SDL_Rect boardPos;


    Img_Logo = SDL_LoadBMP("ist_logo.bmp");
    if(Img_Logo == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Zona do ecrã onde é impressa a imagem
    boardPos.x = 1060;
    boardPos.y = 25;
    boardPos.w = Img_Logo -> w;
    boardPos.h = Img_Logo -> h;

    // Cria uma textura e faz render da mesma no ecrã
    Text_Logo = SDL_CreateTextureFromSurface(_renderer, Img_Logo);
    SDL_RenderCopy(_renderer, Text_Logo, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Logo);
    SDL_FreeSurface(Img_Logo);
}

/** RenderBox1: Função que faz render de uma caixa sem um certo na janela
* \param _renderer renderer to handle all rendering in a window
*/
void RenderBox1( SDL_Renderer *_renderer, int x, int y)
{
    SDL_Texture *Text_Box1;
    SDL_Surface *Img_Box1;
    SDL_Rect boardPos;


    Img_Box1 = SDL_LoadBMP("boxtotick.bmp");
    if(Img_Box1 == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Zona do ecrã onde é impressa a imagem
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = Img_Box1 -> w;
    boardPos.h = Img_Box1 -> h;

    // Cria uma textura e faz render da mesma no ecrã
    Text_Box1 = SDL_CreateTextureFromSurface(_renderer, Img_Box1);
    SDL_RenderCopy(_renderer, Text_Box1, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Box1);
    SDL_FreeSurface(Img_Box1);
}

/** RenderBox2: Função que faz render de uma caixa com um certo na janela
* \param _renderer renderer to handle all rendering in a window
*/
void RenderBox2( SDL_Renderer *_renderer, int x, int y)
{
    SDL_Texture *Text_Box2;
    SDL_Surface *Img_Box2;
    SDL_Rect boardPos;


    Img_Box2 = SDL_LoadBMP("boxticked.bmp");
    if(Img_Box2 == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Zona do ecrã onde é impressa a imagem
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = Img_Box2 -> w;
    boardPos.h = Img_Box2 -> h;

    // Cria uma textura e faz render da mesma no ecrã
    Text_Box2 = SDL_CreateTextureFromSurface(_renderer, Img_Box2);
    SDL_RenderCopy(_renderer, Text_Box2, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Box2);
    SDL_FreeSurface(Img_Box2);
}

/** RenderBikeStation: Função que faz render do logo do Bikestation na janela
* \param _renderer renderer to handle all rendering in a window
*/
void RenderBikeStation( SDL_Renderer *_renderer)
{
    SDL_Texture *Text_Logo;
    SDL_Surface *Img_Logo;
    SDL_Rect boardPos;


    Img_Logo = SDL_LoadBMP("BikeStation_Logo.bmp");
    if(Img_Logo == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Zona do ecrã onde é impressa a imagem
    boardPos.x = 10;
    boardPos.y = 580;
    boardPos.w = Img_Logo -> w;
    boardPos.h = Img_Logo -> h;

    // Cria uma textura e faz render da mesma no ecrã
    Text_Logo = SDL_CreateTextureFromSurface(_renderer, Img_Logo);
    SDL_RenderCopy(_renderer, Text_Logo, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Logo);
    SDL_FreeSurface(Img_Logo);
}

/** RenderCaixas: Função que faz render das caixas para o dia da semana na
*   janela
* \param _renderer renderer to handle all rendering in a window
* \param dias - vector que guarda o valor do dia da semana escolhido e 0 para
*               os outros
*/
void RenderCaixas(SDL_Renderer *_renderer, int dias[SHORTSTR])
{
    int  x = 1310;
    int  y = 180;
    if(dias[0] == 0)
    {
        RenderBox1(_renderer, x, y);
    }
    else
    {
        RenderBox2(_renderer, x, y);
    }
    y += 50;
    if(dias[1] == 0)
    {
        RenderBox1(_renderer, x, y);
    }
    else
    {
        RenderBox2(_renderer, x, y);
    }
    y += 50;
    if(dias[2] == 0)
    {
        RenderBox1(_renderer, x, y);
    }
    else
    {
        RenderBox2(_renderer, x, y);
    }
    y += 50;
    if(dias[3] == 0)
    {
        RenderBox1(_renderer, x, y);
    }
    else
    {
        RenderBox2(_renderer, x, y);
    }
    y += 50;
    if(dias[4] == 0)
    {
        RenderBox1(_renderer, x, y);
    }
    else
    {
        RenderBox2(_renderer, x, y);
    }
    y += 50;
    if(dias[5] == 0)
    {
        RenderBox1(_renderer, x, y);
    }
    else
    {
        RenderBox2(_renderer, x, y);
    }
    y += 50;
    if(dias[6] == 0)
    {
        RenderBox1(_renderer, x, y);
    }
    else
    {
        RenderBox2(_renderer, x, y);
    }

}



/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font,
  SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}

/** RenderNomes: Função que faz render dos nossos nomes e número de aluno na
*   janela
* \param _renderer renderer to handle all rendering in a window
* \param _font TTF font used to render the text
*/
void RenderNomes( SDL_Renderer *_renderer, TTF_Font* _font)
{
    SDL_Color black = {0, 0, 0};
    RenderText(1215, 30, "Goncalo Mestre", _font, &black, _renderer);
    RenderText(1215, 60, "IST187005", _font, &black, _renderer);
    RenderText(1215, 100, "Guilherme Antunes", _font, &black, _renderer);
    RenderText(1215, 130, "IST187011", _font, &black, _renderer);
}


/** RenderDias: Função que faz render dos dias da semana na janela
* \param _renderer renderer to handle all rendering in a window
* \param _font TTF font used to render the text
*/
void RenderDias( SDL_Renderer *_renderer, TTF_Font* _font )
{
    // Declaração da cor branco
    SDL_Color black = {0, 0, 0};

    // Render do texto que dá informação relativamente ao número na janela
    RenderText(1075, 185, "Segunda-Feira", _font, &black, _renderer);
    RenderText(1075, 235, "Terca-Feira", _font, &black, _renderer);
    RenderText(1075, 285, "Quarta-Feira", _font, &black, _renderer);
    RenderText(1075, 335, "Quinta-Feira", _font, &black, _renderer);
    RenderText(1075, 385, "Sexta-Feira", _font, &black, _renderer);
    RenderText(1075, 435, "Sabado", _font, &black, _renderer);
    RenderText(1075, 485, "Domingo", _font, &black, _renderer);
}


/** SelecaoDias: Função que implementa a seleção do dia com o clique de rato
* \param event - variavel com a estrutura do evento ocorrido
* \param dias - vector que guarda o valor do dia da semana escolhido e 0 para
*               os outros
* \param Alteracao - ponteiro para a flag que é 1 se ocorreu uma alteração no
*                    dia da semana selecionado
*/
void SelecaoDias(SDL_Event event,  int dias[SHORTSTR], int *Alteracao)
{
    int i = 0;
    int xinit = 1315;
    int xend = 1345;
    int yinit = 185;
    int yend = 215;
    if(event.button.x < xend && event.button.x >xinit && event.button.y < yend
      && event.button.y > yinit)
    {
        for(i=0; i < MAXDIAS; i++)
        {
            dias[i] = 0;
        }
        dias[0] = 1;
        *Alteracao = 1;
    }
    yinit += 50;
    yend += 50;
    if(event.button.x < xend && event.button.x >xinit && event.button.y < yend
      && event.button.y > yinit)
    {
        for(i=0; i < MAXDIAS; i++)
        {
            dias[i] = 0;
        }
        dias[1] = 1;
        *Alteracao = 1;
    }
    yinit += 50;
    yend += 50;
    if(event.button.x < xend && event.button.x >xinit && event.button.y < yend
      && event.button.y > yinit)
    {
        for(i=0; i < MAXDIAS; i++)
        {
            dias[i] = 0;
        }
        dias[2] = 1;
        *Alteracao = 1;
    }
    yinit += 50;
    yend += 50;
    if(event.button.x < xend && event.button.x >xinit && event.button.y < yend
      && event.button.y > yinit)
    {
        for(i=0; i < MAXDIAS; i++)
        {
            dias[i] = 0;
        }
        dias[3] = 1;
        *Alteracao = 1;
    }
    yinit += 50;
    yend += 50;
    if(event.button.x < xend && event.button.x >xinit && event.button.y < yend
      && event.button.y > yinit)
    {
        for(i=0; i < MAXDIAS; i++)
        {
            dias[i] = 0;
        }
        dias[4] = 1;
        *Alteracao = 1;
    }
    yinit += 50;
    yend += 50;
    if(event.button.x < xend && event.button.x >xinit && event.button.y < yend
      && event.button.y > yinit)
    {
        for(i=0; i < MAXDIAS; i++)
        {
            dias[i] = 0;
        }
        dias[5] = 1;
        *Alteracao = 1;
    }
    yinit += 50;
    yend += 50;
    if(event.button.x < xend && event.button.x >xinit && event.button.y < yend
      && event.button.y > yinit)
    {
        for(i=0; i < MAXDIAS; i++)
        {
            dias[i] = 0;
        }
        dias[6] = 1;
        *Alteracao = 1;
    }
}

/** RenderInfEstacao: Função que faz render da informação para a estação
*                     selecionadajanela
* \param _renderer renderer to handle all rendering in a window
* \param _font TTF font used to render the text
* \param partida - variavel que guarda 1 para a seleção de partidas
* \param chegada - variavel que guarda 1 para a seleção de chegadas
* \param Escolhida - ponteiro para a estação escolhida
*/
void RenderInfEstacao(SDL_Renderer *_renderer, TTF_Font *_font, int partida,
  int chegada, NoEstacao *Escolhida)
{
    SDL_Color black = {0, 0, 0};

    RenderText(330, 590, "Escolheu a estacao:", _font, &black, _renderer);
    RenderText(330, 620, Escolhida->Estacao.DescricaoEstacao, _font, &black,
      _renderer);
    RenderText(330, 675, "Viagens de Partida", _font, &black, _renderer);
    RenderText(690, 675, "Viagens de Chegada", _font, &black, _renderer);
    if(partida == 0)
    {
        RenderBox1(_renderer, 630, 665);
    }
    else
    {
        RenderBox2(_renderer, 630, 665);
    }
    if(chegada == 0)
    {
        RenderBox1(_renderer, 1000, 665);
    }
    else
    {
        RenderBox2(_renderer, 1000, 665);
    }
}

/** SelecaoViagem: Função que implementa a seleção do tipo de rotas a ver
*                 (partidas ou chegadas) com o clique de rato
* \param event - variavel com a estrutura do evento ocorrido
* \param partida - variavel que guarda 1 para a seleção de partidas
* \param chegada - variavel que guarda 1 para a seleção de chegadas
*/
void SelecaoViagem(SDL_Event event, int *partida, int *chegada)
{
    if(event.button.x > 635 && event.button.x < 665 && event.button.y > 670
      && event.button.y < 700)
    {
        if(*partida == 1  &&  *chegada == 1)
        {
            *partida = 0;
        }
        else
        {
            *partida = 1;
        }
    }
    else if(event.button.x > 1005 && event.button.x < 1035 &&
      event.button.y > 670
      && event.button.y < 700)
    {
        if(*chegada == 1  &&  *partida == 1)
        {
            *chegada = 0;
        }
        else
        {
            *chegada = 1;
        }
    }
}

/** ConverteCoordenadas: Função que converte a latitude e longitude para
*                  coordenadas x e y da janela
* \param Latitude - Valor da latitude a converter
* \param Longitude - Valor da longitude a converter
* \param x - ponteiro para a variavel que guarda o valor de x
* \param y - ponteiro para a variavel que guarda o valor de y
*/
void ConverteCoordenadas(double Latitude, double Longitude, int *x, int *y)
{
    int lat=0;
    int lg=0;
    lat = Latitude * 1000000;
    lg = Longitude * 1000000;

    // Cálculo do X em função da longitude introduzida
    *x = ((TABLE_SIZE)*(LONGMAX-lg))/(LONGMAX - LONGMIN);
    // Cálculo do Y em função da latitude introduza
    *y = ((HEIGHT_TABLE_SIZE)*(LATMAX-lat))/(LATMAX - LATMIN);
}


/** Rendermais: Funçao que faz render do botão de mais na janela
* \param _renderer renderer to handle all rendering in a window
*/
void Rendermais( SDL_Renderer *_renderer)
{
    SDL_Texture *Text_Mais;
    SDL_Surface *Img_Mais;
    SDL_Rect boardPos;


    Img_Mais = SDL_LoadBMP("Botaodemais.bmp");
    if(Img_Mais == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Zona do ecrã onde é impressa a imagem
    boardPos.x = MAISX;
    boardPos.y = MAISY;
    boardPos.w = Img_Mais -> w;
    boardPos.h = Img_Mais -> h;

    // Cria uma textura e faz render da mesma no ecrã
    Text_Mais = SDL_CreateTextureFromSurface(_renderer, Img_Mais);
    SDL_RenderCopy(_renderer, Text_Mais, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Mais);
    SDL_FreeSurface(Img_Mais);
}


/** Rendermenos: Funçao que faz render do botão de menos na janela
* \param _renderer renderer to handle all rendering in a window
*/
void Rendermenos( SDL_Renderer *_renderer)
{
    SDL_Texture *Text_Menos;
    SDL_Surface *Img_Menos;
    SDL_Rect boardPos;


    Img_Menos = SDL_LoadBMP("Botaodemenos.bmp");
    if(Img_Menos == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Zona do ecrã onde é impressa a imagem
    boardPos.x = MENOSX;
    boardPos.y = MENOSY;
    boardPos.w = Img_Menos -> w;
    boardPos.h = Img_Menos -> h;

    // Cria uma textura e faz render da mesma no ecrã
    Text_Menos = SDL_CreateTextureFromSurface(_renderer, Img_Menos);
    SDL_RenderCopy(_renderer, Text_Menos, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Menos);
    SDL_FreeSurface(Img_Menos);
}

/** RenderInfEstacao: Função que faz render da informação e botões relacionados
*                     com a janela
* \param _renderer renderer to handle all rendering in a window
* \param _font TTF font used to render the text
* \param nrotas- variavel que guarda o valor do número de rotas escolhidas
*/
void RenderNRotas(SDL_Renderer * _renderer, TTF_Font *_font, long int nrotas)
{
    SDL_Color black =  {0, 0, 0};
    char charnrotas[VERYSHORTSTR] = {0};

    sprintf(charnrotas, "%ld", nrotas);

    RenderText(1100, 550, "N de Rotas", _font, &black, _renderer);
    RenderText(1280, 550, charnrotas, _font, &black, _renderer);
    Rendermais(_renderer);
    Rendermenos(_renderer);
}

/** SelecaoRotas: Função que implementa a os botões de mais e menos para o
*                 número de rotas
* \param event - variavel com a estrutura do evento ocorrido
* \param nrotas - ponteiro para a variavel que guarda o número de rotas
*/
void SelectRotas(SDL_Event Event, long int *nrotas)
{
    if(Event.button.x > (MAISX+DIFIMGA)  &&  Event.button.x < (FIMMAISX-DIFIMGA)
            &&  Event.button.y > (MAISY+DIFIMGA)
            && Event.button.y < (FIMMAISY-DIFIMGA) && *nrotas < MAXROTAS)
    {
        *nrotas = *nrotas + 1;
    }
    if(Event.button.x > (MENOSX+DIFIMGA) &&  Event.button.x < (FIMMENOSX-DIFIMGA)
            &&  Event.button.y > (MENOSY+DIFIMGA)
            && Event.button.y < (FIMMENOSY-DIFIMGA) && *nrotas > 1)
    {
        *nrotas = *nrotas - 1;
    }
}

/** CorrecaoNRotas: Função que limita o número de rotas selecionado
* \param headRota - ponteiro para a cabeça da lista de rotas
* \param nrotas - ponteiro para a variavel que guarda o número de rotas
*/
void CorrecaoNRotas(NoRota *headRota, long int *nrotas)
{
    NoRota *Rota = NULL;
    int totalrotas = 0;
    Rota = headRota;
    while(Rota != NULL)
    {
        totalrotas++;
        Rota = Rota->Next;
    }
    if(*nrotas > totalrotas)
    {
        *nrotas = totalrotas;
    }
}


/** EscolheEstacao: Função que permite selecionar outra estação
* \param event - variavel com a estrutura do evento ocorrido
* \param head - ponteiro para a cabeça da lista de estações
* \param Escolhida - ponteiro que aponta para o ponteiro da estação escolhida
*/
void EscolheEstacao(SDL_Event event, NoEstacao *head, NoEstacao **Escolhida)
{
    int x = 0;
    int y = 0;
    NoEstacao *Iterador = NULL;

    Iterador = head;
    while(Iterador != NULL)
    {
        ConverteCoordenadas(Iterador->Estacao.latitude,
          Iterador->Estacao.longitude, &x, &y);
        if(event.button.x > (x-VARPONTO)  &&  event.button.x < (x+VARPONTO)
        &&  event.button.y > (y-VARPONTO)  &&  event.button.y < (y+VARPONTO))
        {
            *Escolhida = Iterador;
        }
        Iterador = Iterador->Next;
    }
}


/** LimpaRotas: Função que remove todas as rotas da lista de rotas
* \param head - ponteiro para a cabeça da lista de rotas
* \param tail - ponteiro para a cauda da lista de rotas
*/
void LimpaRotas(NoRota **head, NoRota **tail)
{
    NoRota *Rota = NULL;
    NoRota *RotaAux = NULL;
    Rota = *head;
    while(Rota != NULL)
    {
        RotaAux = Rota->Next;
        removeRota(head, tail, Rota);
        Rota = RotaAux;
    }
}

/** PartidasChegadas: Função que implementa a seleção do tipo de rotas
* \param Escolhida - ponteiro para a estação escolhida
* \param headRota - ponteiro para a cabeça da lista de rotas
* \param tailRota - ponteiro para a cauda da lista de rotas
* \param partida - variavel que guarda 1 para a seleção de partidas
* \param chegada - variavel que guarda 1 para a seleção de chegadas
*/
void PartidasChegadas(NoEstacao *Escolhida, NoRota **headRota,
  NoRota **tailRota, int partida, int chegada)
{
    NoRota *RotaAux = NULL;
    NoRota *RotaAux1 = NULL;
    RotaAux = *headRota;
    while(RotaAux != NULL)
    {
        RotaAux1 = RotaAux->Next;
        if(partida == 0)
        {
            if(RotaAux->Rota.estacaoinicio->Estacao.idestacao == Escolhida->Estacao.idestacao)
            {
                removeRota(headRota, tailRota, RotaAux);
            }
        }
        if(chegada == 0)
        {
            if(RotaAux->Rota.estacaofinal->Estacao.idestacao == Escolhida->Estacao.idestacao)
            {
                removeRota(headRota, tailRota, RotaAux);
            }
        }
        RotaAux = RotaAux1;
    }
}


/** DesenhaRotas: Função que desenha as linhas correspondentes às rotas no ecrã
*                 com um degradê de vermelho para verde para as rotas de partida
*                 com numero de viagens crescente
*                 com um degradê de azul claro para roxo para as rotas de
*                 chegada com numero de viagens crescente
* \param _renderer renderer to handle all rendering in a window
* \param headRota - ponteiro para a cabeça da lista de rotas
* \param Escolhida - ponteiro para a estação escolhida
* \param nrotas- variavel que guarda o valor do número de rotas escolhidas
*/
void DesenhaRotas(SDL_Renderer *_renderer, NoRota *headRota,
  NoEstacao *Escolhida, long int nrotas)
{
    int i = 0;
    int x = 0;
    int y = 0;
    int xestacao = 0;
    int yestacao = 0;
    NoRota *Rota = NULL;
    ConverteCoordenadas(Escolhida->Estacao.latitude,
      Escolhida->Estacao.longitude, &x, &y);
    Rota = headRota;
    while(Rota != NULL  &&  i < nrotas)
    {
        if(Rota->Rota.estacaoinicio->Estacao.idestacao ==
          Escolhida->Estacao.idestacao)
        {
            ConverteCoordenadas(Rota->Rota.estacaofinal->Estacao.latitude,
             Rota->Rota.estacaofinal->Estacao.longitude, &xestacao, &yestacao);
            if(Rota->Rota.nviagens == 1)
            {
                SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
            }
            else if(Rota->Rota.nviagens > 1 && Rota->Rota.nviagens <=5)
            {
                SDL_SetRenderDrawColor(_renderer, 204, 51, 0, 255);
            }
            else if(Rota->Rota.nviagens > 5 && Rota->Rota.nviagens <= 15)
            {
                SDL_SetRenderDrawColor(_renderer, 153, 102, 0, 255);
            }
            else if(Rota->Rota.nviagens > 15 && Rota->Rota.nviagens <= 25)
            {
                SDL_SetRenderDrawColor(_renderer, 102, 153, 0, 255);
            }
            else if(Rota->Rota.nviagens > 25 && Rota->Rota.nviagens <= 35)
            {
                SDL_SetRenderDrawColor(_renderer, 51, 204, 0, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
            }
        }
        else
        {
            ConverteCoordenadas(Rota->Rota.estacaoinicio->Estacao.latitude,
            Rota->Rota.estacaoinicio->Estacao.longitude, &xestacao, &yestacao);
            if(Rota->Rota.nviagens == 1)
            {
                SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 255);
            }
            else if(Rota->Rota.nviagens > 2 && Rota->Rota.nviagens <=5)
            {
                SDL_SetRenderDrawColor(_renderer, 51, 102, 255, 255);
            }
            else if(Rota->Rota.nviagens > 5 && Rota->Rota.nviagens <= 15)
            {
                SDL_SetRenderDrawColor(_renderer, 102, 153, 255, 255);
            }
            else if(Rota->Rota.nviagens > 15 && Rota->Rota.nviagens <= 25)
            {
                SDL_SetRenderDrawColor(_renderer, 153, 102, 255, 255);
            }
            else if(Rota->Rota.nviagens > 25 && Rota->Rota.nviagens <= 35)
            {
                SDL_SetRenderDrawColor(_renderer, 204, 51, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
            }
        }
        SDL_RenderDrawLine(_renderer, x, y+1, xestacao-1, yestacao);
        SDL_RenderDrawLine(_renderer, x, y, xestacao, yestacao);
        SDL_RenderDrawLine(_renderer, x+1, y, xestacao, yestacao-1);
        Rota = Rota->Next;
        i++;
    }
}
