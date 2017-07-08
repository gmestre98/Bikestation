#include <stdio.h>
#include <stdlib.h>
#include "SelecaoDados.h"


/** removeViagem: Remove um nó da lista das viagens
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de viagens
* \param tail - ponteiro que aponta para o ponteiro da cauda da lista de viagens
* \param Viagem - ponteiro para o nó da lista de viagens a eliminar
*/
void removeViagem(NoViagem **head, NoViagem **tail, NoViagem *Viagem)
{
    // Verifica se a lista está vazia
    if(*head == NULL)
        printf("A lista está vazia!\n");
    // Verifica o caso em que a lista apenas contem um unico elemento
    if(*tail == Viagem && *head == Viagem)
    {
        *head = NULL;
        *tail = NULL;
    }
    // Verifica se o nó a remover é o primeiro nó da lista
    else if(*head == Viagem)
    {
        if(Viagem->Next != NULL)
        {
            (Viagem->Next)->Prev = NULL;
            *head = Viagem->Next;
        }
    }
    // Verifica se o nó a remover é o último nó da lista
    else if(*tail == Viagem)
    {
        (Viagem->Prev)->Next = NULL;
        *tail = Viagem->Prev;
    }
    else
    {
        (Viagem->Prev)->Next = Viagem->Next;
        (Viagem->Next)->Prev = Viagem->Prev;
    }
    free(Viagem);
}



/** Remocao: Aplica os critérios da seleção de dados, removendo nós da lista de
*   viagens consoante os valores selecionados
* \param head - ponteiro que aponta para o ponteiro da cabeça da lista de viagens
* \param tail - ponteiro que aponta para o ponteiro da cauda da lista de viagens
* \param inicio - ponteiro para a hora de inicio selecionada
* \param fim - ponteiro para a hora de fim selecionada
* \param duracao - guarda o valor da duração escolhida
* \param dia - guarda o valor correspondente ao número do dia escolhido
* \param t - flag que guarda 1 caso tenha existido seleção de hora
*/
void Remocao(NoViagem **head, NoViagem **tail, momento *inicio, momento *fim, long int duracao, int dia, int t)
{
    NoViagem *Iterador = *head;
    NoViagem *Aux = NULL;
    int diainicio = 0;
    int diafim = 0;
    int q = 0;
    int m = 0;
    int ano = 0;
    int flaghorainicio = 0;
    int flaghorafim = 0;
    // Verifica se não há mais nenhum elemento a analisar
    while(Iterador != NULL)
    {
        // Guarda o valor do próximo nó a analisar
        Aux = Iterador->Next;
        // Verificação pela flag t se foi selecionado algum período de tempo especifico
        if(t != 0)
        {
            // Verifica se o valor da hora de inicio escolhida é violado pela hora de inicio do nó
            if(Iterador->Viagem.tinicio.hora < inicio->hora || ((Iterador->Viagem.tinicio.hora == inicio->hora) && (Iterador->Viagem.tinicio.minuto < inicio->minuto)))
            {
                flaghorainicio = 1;
            }
            // Verifica se o valor da hora de fim escolhida é violado pela hora de inicio do nó
            if(Iterador->Viagem.tinicio.hora > fim->hora || ((Iterador->Viagem.tinicio.hora == fim->hora) && (Iterador->Viagem.tinicio.minuto > fim->minuto)))
            {
                flaghorafim = 1;
            }
            // Verifica se o valor da hora de inicio escolhida é violado pela hora de fim do nó
            if(Iterador->Viagem.tfinal.hora < inicio->hora || ((Iterador->Viagem.tfinal.hora == inicio->hora) && (Iterador->Viagem.tfinal.minuto < inicio->minuto)))
            {
                flaghorainicio = 1;
            }
            // Verifica se o valor da hora de fim escolhida é violado pela hora de fim do nó
            if(Iterador->Viagem.tfinal.hora > fim->hora || ((Iterador->Viagem.tfinal.hora == fim->hora) && (Iterador->Viagem.tfinal.minuto > fim->minuto)))
            {
                flaghorafim = 1;
            }
            // É feita a remoção do nó caso o mesmo não pertença ao intervalo escolhido
            if(flaghorainicio != 0 || flaghorafim != 0)
            {
                removeViagem(head, tail, Iterador);
                flaghorainicio = 0;
                flaghorafim = 0;
            }
        }
        // Verifica se foi selecionado algum dia especifico
        if(dia != 0)
        {
            // Conversão do dia inicial guardado na estrutura num dia da semana
            q = Iterador->Viagem.dinicio.dia;
            m = Iterador->Viagem.dinicio.mes;
            ano = Iterador->Viagem.dinicio.ano;
            diainicio = ConverterDia(q, m, ano);

            // Conversão do dia final guardado na estrutura num dia da semnana
            q = Iterador->Viagem.dfinal.dia;
            m = Iterador->Viagem.dfinal.mes;
            ano = Iterador->Viagem.dfinal.ano;
            diafim = ConverterDia(q, m, ano);

            // Remoção da lista caso a viagem não tenha sido efectuada no dia da semana definido
            if((diainicio != dia) && (diafim != dia))
            {
                removeViagem(head, tail, Iterador);
            }
        }
        // Verifica se foi selecionada alguma duração máxima para a  viagem
        if(duracao != -1)
        {
            // Remove a viagem caso a duração da mesma seja superior à definida pelo o utilizador
            if(Iterador->Viagem.duracao > duracao)
            {
                removeViagem(head, tail, Iterador);
            }
        }
        // Passa para o próximo nó da lista
        Iterador = Aux;
    }

}



