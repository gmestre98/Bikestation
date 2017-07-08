#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listas.h"


/** AbrirFicheiros: Função que faz a abertura dos ficheiros que estão como argumentos,
*   verificando a correcta abertura dos mesmos
* \param ftripdata - ponteiro para o ficheiro com os dados das viagens
* \param fstationdata - ponteiro para o ficheiro com os dados das estações
* \param argc - guarda o número de argumentos do programa
* \param argv - ponteiro para os argumentos do programa
*/
void AbrirFicheiros(FILE **ftripdata, FILE **fstationdata, int argc, char *argv[])
{
    *ftripdata = fopen(argv[2], "r");
    if(ftripdata == NULL)            //Verifica se o ficheiro foi correctamente aberto
    {
        printf("Não foi possível fazer a leitura do ficheiro com a informação das viagens\n");
        exit(EXIT_FAILURE);
    }
    *fstationdata = fopen(argv[3], "r");
    if(fstationdata == NULL)         //Verifica se o ficheiro foi correctamente aberto
    {
        printf("Não foi possível fazer a leitura do ficheiro com a informação das estações\n");
        exit(EXIT_FAILURE);
    }
}



/** NewTrip: Função que cria um novo nó a ser inserido na lista de viagens
*   e retorna esse mesmo nó
* \param _Viagem - conjunto de dados que ficam guardados no novo nó
*/
NoViagem* NewTrip(TripData _Viagem)
{
    NoViagem *NovaViagem = NULL;
    NovaViagem =(NoViagem*)malloc(sizeof(NoViagem));
    if(NovaViagem == NULL)      // Verificação da alocação da memória
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    NovaViagem->Viagem=_Viagem;
    NovaViagem->Next=NULL;          // Ponteiro com valor atribuido apenas quando ligado à lista
    NovaViagem->Prev=NULL;          // Ponteiro com valor atribuido apenas quando ligado à lista
    return NovaViagem;
}



/** NewStation: Função que cria um novo nó a ser inserido na lista de estações
*   e retorna esse mesmo nó
* \param _Estacao - conjunto de dados que ficam guardados no novo nó
*/
NoEstacao* NewStation(StationData _Estacao)
{
    NoEstacao *NovaEstacao = NULL;
    NovaEstacao = (NoEstacao*)malloc(sizeof(NoEstacao));
    if(NovaEstacao == NULL)     // Verificação da alocação da memória
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    NovaEstacao->Estacao = _Estacao;
    NovaEstacao->Next = NULL;       // Ponteiro com valor atribuido apenas quando ligado à lista
    NovaEstacao->Prev = NULL;       // Ponteiro com valor atribuido apenas quando ligado à lista
    return NovaEstacao;
}



/** NewRoute: Função que cria um novo nó a ser inserido na lista de rotas
*   e retorna esse mesmo nó
* \param _Rota - conjunto de dados que ficam guardados no novo nó
*/
NoRota* NewRoute(Rota _Rota)
{
    NoRota *NovaRota = NULL;
    NovaRota =(NoRota*)malloc(sizeof(NoRota));
    if(NovaRota == NULL)      // Verificação da alocação da memória
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    NovaRota->Rota=_Rota;
    NovaRota->Next=NULL;          // Ponteiro com valor atribuido apenas quando ligado à lista
    NovaRota->Prev=NULL;          // Ponteiro com valor atribuido apenas quando ligado à lista
    return NovaRota;
}



/** InserirViagem: Função que insere um novo nó na cauda da lista de viagens
*   e retorna esse mesmo nó
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de viagens
* \param tail - ponteiro da cauda da lista de viagens
* \param _Viagem - conjunto de dados que ficam guardados no novo nó
*/
NoViagem* InserirViagem(NoViagem **head, NoViagem *tail, TripData _Viagem)
{
    NoViagem* Aux = NULL;
    NoViagem* NovaViagem = NewTrip(_Viagem);    // Criação do novo nó
    if(*head == NULL)    // Verifica se a lista está vazia
    {
        *head = NovaViagem;
        return NovaViagem;
    }
    Aux = tail;          // Coloca o valor do nó final no auxiliar
    Aux->Next = NovaViagem;
    NovaViagem->Prev = Aux;
    return NovaViagem;
}



/** InserirEstacao: Função que insere um novo nó na cauda da lista de estações
*   e retorna esse mesmo nó
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de estações
* \param tail - ponteiro da cauda da lista de estações
* \param _Estacao - conjunto de dados que ficam guardados no novo nó
*/
NoEstacao* InserirEstacao(NoEstacao **head, NoEstacao *tail, StationData _Estacao)
{
    NoEstacao* Aux = NULL;
    NoEstacao* NovaEstacao = NewStation(_Estacao);     // Criação do novo nó
    if(*head == NULL)       // Verifica se a lista está vazia
    {
        *head = NovaEstacao;
        return NovaEstacao;
    }
    Aux = tail;             // Coloca o valor do nó final no auxiliar
    Aux->Next = NovaEstacao;
    NovaEstacao->Prev = Aux;
    return NovaEstacao;
}



/** InserirRota: Função que insere um novo nó na cauda da lista de rotas
*   e retorna esse mesmo nó
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de rotas
* \param tail - ponteiro da cauda da lista de rotas
* \param _Rota - conjunto de dados que ficam guardados no novo nó
*/
void InserirRota(NoRota **head, NoRota **tail, Rota _Rota)
{
    NoRota* Aux = NULL;
    NoRota* NovaRota = NewRoute(_Rota);    // Criação do novo nó
    if(*head == NULL)    // Verifica se a lista está vazia
    {
        *head = NovaRota;
        *tail = NovaRota;
    }
    else
    {
        Aux = *tail;          // Coloca o valor do nó final no auxiliar
        Aux->Next = NovaRota;
        NovaRota->Prev = Aux;
        *tail = NovaRota;
    }
}



