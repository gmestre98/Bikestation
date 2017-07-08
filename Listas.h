#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Estruturas.h"


void AbrirFicheiros(FILE**, FILE**, int, char**);
NoViagem* NewTrip(TripData);
NoEstacao* NewStation(StationData);
NoRota* NewRoute(Rota);
NoViagem* InserirViagem(NoViagem**, NoViagem*, TripData);
NoEstacao* InserirEstacao(NoEstacao**, NoEstacao*, StationData);
void InserirRota(NoRota **, NoRota**, Rota);
void removeEstacao(NoEstacao **, NoEstacao **, NoEstacao *);
void LimpaEstacoes(NoEstacao **, NoEstacao **);
void LeituraRotas(NoViagem *, NoEstacao *, NoRota **, NoRota **);
NoViagem* TripToList(FILE *, NoViagem **, NoViagem *, char[MAXSTR], NoEstacao *);
NoEstacao* StationToList(FILE *, NoEstacao **, NoEstacao *, char[MAXSTR]);
void PrintListViagens(NoViagem *);
void PrintListadeEstacoes(NoEstacao *, NoViagem *);
void APartir(NoEstacao *, NoViagem *, int *, int *, float *);
void AChegar(NoEstacao *, NoViagem *, int *, int *, float *);
void LeEstacao(int *, NoEstacao*);
void removeRota(NoRota **, NoRota **, NoRota*);
void RestringeRotas(NoEstacao *, NoRota **, NoRota **, int);
void BubbleSortRotas(NoRota **, NoRota **);
void PrintListRotas(NoEstacao*, NoRota *, int);
void StatGenero(NoViagem*);
void StatIdade(NoViagem*);
void StatDuracao(NoViagem *);
void StatVelocidade(NoViagem *);
void PrintStatGenero(float, float, int);
void PrintStatIdade(int users[33], int extrausers[2], float);
void PrintStatDuracao(int viagens[24], float);
void PrintStatVelocidade(double distanciam[33], double distanciaf[33],
        double duracaom[33], double duracaof[33], double distanciam2[2],
        double distanciaf2[2], double duracaom2[2], double duracaof2[2]);
void CalculaDistancia(double, double, double, double, double*);