/** PeriodoTempo: Faz a leitura do período de tempo escolhido pelo
* \param inicio - ponteiro para a hora de inicio a ser selecionada
* \param fim - ponteiro para a hora de fim a ser selecionada
* \param t - ponteiro para a flag que guarda 1 caso tenha existido seleção de hora
*/
void PeriodoTempo(momento* inicio, momento* fim, int *t)
{
    char str[SHORTSTR] = {0};
    int hinicio=0;
    int minicio=0;
    int hfim=0;
    int mfim=0;

    // Leitura do periodo de tempo inicial para uma string e conversao da mesma em dois inteiros(hora e minuto)
    // Este loop também verifica se os valores selecionados são válidos
        printf("Introduza uma hora de início para a viagem no formato hh:mm!\n");
    do
    {
        getchar();
        fgets(str, STRING, stdin);
        sscanf(str, "%d:%d", &hinicio, &minicio);
    }
    while(hinicio<0 || hinicio>23 || minicio<0 || minicio>59);

    // Leitura do periodo de tempo final para uma string e conversao da mesma em dois inteiros(hora e minuto)
    // Este loop verifica também se os valores selecionados são válidos
        printf("Introduza uma hora de fim para a viagem no formato hh:mm!\n");
    do
    {
        fgets(str, STRING, stdin);
        sscanf(str, "%d:%d", &hfim, &mfim);
    }
    while(hfim<hinicio || hfim>23 || mfim<0 || mfim>59 || (hinicio==hfim && mfim<=minicio));

    // Guarda os valores selecionados pelo utilizador numa estrutura de dados
    inicio->hora=hinicio;
    inicio->minuto=minicio;
    fim->hora=hfim;
    fim->minuto=mfim;
    *t=1;
}



/** DiadaSemana - Faz a leitura do dia da semana escolhido pelo utilizador
* \param dia - ponteiro para a variavel que guarda o valor correspondente ao dia da semana escolhido
*/
void DiadaSemana(int *dia)
{
    char c = 0;
        printf("Introduza o número correspondente ao dia da semana que pretende!\n\n");
        printf("Segunda-Feira - 1\n");
        printf("Terça-Feira - 2\n");
        printf("Quarta-Feira - 3\n");
        printf("Quinta-Feira - 4\n");
        printf("Sexta-Feira - 5\n");
        printf("Sábado - 6\n");
        printf("Domingo - 7\n");
    // Loop que pede o dia da semana e só permite a saida do mesmo quando introduzido pelo utilizador um dia valido
    do
    {
        c = getchar();
        *dia = c -48;
    }
    while(*dia<1 || *dia>7);
}


