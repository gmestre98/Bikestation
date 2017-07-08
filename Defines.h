#include <stdio.h>
#include <stdlib.h>

#define MAXID 6
#define MAXSTR 200
#define VERYSHORTSTR 5
#define SHORTSTR 10
#define STRING 100
#define MAXROTAS 10000
#define MAXDIAS 7
#define R 6371              //  Raio da Terra
#define PI 3.14159265359
#define CONVERSOR 3600      //  Constante para converter de segundos para horas
#define MIN_IDADE 15
#define MAX_IDADE 80
#define INTERVALOS 33       //  Numero de intervalos de 2 anos entre 15 e 80
#define EXTRA 2             //  Numero de intervalos fora da idade minima e maxima(maior e menor)
#define HORA_INT 24         //  Numero de intervalos de 15 minutos em 6 horas
#define MINUTO 60           //  Divisor para converter segundos em minutos

// Defines relacionados com a implementação da parte gráfica
#define VARPONTO 7
#define TABLE_SIZE 1050         //    Comprimento do mapa
#define HEIGHT_TABLE_SIZE 560   //    Altura do mapa
#define LEFT_BAR_SIZE 315       //    Tamanho da barra lateral
#define DOWN_BAR_SIZE 200       //    Tamanho da barra inferior
#define WINDOW_POSX 0           //    Posição inicial da janela: x
#define WINDOW_POSY 0           //    Posição inicial da janela: y
#define LATMAX 42396438         //    Escrita ignorando as casas decimais para facilitar os calculos
#define LATMIN 42322985         //    Escrita ignorando as casas decimais para facilitar os calculos
#define LONGMIN -70990688       //    Escrita ignorando as casas decimais para facilitar os calculos
#define LONGMAX -71160109       //    Escrita ignorando as casas decimais para facilitar os calculos
#define MAISX 1130              //    Limite inferior (x) do botão para aumentar o número de rotas
#define MAISY 640               //    Limite inferior (y) do botão para aumentar o número de rotas
#define FIMMAISX 1190           //    Limite superior (x) do botão para aumentar o número de rotas
#define FIMMAISY 700            //    Limite superior (y) do botão para aumentar o número de rotas
#define MENOSX 1250             //    Limite inferior (x) do botão para diminuir o número de rotas
#define MENOSY 640              //    Limite inferior (y) do botão para diminuir o número de rotas
#define FIMMENOSX 1310          //    Limite superior (x) do botão para diminuir o número de rotas
#define FIMMENOSY 700           //    Limite superior (y) do botão para diminuir o número de rotas
#define DIFIMGA 10              //    Valor correctivo ao clique do rato nos botões para aumentar e diminuir o número de rotas
