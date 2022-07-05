//
// Created by VipSo on 7/5/2022.
//
#include "TabelaDePaginas.h"
#define WORKINGSETLIMIT 4;

static int PID = 0;

typedef struct Processo{
    int PID;
    TabelaDePaginas * tabelaDePaginas;
    int workingset;

} Processo;

void criarProcesso(Processo *processo){
    processo->PID = PID+1;
    processo->tabelaDePaginas = criarTabelaDePaginas();
    processo->workingset = 0;
}

void mostrarPaginaProcesso(TabelaDePaginas *tabelaDePaginas){
    printf("\033[34mProcesso\t| Inicio\t| T. de Servico\t| Tipo de IO\t| Inicio do IO\t| STATUS \t| PRIRD.|\033[0m\n");
}