/** TripToList: Função que guarda a ultima linha do ficheiro de viagens lida num nó
*   da lista de viagens e retorna esse mesmo nó
* \param ftripdata - ponteiro para o ficheiro com os dados das viagens
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de viagens
* \param tail - ponteiro da cauda da lista de viagens
* \param char - string que guarda os dados da linha do ficheiro lida
* \param headEstacao - ponteiro para a cabeça da lista de estações
*/
NoViagem* TripToList(FILE *ftripdata, NoViagem **head, NoViagem *tail, char str[MAXSTR], NoEstacao *headEstacao)
{
    char * str2 = NULL;
    char str3[STRING] = {0};
    TripData *_Viagem = NULL;
    NoViagem *NovaViagem = NULL;
    NoEstacao *Aux = NULL;
    int compar=0;
    // Alocação de memória para a estrutura com os dados de uma viagem
    _Viagem = (TripData*)malloc(sizeof(TripData));
    // Verificação da correcta alocação da memória
    if(_Viagem == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }

    // Alocação de memória para a estação inicial
    _Viagem->estacaoinicio = (NoEstacao*)malloc(sizeof(NoEstacao));
    // Verificação da correcta alocação da memória
    if(_Viagem->estacaoinicio == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }

    // Alocação de memória para a estação final
    _Viagem->estacaofinal = (NoEstacao*)malloc(sizeof(NoEstacao));
    // Verificação da correcta alocação da memória
    if(_Viagem->estacaofinal == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }



    /** Conjunto de conversões da string lida do ficheiro para cada uma das varieveis
    *   da estrutura de dados da Viagem
    *   Utilização de strtok para separar em tokens a string lida do ficheiro
    *   Conversão para inteiros no caso em que se pretende guardar um inteiro utilizando sscanf
    *   Nos casos em que se pretendia apenas copiar o conteudo para um string foi utilizado strcpy
    **/

    str2 = strtok(str, ",/ :");
    sscanf(str2, "%d", &_Viagem->id);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->duracao);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->dinicio.mes);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->dinicio.dia);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->dinicio.ano);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->tinicio.hora);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->tinicio.minuto);

    str2 = strtok(NULL, ",/ :");
    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->estacaoinicio->Estacao.idestacao);
    /* Loop que verifica qual é o nó da lista estações correspondente à estação
    de inicio da viagem */
    Aux = headEstacao;
    while(Aux->Estacao.idestacao != _Viagem->estacaoinicio->Estacao.idestacao)
    {
        Aux = Aux->Next;
    }
    _Viagem->estacaoinicio = Aux;

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->dfinal.mes);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->dfinal.dia);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->dfinal.ano);


    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->tfinal.hora);

    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->tfinal.minuto);

    str2 = strtok(NULL, ",/ :");
    str2 = strtok(NULL, ",/ :");
    sscanf(str2, "%d", &_Viagem->estacaofinal->Estacao.idestacao);
    /* Loop que verifica qual é o nó da lista estações correspondente à estação
    de fim da viagem */
    Aux = headEstacao;
    while(Aux->Estacao.idestacao != _Viagem->estacaofinal->Estacao.idestacao)
    {
        Aux = Aux->Next;
    }
    _Viagem->estacaofinal = Aux;

    str2 = strtok(NULL, ",/ :");
    strcpy(_Viagem->BikeID, str2);

    str2 = strtok(NULL, ",/ :");
    strcpy(str3, str2);

    // Caso o utilizador seja registado é feita a leitura dos restantes dados
    if(strcmp(str3, "Registered") == 0)
    {
        _Viagem->User.tipo = 1;

        str2 = strtok(NULL, ",/ :");
        sscanf(str2, "%d", &_Viagem->User.anonascimento);

        str2 = strtok(NULL, ",/ :");
        strcpy(str3, str2);
        // Verificação do género do usuário
        compar=strcmp(str3, "Male");
        // É guardado um valor inteiro consoante o género do usuário
        if(compar > 0)
        {
            _Viagem->User.genero = 1;
        }
        else
            _Viagem->User.genero = 0;

    }
    // Caso o utilizador seja casual apenas é feita a leitura desse dado
    else
    {
        _Viagem->User.tipo = 0;
    }
    NovaViagem = InserirViagem(head, tail, *_Viagem);
    free(_Viagem);
    return NovaViagem;
}



/** StationToList: Função que guarda a ultima linha do ficheiro de estações lida num nó
*   da lista de estações e retorna esse mesmo nó
* \param fstationdata - ponteiro para o ficheiro com os dados das estações
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de estações
* \param tail - ponteiro da cauda da lista de estações
* \param char - string que guarda os dados da linha do ficheiro lida
* \param headEstacao - ponteiro para a cabeça da lista de estações
*/
NoEstacao* StationToList(FILE *fstationdata, NoEstacao **head, NoEstacao *tail, char str[MAXSTR])
{
    char *str2 = NULL;
    char str3[STRING] = {0};
    StationData *_Estacao = NULL;
    NoEstacao *NovaEstacao = NULL;
    // Alocação de memória para a estrutura com os dados de uma estação
    _Estacao = (StationData*)malloc(sizeof(StationData));
    // Verificação da correcta alocação da memória
    if(_Estacao == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }

    _Estacao->idestacao = 0;

    /** Conjunto de conversões da string lida do ficheiro para cada uma das varieveis
    *   da estrutura de dados da Estação
    *   Utilização de strtok para separar em tokens a string lida do ficheiro
    *   Conversão para inteiros no caso em que se pretende guardar um inteiro utilizando sscanf
    *   Nos casos em que se pretendia apenas copiar o conteudo para um string foi utilizado strcpy
    **/
    str2 = strtok(str, ",");
    sscanf(str2, "%d", &_Estacao->idestacao);

    str2 = strtok(NULL, ",");
    strcpy(_Estacao->StationID, str2);

    str2 = strtok(NULL, ",");
    strcpy(_Estacao->DescricaoEstacao, str2);

    str2 = strtok(NULL, ",");
    strcpy(_Estacao->municipio, str2);

    str2 = strtok(NULL, ",");
    sscanf(str2, "%lf", &_Estacao->latitude);

    str2 = strtok(NULL, ",");
    sscanf(str2, "%lf", &_Estacao->longitude);

    str2 = strtok(NULL, ",");
    strcpy(str3, str2);

    if(strcmp(str3, "Removed") < 0)
        _Estacao->estado=1;
    else
        _Estacao->estado=0;

    if(_Estacao->idestacao != 0)
    {
        NovaEstacao = InserirEstacao(head, tail, *_Estacao);
    }
    free(_Estacao);
    return NovaEstacao;
}

