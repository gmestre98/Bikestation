/*    Comentário de introdução ao projecto:BIKESTATION

Trabalho Realizado por Gonçalo Mestre, nº de aluno 87005 e
                      Guilherme Antunes nº de aluno 87011

Projecto realizado com o objectivo de desenvonvilmento de uma aplicação
desiganada BIKESTATION


Esta aplicação pretende analisar os dados de um sistema de alugar de bicicletas

É constituido por uma parte textual onde é possivel fazer uma seleção de dados,
restringindo os mesmos por hora de inicio e fim, duracao ou dia da semana
Também é possivel fazer uma listagem das viagens analisadas, das estações, das
rotas e das estatisticas

A aplicação também contém uma parte gráfica em que é possivel ver as rotas
disponiveis para a estaçao escolhida para 1 dia da semana, restingindo, sendo
possivel selecionar o numero de rotas e se as mesmas são de partida ou chegada.
Também é possivel escolher uma estação, tudo através do clique do rato!
*/


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defines.h"
#include "Gráfica.h"

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *serif = NULL;
    TTF_Font *Demonized = NULL;
    SDL_Event event;
    int quit = 0;
    int width = (TABLE_SIZE + LEFT_BAR_SIZE);
    int height = (HEIGHT_TABLE_SIZE + DOWN_BAR_SIZE);
    NoViagem *headViagem = NULL;
    NoViagem *tailViagem = NULL;
    NoViagem *Iterador = NULL;
    NoViagem *Aux = NULL;
    NoViagem *Aux1 = NULL;
    NoViagem *Aux2 = NULL;
    NoEstacao *headEstacao = NULL;
    NoEstacao *tailEstacao = NULL;
    NoEstacao *Escolhida = NULL;
    NoRota *headRota = NULL;
    NoRota *tailRota = NULL;
    momento *horainicio = NULL;
    momento *horafim = NULL;
    int modografico=0;
    int modotextual=0;
    int ficheiro1=0;
    int ficheiro2=0;
    int Alteracaodias = 0;
    int dia = 0;
    int dias[SHORTSTR] = {0};
    int partida = 1;
    int chegada = 1;
    long int nrotas=10;
    char str[MAXSTR]= {0};
    FILE *ftripdata = NULL;
    FILE *fstationdata = NULL;


    // Verificação do número de argumentos inseridos
    if(argc < 4)
    {
        printf("Existem argumentos em falta\n\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Bloco que verifica se os argumentos inseridos estão dentro do permitido,
        caso algum deles não esteja é feita a saida do programa */
        modografico = strcmp(argv[1], "-g");
        modotextual = strcmp(argv[1], "-t");
        ficheiro1 = strcmp(argv[2], "tripdata.csv");
        ficheiro2 = strcmp(argv[3], "stationdata.csv");
        if((modografico != 0 && modotextual != 0) || (ficheiro1 != 0) || (ficheiro2 != 0))
        {
            printf("Um ou mais argumentos não estão de acordo com o pretendido!\n");
            exit(EXIT_FAILURE);
        }
        // Caso os argumentos estejam dentro do permitido é executado o programa
        else
        {
            // Abertura dos ficheiros e escrita dos mesmos nnas listas respectivas
            AbrirFicheiros(&ftripdata, &fstationdata, argc, argv);
            while(fgets(str, MAXSTR, fstationdata) != NULL)
            {
                tailEstacao=StationToList(fstationdata, &headEstacao, tailEstacao, str);
            }
            while(fgets(str, MAXSTR, ftripdata) != NULL)
            {
                tailViagem=TripToList(ftripdata, &headViagem, tailViagem, str, headEstacao);
            }
            Aux = headViagem;
            while(Aux != NULL)
            {
                Aux1 = Aux->Next;
                if(strcmp(Aux->Viagem.BikeID, "Casual") == 0 || strcmp(Aux->Viagem.BikeID, "Registered") == 0)
                {
                    removeViagem(&headViagem, &tailViagem, Aux);
                }
                Aux = Aux1;
            }
            // Execuão do modo textual caso o mesmo tenha sido escolhido
            if(modotextual == 0)
            {
                ModoTextual(&headViagem, &tailViagem, ftripdata, fstationdata, argc, argv, headEstacao, &headRota, &tailRota);
            }
            // Execução do modo gráfico caso o mesmo tenha sido escolhido
            if(modografico == 0)
            {
                Escolhida = headEstacao;
                dias[0] = 1;
                AbrirFicheiros(&ftripdata, &fstationdata, argc, argv);
                while(fgets(str, MAXSTR, ftripdata) != NULL)
                {
                    tailViagem=TripToList(ftripdata, &headViagem, tailViagem, str, headEstacao);
                }
                Aux1 = headViagem;
                while(Aux1 != NULL)
                {
                    Aux2 = Aux1->Next;
                    if(strcmp(Aux1->Viagem.BikeID, "Casual") == 0 || strcmp(Aux1->Viagem.BikeID, "Registered") == 0)
                    {
                        removeViagem(&headViagem, &tailViagem, Aux1);
                    }
                Aux1 = Aux2;
                }
                Remocao(&headViagem, &tailViagem, horainicio, horafim, -1, 1, 0);
                SelecaoViagem(event, &partida, &chegada);
                SelectRotas(event, &nrotas);
                EscolheEstacao(event, headEstacao, &Escolhida);
                LimpaRotas(&headRota, &tailRota);
                LeituraRotas(headViagem, headEstacao, &headRota, &tailRota);
                RestringeRotas(headEstacao, &headRota, &tailRota, Escolhida->Estacao.idestacao);
                PartidasChegadas(Escolhida, &headRota, &tailRota, partida, chegada);
                CorrecaoNRotas(headRota, &nrotas);
                BubbleSortRotas(&headRota, &tailRota);
                InitEverything(width, height, &serif, &window, &renderer, &Demonized);
                while(quit == 0)
                {
                    while( SDL_PollEvent( &event ) )
                    {
                        // Condição que indica que o jogo foi fechado
                        if( event.type == SDL_QUIT )
                        {
                            quit = 1;
                        }
                        // Condição que indica que uma tecla foi pressionada
                        else if ( event.type == SDL_MOUSEBUTTONDOWN )
                        {
                            switch(event.button.button)
                            {
                            case SDL_BUTTON_LEFT:
                                SelecaoDias(event, dias, &Alteracaodias);
                                if(Alteracaodias == 1)
                                {
                                    dia = 0;
                                    while(dias[dia] != 1)
                                    {
                                        dia++;
                                    }
                                    Iterador = headViagem;
                                    while(Iterador != NULL)
                                    {
                                        Aux = Iterador->Next;
                                        removeViagem(&headViagem, &tailViagem,Iterador);
                                        Iterador = Aux;
                                    }
                                    AbrirFicheiros(&ftripdata, &fstationdata, argc, argv);
                                    while(fgets(str, MAXSTR, ftripdata) != NULL)
                                    {
                                        tailViagem=TripToList(ftripdata, &headViagem, tailViagem, str, headEstacao);
                                    }
                                    Aux1 = headViagem;
                                    while(Aux1 != NULL)
                                    {
                                        Aux2 = Aux1->Next;
                                        if(strcmp(Aux1->Viagem.BikeID, "Casual") == 0 || strcmp(Aux1->Viagem.BikeID, "Registered") == 0)
                                        {
                                            removeViagem(&headViagem, &tailViagem, Aux1);
                                        }
                                        Aux1 = Aux2;
                                    }
                                    Remocao(&headViagem, &tailViagem, horainicio, horafim, -1, dia+1, 0);

                                }
                                SelecaoViagem(event, &partida, &chegada);
                                SelectRotas(event, &nrotas);
                                EscolheEstacao(event, headEstacao, &Escolhida);
                                LimpaRotas(&headRota, &tailRota);
                                LeituraRotas(headViagem, headEstacao, &headRota, &tailRota);
                                RestringeRotas(headEstacao, &headRota, &tailRota, Escolhida->Estacao.idestacao);
                                PartidasChegadas(Escolhida, &headRota, &tailRota, partida, chegada);
                                CorrecaoNRotas(headRota, &nrotas);
                                BubbleSortRotas(&headRota, &tailRota);
                                break;
                            default:
                                break;
                            }
                        }

                    }

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                    RenderMapa(renderer);
                    RenderLogo(renderer);
                    RenderBikeStation(renderer);
                    RenderNomes(renderer, serif);
                    RenderDias(renderer, Demonized);
                    RenderCaixas(renderer, dias);
                    RenderInfEstacao(renderer, Demonized, partida, chegada, Escolhida);
                    RenderNRotas(renderer, Demonized, nrotas);
                    DesenhaRotas(renderer, headRota, Escolhida, nrotas);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(50);

                }
                TTF_CloseFont(serif);
                TTF_CloseFont(Demonized);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return EXIT_SUCCESS;
            }
        }
    }

    LimpaEstacoes(&headEstacao, &tailEstacao);
    LimpaRotas(&headRota, &tailRota);
    Aux1 = headViagem;
    while(Aux1 != NULL)
    {
        Aux = Aux1->Next;
        removeViagem(&headViagem, &tailViagem, Aux1);
        Aux1 = Aux;
    }
}
