#include <stdio.h>
#include <stdlib.h>
#include "Defines.h"

// Estrutura para os dados do dia em que a viagem foi efectuada
typedef struct{
    int mes;
    int dia;
    int ano;
}data;

// Estrutura para os dados da hora em que a viagem foi efectuada
typedef struct{
    int hora;
    int minuto;
}momento;

// Estrutura para os dados da pessoa que efectua a viagem
typedef struct{
    int tipo;           //Para um usuário "Registered", tipo=1, para um usuário "Casual", tipo=0
    int anonascimento;
    int genero;         //Para um usuário "Male", genero=1, para um usuário "Female", genero=0
}pessoa;

// Estrutura para os dados da estação
typedef struct StationData{
    int idestacao;
    char StationID[SHORTSTR];
    char DescricaoEstacao[MAXSTR];
    char municipio[SHORTSTR];
    double latitude;
    double longitude;
    int estado;         //Para uma estação "Existing", estado=1, para uma estação "Removed", estado=0
}StationData;

// Lista duplamente ligada que guarda os dados para cada estação
typedef struct NoEstacao{
    struct StationData Estacao;
    struct NoEstacao *Next;
    struct NoEstacao *Prev;
}NoEstacao;


// Estrutura para os dados da viagem
typedef struct TripData{
    int id;
    int duracao;
    data dinicio;
    momento tinicio;
    NoEstacao *estacaoinicio;
    data dfinal;
    momento tfinal;
    NoEstacao *estacaofinal;
    char BikeID[MAXID];
    pessoa User;
}TripData;


// Lista duplamente ligada que guarda os dados para cada viagem
typedef struct NoViagem{
    struct TripData Viagem;
    struct NoViagem *Next;
    struct NoViagem *Prev;
}NoViagem;

// Estrutura para os dados da rota
typedef struct Rota{
    int nviagens;
    NoEstacao *estacaoinicio;
    NoEstacao *estacaofinal;
}Rota;


// Lista duplamente ligada que guarda os dados para cada rota
typedef struct NoRota{
    struct Rota Rota;
    struct NoRota *Next;
    struct NoRota *Prev;
}NoRota;