/** removeEstacao: Remove um nó da lista das estações
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de estação
* \param tail - ponteiro que aponta para o ponteiro da cauda da lista de estação
* \param Estacao - ponteiro para o nó da lista de estações a eliminar
*/
void removeEstacao(NoEstacao **head, NoEstacao **tail, NoEstacao *Estacao)
{
    // Verifica se a lista está vazia
    if(*head == NULL)
        printf("A lista está vazia!\n");
    // Verifica o caso em que a lista apenas contem um unico elemento
    if(*tail == Estacao && *head == Estacao)
    {
        free(Estacao);
        *head = NULL;
        *tail = NULL;
    }
    // Verifica se o nó a remover é o primeiro nó da lista
    else if(*head == Estacao)
    {
        if(Estacao->Next != NULL)
        {
            (Estacao->Next)->Prev = NULL;
            *head = Estacao->Next;
            free(Estacao);
        }
    }
    // Verifica se o nó a remover é o último nó da lista
    else if(*tail == Estacao)
    {
        (Estacao->Prev)->Next = NULL;
        *tail = Estacao->Prev;
        free(Estacao);
    }
    else
    {
        (Estacao->Prev)->Next = Estacao->Next;
        (Estacao->Next)->Prev = Estacao->Prev;
        free(Estacao);
    }
}

/** LimpaEstacoes: Função que remove todas as estações da lista de estações
* \param head - ponteiro para a cabeça da lista de estações
* \param tail - ponteiro para a cauda da lista de estações
*/
void LimpaEstacoes(NoEstacao **head, NoEstacao **tail)
{
    NoEstacao *Estacao = NULL;
    NoEstacao *EstacaoAux = NULL;
    Estacao = *head;
    while(Estacao != NULL)
    {
        EstacaoAux = Estacao->Next;
        removeEstacao(head, tail, Estacao);
        Estacao = EstacaoAux;
    }
}



