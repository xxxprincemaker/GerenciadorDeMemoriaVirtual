//
// Created by VipSo on 7/5/2022.
//
#include "Pagina.h"
#include "TabelaDePaginas.h"
#include "LRUQueue.h"
#define WORKINGSETLIMIT 2

static int PID = 0;

typedef struct Processo{
    int PID;
    TabelaDePaginas *tabelaDePaginas;
    Pagina **paginas;
    int workingset;
    LRUQueue *queue;
} Processo;

Processo* criarProcesso(){
    Processo* processo = (Processo*) malloc(sizeof(Processo));
    processo->PID = PID+1;
    processo->tabelaDePaginas = criarTabelaDePaginas();
    processo->paginas = (Pagina**) malloc(sizeof(Pagina*) * MAXPAGINAS);
    if(!processo->paginas) printf("Não malocou irmão");
    for(int i = 0; i < MAXPAGINAS; i++){
        processo->paginas[i] = criarPagina(processo);
        setIndex(processo->paginas[i], i);
    }
    processo->workingset = 0;
    processo->queue = criaLRUQueue();
    printf("\n\n\n%x\n\n\n", processo->paginas);
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
