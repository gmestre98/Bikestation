#include <stdio.h>
#include <stdlib.h>
#include "Listas.h"

void removeViagem(NoViagem **, NoViagem**, NoViagem *);
void PeriodoTempo(momento*, momento*, int*);
void DiadaSemana(int *);
void DuracaoMaxima(long int *);
void ResetSelecao(momento*, momento*, int*, long int*, int*);
void Remocao(NoViagem **, NoViagem **, momento *, momento *,long int, int, int);
int ConverterDia(int, int, int);