/** DuracaoMaxima - Faz a leitura da duração máxima para as viagens escolhida pelo utilizador
* \param duracao - ponteiro para a variavel que guarda o valor da duração escolhida
*/
void DuracaoMaxima(long int *duracao)
{
    char str[SHORTSTR] = {0};
    printf("Introduza um valor para a duração máxima das viagens!\n");
    do
    {
        fgets(str, STRING, stdin);
        sscanf(str, "%ld", duracao);
    }
    while(*duracao < 0);
}



/** ResetSelecao: Faz o reset dos dados selecionados
* \param inicio - ponteiro para a hora de inicio selecionada
* \param fim - ponteiro para a hora de fim selecionada
* \param duracao - ponteiro para a variavel que guarda o valor da duração escolhida
* \param dia - ponteiro para a variavel que guarda o valor correspondente ao número do dia escolhido
* \param t - ponteiro para a flag que guarda 1 caso tenha existido seleção de hora
*/
void ResetSelecao(momento *inicio, momento *fim, int *dia, long int *duracao, int *t)
{
    /* Volta a alocar a memória para as estruturas de hora de inicio e de fim, libertando
    a anterior de modo a reiniciar os valores*/
    free(inicio);
    inicio = NULL;
    inicio = (momento*)malloc(sizeof(momento));
    // Verifica se a memória foi correctamente alocada
    if(inicio == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    free(fim);
    fim = NULL;
    fim = (momento*)malloc(sizeof(momento));
    // Verifica se a memória foi correctamente alocada
    if(fim == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    // reset das variaveis dia, duracao e t para os valores iniciais
    *dia = 0;
    *duracao = -1;
    *t=0;
}


// Função que faz a conversão de um dia do ano para um dia da semana
/** ConverterDia - Faz a conversão de um dia do ano para um dia da semana
* \param q - Dia do mês correspondente à data a converter
* \param m - Mês do ano correspondente à data a converter
* |param ano - Ano correspondente à data a converter
*/
int ConverterDia(int q, int m, int ano)
{
    int h, k, j=0;
    /*
      O algoritmo apresentado para o cálculo do dia da semana e uma adaptação da congruência de Zeller
      A congruência de Zeller original é:
          h = ((q + ((m+1)*26)/10 + k + k/4 + j/4 + 5*j))%7;

      h - dia da semana (0=sábado, 1=domingo, 2=segunda, ...)
      q - dia do mês
      m - mês (3=março, 4=abril, 5=maio, ...)(janeiro e fevereiro são os meses
          13 e 14 do ano anterior, respetivamente)
      k - ano do século (ano%100)
      j - século (ano/100)(Não corresponde a escala normal dos séculos! Exemplo:
          1995 realizando a divisão por 100 corresponde ao século 19, mas na realidade)
          é o século 20)

      A nossa alteração ao programa consiste em subtrair 2 antes de realizar a operação módulo(%7). Desta forma
      alteramos a correspondência entre os valores de h e os dias da semana, isto é, em vez de 0 corresponder
      a sábado, passa a corresponder a segunda, 1 corresponde a terça, etc...). No fim do cálculo de h, incrementamos
      o seu valor para que fique compreendido entre 1 e 7 (antes encontrava-se entre 0 e 6). Deste modo, a correspondência
      entre h e os dias da semana é novamente alterada: 1=segunda, 2=terça, 3=quarta, etc...

      */


    // janeiro e fevereiro sao os meses 13 e 14 do ano anterior
    if ( m == 1 || m == 2)
    {
        m = m + 12;
        ano = ano - 1;
    }

    // K é o ano do século
    k = ano%100;

    // J é o século (não corresponde à realidade)
    j = ano/100;

    h = ((q + ((m+1)*26)/10 + k + k/4 + j/4 + 5*j)-2)%7;
    h = h+1;


    // Retorna o valor correspondente ao dia da semana encontrado
    return h;
}
