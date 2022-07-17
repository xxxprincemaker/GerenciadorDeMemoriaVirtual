#include <stdlib.h>
#include <stdio.h>
#include "timer.c"
#include "GerenciadorDeMV.h"


int main(){
    GerenciadorDeMV* gmv = criaGMV();
    Processo* proc = criarProcesso();
    
    mostraTabela(proc->tabelaDePaginas);

    imprimeMemoriaPrincipal(gmv->mp);

    acessaPagina(gmv, proc, 10);

    mostraTabela(proc->tabelaDePaginas);

    imprimeMemoriaPrincipal(gmv->mp);

    tiraPagDaMP(gmv, proc, 10);

    mostraTabela(proc->tabelaDePaginas);

    imprimeMemoriaPrincipal(gmv->mp);

    return 0;
}