/** LeituraRotas: Função que guarda os dados de todas as rotas na lista de rotas, criando a mesma
* \param headViagem - ponteiro para a cabeça da lista de viagens
* \param headEstacao - ponteiro para a cabeça da lista de estações
* \param headRota - ponteiro que aponta para o ponteiro da cabeça da lista de rotas
* \param tailRota - ponteiro que aponta para o ponteiro da cauda da lista de estações
*/
void LeituraRotas(NoViagem *headViagem, NoEstacao *headEstacao, NoRota **headRota, NoRota **tailRota)
{
    NoViagem *ViagemAux = NULL;
    NoEstacao *NoEstacaoI = NULL;
    NoEstacao *NoEstacaoF = NULL;
    NoRota *RotaAux = NULL;
    Rota *NovaRota = NULL;

    // Alocação de memória para a estrutura com os dados de uma rota
    NovaRota = (Rota*)malloc(sizeof(Rota));
    // Verificação da correcta alocação da memória
    if(NovaRota == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    // Alocação de memória para a estação inicial da Rota
    NovaRota->estacaoinicio = (NoEstacao*)malloc(sizeof(NoEstacao));
    // Verificação da correcta alocação da memória
    if(NovaRota->estacaoinicio == NULL)
    {
        printf("ERROR! Memory was NOT allocated\n");
        exit(EXIT_FAILURE);
    }
    // Alocação de memória para a estação final da Rota
    NovaRota->estacaofinal = (NoEstacao*)malloc(sizeof(NoEstacao));
    // Verificação da correcta alocação da memória
    if(NovaRota->estacaofinal == NULL)
    {
        printf("ERROR! Memory was NOT allocated\n");
        exit(EXIT_FAILURE);
    }


    ViagemAux = headViagem;
    // Loop que percorre todas as viagens da lista de viagens
    while(ViagemAux != NULL)
    {
        /* Loops que colocam as variaveis NoEstacaoI e NoEstacaoF a apontar para o mesmo nó que apontam
        as estações de inicio e fim da viagem, respectivamente*/
        NoEstacaoI = headEstacao;
        while(ViagemAux->Viagem.estacaoinicio->Estacao.idestacao != NoEstacaoI->Estacao.idestacao)
        {
            NoEstacaoI = NoEstacaoI->Next;
        }
        NoEstacaoF = headEstacao;
        while(ViagemAux->Viagem.estacaofinal->Estacao.idestacao != NoEstacaoF->Estacao.idestacao)
        {
            NoEstacaoF = NoEstacaoF->Next;
        }
        // Inserção de uma rota na cabeça da lista caso a mesma esteja vazia
        RotaAux = *headRota;
        if(RotaAux == NULL)
        {
            NovaRota->nviagens = 1;
            NovaRota->estacaoinicio = NoEstacaoI;
            NovaRota->estacaofinal = NoEstacaoF;
            InserirRota(headRota, tailRota, *NovaRota);
        }
        else
        {
            // Inserção de uma rota na cauda da lista
            while(RotaAux != NULL  &&  (RotaAux->Rota.estacaoinicio->Estacao.idestacao != NoEstacaoI->Estacao.idestacao  ||
            RotaAux->Rota.estacaofinal->Estacao.idestacao != NoEstacaoF->Estacao.idestacao))
            {
                RotaAux = RotaAux->Next;
            }
            if(RotaAux != NULL)
            {
                RotaAux->Rota.nviagens = RotaAux->Rota.nviagens +1;
            }
            if(RotaAux == NULL)
            {
                NovaRota->nviagens = 1;
                NovaRota->estacaoinicio = NoEstacaoI;
                NovaRota->estacaofinal = NoEstacaoF;
                InserirRota(headRota, tailRota, *NovaRota);
            }
            ViagemAux = ViagemAux->Next;
        }
    }
    free(NovaRota);
}




/** removeRota: Remove um nó da lista das rotas
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de rotas
* \param tail - ponteiro que aponta para o ponteiro da cauda da lista de rotas
* \param Rota - ponteiro para o nó da lista de viagens a eliminar
*/
void removeRota(NoRota **head, NoRota **tail, NoRota *Rota)
{
    // Verifica se a lista está vazia
    if(*head == NULL)
        printf("A lista está vazia!\n");
    // Verifica o caso em que a lista apenas contem um unico elemento
    if(*tail == Rota && *head == Rota)
    {
        free(Rota);
        *head = NULL;
        *tail = NULL;
    }
    // Verifica se o nó a remover é o primeiro nó da lista
    else if(*head == Rota)
    {
        if(Rota->Next != NULL)
        {
            (Rota->Next)->Prev = NULL;
            *head = Rota->Next;
            free(Rota);
        }
    }
    // Verifica se o nó a remover é o último nó da lista
    else if(*tail == Rota)
    {
        (Rota->Prev)->Next = NULL;
        *tail = Rota->Prev;
        free(Rota);
    }
    else
    {
        (Rota->Prev)->Next = Rota->Next;
        (Rota->Next)->Prev = Rota->Prev;
        free(Rota);
    }
}



/** LeEstacao: Lê que pede ao utilizador uma estação e verifica o id da última estação
* \param idestacao - ponteiro para a variavel que guarda o id da estação escolhida
* \param headEstacao - ponteiro para a cabeça da lista de estações
*/
void LeEstacao(int *idestacao, NoEstacao *headEstacao)
{
    NoEstacao *Estacao = NULL;
    char str[SHORTSTR] = {0};
    int flagid = 0;
    // Leitura do id da estação
    printf("Selecione o ID da estação!\n");
    getchar();
    do
    {
        fgets(str, STRING, stdin);
        sscanf(str, "%d", idestacao);
        Estacao = headEstacao;
        // Loop que verifica se a estação escolhida corresponde a alguma das estações da lista
        while(Estacao != NULL)
        {
            if(Estacao->Estacao.idestacao == *idestacao)
            {
                flagid = 1;
            }
            Estacao = Estacao->Next;
        }
        // Caso a estação escolhida não seja válida imprime uma mensagem de erro
        if(flagid == 0)
        {
            printf("A estação escolhida não consta na lista de dados!\n");
        }
    }
    while(flagid != 1);
}




/** RestringeRotas: Função que restringe as rotas da lista eliminando as que não incluem a estação escolhida
* \param headEstacao - ponteiro para a cabeça da lista de estações
* \param headRota - ponteiro para o ponteiro que aponta para a cabeça da lista de rotas
* \param tailRita - ponteiro para o ponteiro que aponta para a cauda da lista de rotas
* \param idestacao - variavel que guarda o id da estação escolhida
*/
void RestringeRotas(NoEstacao *headEstacao, NoRota **headRota, NoRota **tailRota, int idestacao)
{
    NoRota *Rota = NULL;
    NoRota *Aux = NULL;
    Rota = *headRota;
    while(Rota != NULL)
    {
        Aux = Rota->Next;
        // É efectuada a remoção da rota caso esta não inclua a estação escolhida
        if(idestacao != Rota->Rota.estacaoinicio->Estacao.idestacao  &&  idestacao != Rota->Rota.estacaofinal->Estacao.idestacao)
        {
            removeRota(headRota, tailRota, Rota);
        }
        Rota = Aux;
    }
}




/** OrdenaRotas: Função que ordena a lista de rotas
* \param headRota - ponteiro para o ponteiro que aponta para a cabeça da lista de rotas
* \param tailRita - ponteiro para o ponteiro que aponta para a cauda da lista de rotas
*/
void BubbleSortRotas(NoRota **head, NoRota **tail)
{
    int i=0;
    int j=0;
    NoRota *Aux1 = NULL;
    NoRota *Aux2 = NULL;

    // Conjunto de loops que ordenam a lista de rotas
    for(i=0; i < MAXROTAS; i++)
    {
        Aux1 = *head;
        Aux2 = Aux1->Next;
        for(j=0; j < MAXROTAS; j++)
        {
            if(Aux2 != NULL  &&  Aux1->Rota.nviagens < Aux2->Rota.nviagens)
            {
                if(Aux1 == *head)
                {
                    (Aux2->Next)->Prev = Aux1;
                    Aux1->Prev = Aux2;
                    Aux1->Next = Aux2->Next;
                    Aux2->Next = Aux1;
                    Aux2->Prev = NULL;
                    *head = Aux2;
                    Aux2 = Aux1->Next;
                }
                else if(Aux2 == *tail)
                {
                    (Aux1->Prev)->Next = Aux2;
                    Aux2->Prev = Aux1->Prev;
                    Aux2->Next = Aux1;
                    Aux1->Prev = Aux2;
                    Aux1->Next = NULL;
                    *tail = Aux1;
                    Aux2 = Aux1->Next;
                }
                else
                {
                    (Aux1->Prev)->Next = Aux2;
                    (Aux2->Next)->Prev = Aux1;
                    Aux2->Prev = Aux1->Prev;
                    Aux1->Next = Aux2->Next;
                    Aux1->Prev = Aux2;
                    Aux2->Next = Aux1;
                    Aux2 = Aux1->Next;
                }
            }

            else
            {
                if(Aux1 != NULL)
                {
                    Aux1 = Aux1->Next;
                }
                if(Aux2 != NULL)
                {
                    Aux2 = Aux2->Next;
                }
            }
        }
    }
}




/** PrintListViagens: Função que implementa o modo de listagem de viagens
* \param head - ponteiro para a cabeça da lista de viagens
*/
void PrintListViagens(NoViagem *head)
{
    NoViagem *Iterador = head;
    char str[SHORTSTR] = {0};
    int c = 0;
    int i = 1;
    int k = 0;  // Variável que guarda o número de viagens por página
    int j = 0;  // Variável que guarda o número da página
    int n = 0;  // Variavel para fazer o acerto do número da viagem ṕara a página seguinte
    int proxpag = 1;

    // Loop que lê o número de viagens que o utilizador pretende ver por página
    printf("Quantas viagens por página pretende ver?\n");
    do
    {
        fgets(str, STRING, stdin);
        sscanf(str, "%d", &k);
    }
    while(k <= 0);

    // Loop que verifica se o utilizador pretende ver mais uma página
    while(proxpag == 1)
    {
        j++;
        printf("-----------------------------------------------------------------\n");
        printf("\t\t\t Página %d\n", j);
        printf("-----------------------------------------------------------------\n");
        // Loop que é executado tantas vezes quantas as viagens que o utilizador pretende imprimir
        for(i=1; i <= k; i++)
        {
            // Verificação do caso em que se alcançou o fim da lista
            if(Iterador != NULL)
            {
                // Impressão dos dados no ecrã
                printf("Viagem %d:\n", n+i);
                printf("\tID: %d\n", Iterador->Viagem.id);
                printf("\tDuração: %d\n", Iterador->Viagem.duracao);
                printf("\tData de Início: %d/%d/%d\n", Iterador->Viagem.dinicio.mes, Iterador->Viagem.dinicio.dia, Iterador->Viagem.dinicio.ano);
                printf("\tHora de Início: %d:%d:00\n", Iterador->Viagem.tinicio.hora, Iterador->Viagem.tinicio.minuto);
                printf("\tEstação de Início: %d", Iterador->Viagem.estacaoinicio->Estacao.idestacao);
                printf("\tData de Fim: %d/%d/%d\n", Iterador->Viagem.dfinal.mes, Iterador->Viagem.dfinal.dia, Iterador->Viagem.dfinal.ano);
                printf("\tHora de Fim: %d:%d:00\n", Iterador->Viagem.tfinal.hora, Iterador->Viagem.tfinal.minuto);
                printf("\tEstação de Fim: %d\n", Iterador->Viagem.estacaofinal->Estacao.idestacao);
                printf("\tBIKEID: %s\n", Iterador->Viagem.BikeID);
                if(Iterador->Viagem.User.tipo == 1)
                {
                    printf("\tTipo de Usuário: Registado\n");
                    printf("\tAno de Nascimento do Usuário: %d\n", Iterador->Viagem.User.anonascimento);
                    if(Iterador->Viagem.User.genero == 1)
                        printf("\tGénero do Usuário: Masculino\n");
                    else
                        printf("\tGénero do Usuário: Feminino\n");
                }
                else
                    printf("\tTipo de Usuário: Casual\n");
                Iterador = Iterador->Next;
            }
        }
        printf("-----------------------------------------------------------------\n");
        printf("\t\t\t Fim da Página %d\n", j);
        printf("-----------------------------------------------------------------\n\n");
        // Verifica se o utilizador pretende ver mais uma página
        printf("Pretende ver mais uma página?\n");
        printf("Sim=1\n");
        printf("Não=0\n");
        n += k;
        do
        {
            c = getchar();
            proxpag = c-48;
        }
        while(proxpag != 0 && proxpag != 1);
    }
}



/** PrintListadeEstacoes: Função que implementa o modo de listagem de estações
* \param head - ponteiro para a cabeça da lista de estações
* \param headViagem - ponteiro para a cabeça da lista de viagens
*/
void PrintListadeEstacoes(NoEstacao *head, NoViagem *headViagem)
{
    int max = 0;
    int min = 0;
    float media = 0;
    NoEstacao *Estacao = NULL;
    Estacao = head;
    // Verifica se foi alcançado o fim da lista
    while(Estacao != NULL)
    {
        // Impressão dos dados
        printf("Estação número: %d\n", Estacao->Estacao.idestacao);
        printf("ID da estação: %s\n", Estacao->Estacao.StationID);
        printf("Descrição da estação: %s\n", Estacao->Estacao.DescricaoEstacao);
        printf("Municipio da estação: %s\n", Estacao->Estacao.municipio);
        printf("Latitude: %lf\n", Estacao->Estacao.latitude);
        printf("Longitude: %lf\n", Estacao->Estacao.longitude);
        if(Estacao->Estacao.estado == 1)
            printf("Estado da estação: Existing\n");
        else
            printf("Estado da estação: Removed\n");
        // Cálculo e impressão do maximo, minimo e media de bicicletas a partir por hora
        APartir(Estacao, headViagem, &max, &min, &media);
        printf("Máximo de bicicletas a partir por hora: %d\n", max);
        printf("Mínimo de bicicletas a paritr por hora: %d\n", min);
        printf("Média de bicicletas a partir por hora: %.2f\n", media);
        // Cálculo e impressão do máximo, minimo e media de bicicletas a chegar por hora
        AChegar(Estacao, headViagem, &max, &min, &media);
        printf("Máximo de bicicletas a chegar por hora: %d\n", max);
        printf("Mínimo de bicicletas a chegar por hora: %d\n", min);
        printf("Média de bicicletas a chegar por hora: %.2f\n\n\n", media);
        Estacao = Estacao->Next;
    }
}



/** APartir: Função que cálcula os números máximo, mínimo e médio de bicicletas a partir por hora de uma dada estação
* \param Estacao - ponteiro para a estação para a qual vão ser calculados os dados
* \param headViagem - ponteiro para a cabeça da lista de viagens
* \param max - ponteiro para o valor máximo a ser guardado
* \param min - ponteiro para o valor minimo a ser guardado
* \param float - ponteiro para a o valor médio a ser guardado
*/
void APartir(NoEstacao *Estacao, NoViagem *headViagem, int *max, int *min, float *media)
{
    float bicla = 0;
    int h = 0;
    float somabiclas = 0;
    NoViagem *Viagem = NULL;
    *max = 0;
    *min = 0;
    *media = 0;
    // Verifica para as 24 horas
    for(h=0; h<24; h++)
    {
        Viagem = headViagem;
        bicla = 0;
        // Verifica para todas as viagens, terminando quando se chega ao fim da lista
        while(Viagem != NULL)
        {
            if(Viagem->Viagem.estacaoinicio->Estacao.idestacao == Estacao->Estacao.idestacao)
            {
                if(Viagem->Viagem.tinicio.hora == h)
                    bicla ++;
            }
            Viagem = Viagem->Next;
        }
        // Guarda o valor máximo para aquela estação
        if(*max <= bicla)
            *max = bicla;
        // Guarda o valor mínimo para aquela estação
        if(h == 0 || *min >= bicla)
            *min = bicla;
        somabiclas += bicla;
    }
    *media = somabiclas/24;
}



/** AChegar: Função que cálcula os números máximo, mínimo e médio de bicicletas a chegar por hora de uma dada estação
* \param Estacao - ponteiro para a estação para a qual vão ser calculados os dados
* \param headViagem - ponteiro para a cabeça da lista de viagens
* \param max - ponteiro para o valor máximo a ser guardado
* \param min - ponteiro para o valor minimo a ser guardado
* \param float - ponteiro para a o valor médio a ser guardado
*/
void AChegar(NoEstacao *Estacao, NoViagem *headViagem, int *max, int *min, float*media)
{
    float bicla = 0;
    int h = 0;
    float somabiclas = 0;
    NoViagem *Viagem = NULL;

    *max = 0;
    *min = 0;
    *media = 0;
    // Verifica para as 24 horas
    for(h=0; h<24; h++)
    {
        Viagem = headViagem;
        bicla = 0;
        // Verifica para todas as viagens, terminando quando se chega ao fim da lista
        while(Viagem != NULL)
        {
            if(Viagem->Viagem.estacaofinal->Estacao.idestacao == Estacao->Estacao.idestacao)
            {
                if(Viagem->Viagem.tfinal.hora == h)
                    bicla ++;
            }
            Viagem = Viagem->Next;
        }
        // Guarda o valor máximo para aquela estação
        if(*max <= bicla)
            *max = bicla;
        // Guarda o valor mínimo para aquela estação
        if(h == 0 || *min >= bicla)
            *min = bicla;
        somabiclas += bicla;
    }
    *media = somabiclas/24;
}





/** PrintListRotas: Função que implementa a listagem de rotas
* \param headEstacao - ponteiro para a cabeça da lista de estações
* \param headRota - ponteiro para a cabeça da lista de rotas
* \param idestacao - id correspondente à estação escolhida pelo utilizador
*/
void PrintListRotas(NoEstacao *headEstacao, NoRota *headRota, int idestacao)
{
    NoRota *RotaAux = NULL;
    NoEstacao *Estacao = NULL;
    char c = 0;
    char str[SHORTSTR] = {0};
    int nestacoes = 0;
    int a = 0;
    int i = 0;
    int n = 0;
    int nrotas = 0;
    int proxpag = 1;


    printf("A estação escolhida foi a estação:\n");
    printf("Estação número: %d\n", idestacao);

    // Impressão dos dados da estação escolhida
    Estacao = headEstacao;
    while(Estacao != NULL)
    {
        if(Estacao->Estacao.idestacao == idestacao)
        {
            printf("\n\nID da estação: %s\n", Estacao->Estacao.StationID);
            printf("Descrição da estação: %s\n", Estacao->Estacao.DescricaoEstacao);
            printf("Municipio da estação: %s\n", Estacao->Estacao.municipio);
            printf("Latitude: %lf\n", Estacao->Estacao.latitude);
            printf("Longitude: %lf\n", Estacao->Estacao.longitude);
            if(Estacao->Estacao.estado == 1)
                printf("Estado da estação: Existing\n");
            else
                printf("Estado da estação: Removed\n");
        }
        nestacoes ++;
        Estacao = Estacao->Next;
    }

    // Leitura do número de rotas pretendidas por página
    printf("\n\nQuantas rotas pretende ver por página?\n");
    do
    {
        fgets(str, STRING, stdin);
        sscanf(str, "%d", &nrotas);
    }
    while(nrotas <= 0 || nrotas > (2*nestacoes));



    /* Loop que apenas termina quando se chega ao fim da lista de rotas ou quando o utilizador
    decide que não pretende ver mais páginas*/
    RotaAux = headRota;
    while(proxpag != 0 && RotaAux != NULL)
    {
        a ++;
        printf("--------------------------------------------------------------------------------\n");
        printf("\t\t\t\tPágina %d\n", a);
        printf("--------------------------------------------------------------------------------\n");
        // Impressão dos dados de cada rota
        for(i=1; i <=nrotas; i++)
        {
            if(RotaAux != NULL)
            {
                printf("Rota %d:\n", n+i);
                printf("\t\tNúmero de viagens para esta Rota %d\n", RotaAux->Rota.nviagens);
                printf("\t\tEstação de inicio: %s\n", RotaAux->Rota.estacaoinicio->Estacao.DescricaoEstacao);
                printf("\t\tEstação de fim: %s\n", RotaAux->Rota.estacaofinal->Estacao.DescricaoEstacao);
                if(RotaAux->Rota.estacaoinicio->Estacao.idestacao == idestacao)
                {
                    printf("\t\tEsta rota corresponde a uma rota de partida da estação escolhida\n");
                }
                else
                {
                    printf("\t\tEsta rota corresponde a uma rota de chegada à estação escolhida\n");
                }
                RotaAux = RotaAux->Next;
            }
        }
        printf("--------------------------------------------------------------------------------\n");
        printf("\t\t\t Fim da Página %d\n", a);
        printf("--------------------------------------------------------------------------------\n\n");
        // Verifica se o utilizador pretende ver mais uma página
        printf("Pretende ver mais uma página?\n");
        printf("Sim=1\n");
        printf("Não=0\n");
        n += nrotas;
        do
        {
            c = getchar();
            proxpag = c-48;
        }
        while(proxpag != 0 && proxpag != 1);
    }
}



/** StatGenero: Função que calcula o número de viagens feitas por utilizadores
* registados (género masculino, feminino e viagens totais)
* \param head - ponteiro para a cabeça da lista de viagens
*/
void StatGenero(NoViagem *head)
{
    NoViagem *Iterador = head;
    float male = 0;
    float female = 0;
    int nviagens = 0;
    while (Iterador != NULL)
    {
        if(Iterador->Viagem.User.tipo == 1 && Iterador->Viagem.User.genero == 1)
        {
            male++;
            nviagens++;
        }
        else if(Iterador->Viagem.User.tipo == 1 && Iterador->Viagem.User.genero == 0)
        {
            female++;
            nviagens++;
        }
        Iterador = Iterador->Next;
    }
    PrintStatGenero(male, female, nviagens);
}

/** PrintStatGenero: Função que calcula as percentagens de utilizadores do género
*   masculino e feminino e as imprime num ficheiro
*  \param _male - número de viagens feitas por utilizadores do género masculino
*  \param _female - número de viagens feitas por utilizadores do género feminino
*  \param _nviagens - número total de viagens;
*/
void PrintStatGenero(float _male, float _female, int _nviagens)
{
    FILE *f;
    f = fopen("EstatísticasGénero.txt", "a");
    float pmale = (_male/_nviagens) * 100;
    float pfemale = (_female/_nviagens) * 100;
    fprintf(f, "Género:\n");
    fprintf(f, "\t\tMasculino: %.2f %%\n", pmale);
    fprintf(f, "\t\tFeminino: %.2f %%\n\n", pfemale);
    fclose(f);
    printf("\nAs estatisticas feitas consoante a seleção de dados foram guardadas no ficheiro «EstatísticasGénero.txt»\n");
}

/** StatIdade: Função que calcula a idade do utilizador no caso deste ser registado,
*   e o coloca na posição correspondente do vetor de idades. Tem ainda um vetor extra
*   para os utilizadores que tenham idade acima de MAX_IDADE e abaixo de MIN_IDADE
*   \param - ponteiro para a cabeça da lista de viagens
*/
void StatIdade(NoViagem *head)
{
    NoViagem *Iterador = head;

    int users[INTERVALOS] = {0};      //vetor que guarda o número de utilizadores por intervalos de idade de 2 anos
    int extrausers[EXTRA] = {0};  //vetor que guarda o número de utilizadores com idades fora dos intervalos definidos
    int idade = 0;            //variável usada para guardar a idade do utilizador
    float nusers = 0;         //variável que conta o número de utilizadores da amostra
    int i = 0;
    while (Iterador != NULL)
    {
        idade = Iterador->Viagem.dinicio.ano - Iterador->Viagem.User.anonascimento;
        if(idade <= MAX_IDADE && idade >= MIN_IDADE && Iterador->Viagem.User.tipo == 1)
        {
            for(i=0; i<INTERVALOS; i++)
            {
                //Avalia se o número é ímpar
                if(idade%2 == 1 && idade == 2*i + 15)
                {
                    users[i] = users[i] + 1;
                }
                else if(idade%2 == 0 && idade == 2*i + 16)
                {
                    users[i] = users[i] + 1;
                }
            }
            nusers++;
        }
        else if(idade > 0 && Iterador->Viagem.User.tipo == 1)
        {
            extrausers[0] = extrausers[0] + 1;
            nusers++;
        }
        else if(idade > MAX_IDADE && Iterador->Viagem.User.tipo == 1)
        {
            extrausers[1] = extrausers[1] + 1;
            nusers++;
        }
        Iterador = Iterador->Next;
    }
    PrintStatIdade(users, extrausers, nusers);
}

/** PrintStatIdade: Função que calcula a percentagem de utilizadores para cada
*   intervalo de idade
*  \param users - vetor que contem o numero de utilizadores por intervalo de idades
*  \param extrausers - vetor que contem o numero  de utilizadores com idade superior ou inferior
*                     aos intervalos definidos;
* \param nusers - variável que contem o numero de utilizadores registados
*/
void PrintStatIdade(int users[33], int extrausers[2], float nusers)
{
    FILE *f;
    int i = 0;
    float percentagem = 0;
    int par = 0;
    int impar = 0;
    f = fopen("EstatísticasIdade.txt", "a");
    fprintf(f, "Idade:\n");
    percentagem = (extrausers[0]/nusers) * 100;
    fprintf(f, "\t\tMenos de 15 anos: %.2f %%\n", percentagem);
    for(i=0; i<33; i++)
    {
        percentagem = (users[i]/nusers)*100;
        impar = (2 * i) + 15;
        par = (2 * i) + 16;
        fprintf(f, "\t\tEntre %d e %d: %.2f %%\n", impar, par, percentagem);
    }
    percentagem = (extrausers[1]/nusers) * 100;
    fprintf(f, "\t\tMais de 80 anos: %.2f %%\n\n", percentagem);
    fclose(f);
    printf("\nAs estatisticas feitas consoante a seleção de dados foram guardadas no ficheiro «EstatísticasIdade.txt»\n");
}

void StatDuracao(NoViagem *head)
{
    NoViagem *Iterador = head;
    float duracaofloat = 0;
    int duracao = 0;
    float nviagens = 0;
    int i = 0;
    int viagens[24] = {0};
    while(Iterador != NULL)
    {
        duracaofloat = (float)Iterador->Viagem.duracao / MINUTO;
        duracao = (int)duracaofloat;
        if(duracao > 0)
        {
            for(i=0; i<24; i++)
            {
                if(duracao >= (i*15) + 1 && duracao <= (i+1) * 15)
                {
                    viagens[i] = viagens[i] + 1;
                    nviagens++;
                }
            }
        }
        Iterador = Iterador->Next;
    }
    PrintStatDuracao(viagens, nviagens);
}

void PrintStatDuracao(int viagens[24], float nviagens)
{
    float percentagem = 0; //variável para a percentagem do numero de viagens para cada intervalo de tempo
    int minintervalo = 0;
    int maxintervalo = 0;
    int hora = 0;
    int minuto = 0;
    int i = 0;
    FILE *f;
    f = fopen("EstatísticasDuração.txt", "a");
    fprintf(f, "\nDuração:\n");
    for(i=0; i<24; i++)
    {
        percentagem = (viagens[i]/nviagens) * 100;
        minintervalo = (i*15) + 1;
        hora = minintervalo / 60;
        minuto = minintervalo % 60;
        fprintf(f, "\t\tEntre %dh%dm e ", hora, minuto);
        maxintervalo = (i+1) * 15;
        hora = maxintervalo / 60;
        minuto = maxintervalo % 60;
        fprintf(f, "%dh%dm: %.2f %% \n", hora, minuto, percentagem);
    }
    fclose(f);
    printf("\nAs estatisticas feitas consoante a seleção de dados foram guardadas no ficheiro «EstatísticasDuração.txt»\n");
}

void StatVelocidade(NoViagem *headViagem)
{
    NoViagem *Iterador = headViagem;
    int i = 0;
    int idade = 0;
    double distanciam[33] = {0};
    double distanciaf[33] = {0};
    double distanciam2[2] = {0};
    double distanciaf2[2] = {0};
    double duracaom[33] = {0};
    double duracaof[33] = {0};
    double duracaom2[2] = {0};
    double duracaof2[2] = {0};
    double distancia = 0;
    double duracao = 0;
    double lat1 = 0;
    double long1 = 0;
    double lat2 = 0;
    double long2 = 0;
    while(Iterador != NULL)
    {
        if(Iterador->Viagem.User.tipo == 1)
        {
            duracao = (double)Iterador->Viagem.duracao / CONVERSOR;
            idade = Iterador->Viagem.dinicio.ano - Iterador->Viagem.User.anonascimento;
            lat1 = Iterador->Viagem.estacaoinicio->Estacao.latitude;
            lat2 = Iterador->Viagem.estacaofinal->Estacao.latitude;
            long1 = Iterador->Viagem.estacaoinicio->Estacao.longitude;
            long2 = Iterador->Viagem.estacaofinal-> Estacao.longitude;
            CalculaDistancia(lat1, long1, lat2, long2, &distancia);
            if( distancia > 0 && duracao > 0 && idade > 0)
            {
                //Avalia se a idade é ímpar
                if(idade%2 == 1 && idade <= 80 && idade >= 15)
                {
                    if(Iterador->Viagem.User.genero == 1)
                    {
                        for(i=0; i<33; i++)
                        {
                            if(idade == 2*i + 15)
                            {
                                duracaom[i] = duracaom[i] + duracao;
                                distanciam[i] = distanciam[i] + distancia;
                            }
                        }
                    }
                    else
                    {
                        for(i=0; i<33; i++)
                        {
                            if(idade == 2*i + 15)
                            {
                                duracaof[i] = duracaof[i] + duracao;
                                distanciaf[i] = distanciaf[i] + distancia;
                            }
                        }
                    }
                }
                else if(idade <= 80 && idade >= 15)
                {
                    if(Iterador->Viagem.User.genero == 1)
                    {
                        for(i=0; i<33; i++)
                        {
                            if(idade == 2*i +16)
                            {
                                duracaom[i] = duracaom[i] + duracao;
                                distanciam[i] = distanciam[i] + distancia;
                            }
                        }
                    }
                    else
                    {
                        for(i=0; i<33; i++)
                        {
                            if(idade == 2*i + 15)
                            {
                                duracaof[i] = duracaof[i] + duracao;
                                distanciaf[i] = distanciaf[i] + distancia;
                            }
                        }

                    }
                }
                else if (idade < 15)
                {
                    if(Iterador->Viagem.User.genero == 1)
                    {
                        duracaom2[0] = duracaom2[0] + duracao;
                        distanciam2[0] = distanciam2[0] + distancia;
                    }
                    else
                    {
                        duracaof2[0] = duracaof2[0] + duracao;
                        distanciaf2[0] = distanciaf2[0] + distancia;
                    }
                }
                else if(idade > 80)
                {
                    if(Iterador->Viagem.User.genero == 1)
                    {
                        duracaom2[1] = duracaom2[1] + duracao;
                        distanciam2[1] = distanciam2[1] + distancia;
                    }
                    else
                    {
                        duracaof2[1] = duracaof2[1] + duracao;
                        distanciaf2[1] = distanciaf2[1] + distancia;
                    }
                }
            }
        }
        Iterador = Iterador->Next;
    }
    PrintStatVelocidade(distanciam, distanciaf, duracaom, duracaof, distanciam2, distanciaf2, duracaom2, duracaof2);
}

void PrintStatVelocidade(double distanciam[33], double distanciaf[33],
   double duracaom[33], double duracaof[33], double distanciam2[2],
   double distanciaf2[2], double duracaom2[2], double duracaof2[2])
{
    FILE *f;
    f = fopen("EstatísticasVelocidade.txt", "a");
    double velocidadem[33] = {0};
    double velocidadef[33] = {0};
    double velocidadem2[2] = {0};
    double velocidadef2[2] = {0};
    int i = 0;
    int idade = 0;
    for(i=0; i<2; i++)
    {
        velocidadem2[i] = distanciam2[i]/duracaom2[i];
        velocidadef2[i] = distanciaf2[i]/duracaof2[i];
    }
    fprintf(f, "\nVelocidade:\n\n");
    fprintf(f, "\t\tIdade\t\t\t\tHomens");
    fprintf(f, "\t\t\t\tMulheres\n");
    fprintf(f, "\t\t< 15\t\t\t\t%.3fkm/h\t\t\t%.3fkm/h\n", velocidadem2[0], velocidadef2[0]);
    for(i=0; i<33; i++)
    {
        velocidadem[i] = distanciam[i]/duracaom[i];
        velocidadef[i] = distanciaf[i]/duracaof[i];
        idade = 2*i + 15;
        fprintf(f, "\t\t%d-%d\t\t\t\t%.3fkm/h\t\t\t%.3fkm/h\n", idade, idade+1, velocidadem[i], velocidadef[i]);
    }
    fprintf(f, "\t\t> 80\t\t\t\t%.3fkm/h\t\t\t%.3fkm/h\n", velocidadem2[1], velocidadef2[1]);
    fclose(f);
    printf("\nAs estatisticas feitas consoante a seleção de dados foram guardadas no ficheiro «EstatísticasVelocidade.txt»\n");
}

void CalculaDistancia(double lat1, double long1, double lat2, double long2, double *distancia)
{
    double rad = (PI/180);
    double vlat = 0;
    double vlong = 0;
    double a, c = 0;
    lat1 = lat1*rad;
    lat2 = lat2*rad;
    long1 = long1*rad;
    long2 = long2*rad;
    vlat =  lat2 - lat1;
    vlong = long2 - long1;
    a = sin(vlat/2) * sin (vlat/2) + cos(lat1) * cos(lat2) * sin(vlong/2) * sin(vlong/2);
    c = 2 * atan2((sqrt(a)), (sqrt((1-a))));
    *distancia = R * c;
}
