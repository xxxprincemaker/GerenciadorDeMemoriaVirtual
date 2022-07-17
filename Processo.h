//
// Created by VipSo on 7/5/2022.
//
#include "TabelaDePaginas.h"
#define WORKINGSETLIMIT 4;

static int PID = 0;

typedef struct Processo{
    int PID;
    TabelaDePaginas *tabelaDePaginas;
    int workingset;

} Processo;

typedef struct Pagina{
    Processo* proc;
    int index;
} Pagina;

Processo* criarProcesso(){
    Processo* processo = (Processo*) malloc(sizeof(Processo));
    processo->PID = PID+1;
    processo->tabelaDePaginas = criarTabelaDePaginas();
    processo->workingset = 0;
}

int getWorkingSet(Processo *p)
{
    return p->workingset;
}

int getPID(Processo *p)
{
    return p->PID;
}

TabelaDePaginas * getTabelaDePaginas(Processo *p)
{
    return p->tabelaDePaginas;
}