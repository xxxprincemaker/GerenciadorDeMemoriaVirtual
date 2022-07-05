//
// Created by VipSo on 7/5/2022.
//
#include "TabelaDePaginas.h"

typedef struct Processo{
    int PID;
    TabelaDePaginas tabelaDePaginas;
    int frames;
    int workingset;
} Processo;
