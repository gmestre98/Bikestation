#include <stdio.h>
#include <stdlib.h>
#include "Menus.h"


/** ModoTextual: Executa o modo textual e todos os menus pertencentes
* \param headViagem - ponteiro que aponta para o ponteiro da cabeça da lista de viagens
* \param tailViagem - ponteiro que aponta para o ponteiro da cauda da lista de viagens
* \param ftripdata - ponteiro para o ficheiro com os dados das viagens
* \param fstationdata - ponteiro para o ficheiro com os dados das estações
* \param argc - guarda o número de argumentos do programa
* \param argv - ponteiro para os argumentos do programa
* \param headEstacao - ponteiro para a cabeça da lista de estações
* \param headRota - ponteiro que aponta para o ponteiro da cabeça da lista de rotas
* \param tailRota - ponteiro que aponta para o ponteiro da cauda da lista de rotas
*/
void ModoTextual(NoViagem **headViagem, NoViagem **tailViagem, FILE *ftripdata, FILE *fstationdata,
                 int argc, char *argv[], NoEstacao *headEstacao, NoRota **headRota, NoRota **tailRota)
{
    char c = 0;
    int fimprog = 0;
    long int duracao = -1;
    int t = 0;
    int diadasemana = 0;
    int opcao = 0;
    int estatisticas = 0;
    int idestacao = 0;
    momento *horainicio=NULL;
    momento *horafim=NULL;
    // Alocação de memória para as estruturas que guardam a hora de inicio e de fim selecionadas
    horainicio = (momento*)malloc(sizeof(momento));
    // Verificação da correcta alocação da memória
    if(horainicio == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    horafim = (momento*)malloc(sizeof(momento));
    // Verificação da correcta alocação da memória
    if(horafim == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }

    // Loop que verifica se o utilizador pretende continuar o programa no fim da execução de uma operação
    while(fimprog == 0)
    {
        Apresentacao(&opcao);
        if(opcao == 1)
        {
            // Execução da seleção de dados
            Opcao1(horainicio, horafim, headViagem, tailViagem, ftripdata, fstationdata, argc, argv,
                   &t, &diadasemana, &duracao, headEstacao);
        }
        if(opcao == 2)
        {
            // Execução da listagem de viagens
            PrintListViagens(*headViagem);
        }
        if(opcao == 3)
        {
            // Execução da listagem de estações
            PrintListadeEstacoes(headEstacao, *headViagem);
        }
        if(opcao == 4)
        {
            // Execução da listagem de rotas
            LeituraRotas(*headViagem, headEstacao, headRota, tailRota);
            LeEstacao(&idestacao, headEstacao);
            RestringeRotas(headEstacao, headRota, tailRota, idestacao);
            BubbleSortRotas(headRota, tailRota);
            PrintListRotas(headEstacao, *headRota, idestacao);
        }
        if(opcao == 5)
        {
            // Execução do menu para a Listagem de Estatísticas
            printf("Escolheu a Listagem de Estatísticas!\n");
            printf("Escolha uma das seguintes opções escrevendo o número correspondente!\n");
            printf("1. Estatísticas por género\n");
            printf("2. Estatísticas da idade\n");
            printf("3. Estatísticas da duração\n");
            printf("4. Estatísticas da velocidade\n");
            do{
                c = getchar();
                estatisticas = c - 48;
            }while(estatisticas > 4 || estatisticas < 1);
            if(estatisticas == 1)
            {
                StatGenero(*headViagem);
            }
            if(estatisticas == 2)
            {
                StatIdade(*headViagem);
            }
            if(estatisticas == 3)
            {
                StatDuracao(*headViagem);
            }
            if(estatisticas == 4)
            {
                StatVelocidade(*headViagem);
            }
        }
        printf("Pretende terminar o Programa?\n");
        printf("Sim=1\n");
        printf("Não=0\n");
        do{
        c = getchar();
        fimprog = c - 48;
        }while(fimprog != 0 && fimprog != 1);
        // Execução da função que implementa a seleção de dados
        Remocao(headViagem, tailViagem, horainicio, horafim, duracao, diadasemana, t);
    }
}

// Função que lê a opção a ser escolhida no inicio do modo textual


/** Apresentacao: Lê a opção a ser escolhida no inicio do modo textual
* \param opcao - ponteiro para a variavel guarda o valor da opção escolhida
*/
void Apresentacao(int *opcao)
{
    char c = 0;
    // Escrita do texto inicial no ecrã
    printf("BEM VINDO AO MODO TEXTUAL DO BIKESTATION!\n\n");
    printf("Escolheu executar o programa no modo textual!\n");
    printf("Se pretender executar no modo gráfico use -g em vez de -t\n\n\n");
    printf("Pode utilizar cada uma das seguintes opções:\n");
    printf("1. Seleção de Dados\n");
    printf("2. Listagem de Viagens\n");
    printf("3. Listagem de Estações\n");
    printf("4. Listagem de Rotas\n");
    printf("5. Listagem de Estatísticas\n\n");
    printf("Insira o número correspondente à opção que pretende seguir!\n");
    do
    {
        c = getchar();
        *opcao = c -48;
    }while(*opcao > 5 || *opcao < 1);
}

// Função que executa a seleção de dados
/** Opcao1: Executa a seleção de dados
* \param inicio - ponteiro para a hora de inicio selecionada
* \param fim - ponteiro para a hora de fim selecionada
* \param headViagem - ponteiro que aponta para o ponteiro da cabeça da lista de viagens
* \param tailViagem - ponteiro que aponta para o ponteiro da cauda da lista de viagens
* \param ftripdata - ponteiro para o ficheiro com os dados das viagens
* \param fstationdata - ponteiro para o ficheiro com os dados das estações
* \param argc - guarda o número de argumentos do programa
* \param argv - ponteiro para os argumentos do programa
* \param t - ponteiro para a flag que guarda 1 caso tenha existido seleção de hora
* \param dia - ponteiro para a variavel guarda o valor correspondente ao número do dia escolhido
* \param duracao - ponteiro para a variavel guarda o valor da duração escolhida
* \param headEstacao - ponteiro para a cabeça da lista de estações
*/
void Opcao1(momento *horainicio, momento *horafim, NoViagem **headViagem, NoViagem **tailViagem, FILE *ftripdata,
            FILE *fstationdata, int argc, char *argv[], int *t, int *diadasemana, long int *duracao, NoEstacao *headEstacao)
{
    char c = 0;
    int continuaselecao=0;
    int limpeza=0;
    int selecao=0;
    char str[STRING] = {0};
    NoViagem *Iterador = NULL;
    NoViagem *Aux = NULL;
    NoViagem *Aux1 = NULL;
    NoViagem *Aux2 = NULL;

    do
    {
        // Decisão de limpeza ou não dos dados da lista
        printf("\n\nEscolheu a seleção de dados!\n");
        printf("Pretende limpar os critérios previamente escolhidos?\n");
        printf("Não=0 e Sim=1\n");
        do{
        c = getchar();
        limpeza = c - 48;
        }while(limpeza != 0 && limpeza != 1);

        // Reset dos valores selecionados
        // Remoção de todos os nós da lista de viagens e nova leitura do ficheiro
        if(limpeza == 1)
        {
            ResetSelecao(horainicio, horafim, diadasemana, duracao, t);
            Iterador = *headViagem;
            while(Iterador != NULL)
            {
                Aux = Iterador->Next;
                removeViagem(headViagem, tailViagem,Iterador);
                Iterador = Aux;
            }
            AbrirFicheiros(&ftripdata, &fstationdata, argc, argv);
            while(fgets(str, MAXSTR, ftripdata) != NULL)
            {
                *tailViagem=TripToList(ftripdata, headViagem, *tailViagem, str, headEstacao);
            }
            Aux1 = *headViagem;
            while(Aux1 != NULL)
            {
                Aux2 = Aux1->Next;
                if(strcmp(Aux1->Viagem.BikeID, "Casual") == 0 || strcmp(Aux1->Viagem.BikeID, "Registered") == 0)
                {
                    removeViagem(headViagem, tailViagem, Aux1);
                }
                Aux1 = Aux2;
            }
        }

        // Lê que tipo de seleção se pretende fazer aos dados
        printf("\nPode selecionar dados consoante:\n");
        printf("1. Período de Tempo\n");
        printf("2. Dia da Semana\n");
        printf("3. Duração\n");
        printf("Introduza o número da operação que pretende seguir!\n");
        do{
            c = getchar();
            selecao = c -48;
        }while(selecao > 3 || selecao < 1);

        // Leitura da seleção por periodo de tempo
        if(selecao == 1)
        {
                printf("\nIntroduza um período de tempo válido, com hora de inicio inferior à hora de fim!\n");
                PeriodoTempo(horainicio, horafim, t);
                printf("Pretende continuar a fazer selecao de dados?\n");
                printf("Não=0 e Sim=1\n");
            do{
                c = getchar();
                continuaselecao = c -48;
            }while(continuaselecao != 0 && continuaselecao != 1);
        }

        // Leitura da seleção por dia da semana
        if(selecao == 2)
        {
                DiadaSemana(diadasemana);
                printf("Pretende continuar a fazer selecao de dados?\n");
                printf("Não=0 e Sim=1\n");
            do{
                c = getchar();
                continuaselecao = c -48;
            }while(continuaselecao != 0 && continuaselecao != 1);
        }

        // Leitura da seleção por duração
        if(selecao == 3)
        {
                DuracaoMaxima(duracao);
                printf("Pretende continuar a fazer selecao de dados?\n");
                printf("Não=0 e Sim=1\n");
            do{
                c = getchar();
                continuaselecao = c -48;
            }while(continuaselecao != 0 && continuaselecao != 1);
        }
    }
    while(continuaselecao == 1);
}
