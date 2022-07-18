#include <stdlib.h>
#include <stdio.h>
#include "timer.c"
#include "GerenciadorDeMV.h"

#define MAX_PROC 20

int main(int argc, char **argv){
    GerenciadorDeMV *gmv = criaGMV();
    Processo **processos = (Processo**) err_malloc(sizeof(Processo*) * MAX_PROC);
    int proc_count = 0, time_limit = 120;

    if(argc >= 2) time_limit = atoi(argv[1]);

    srand(time(NULL));

    while(1) {
        if(t > time_limit) break;

        if(proc_count < MAX_PROC) {
            processos[proc_count++] = criarProcesso();
            printf("[%03d] Processo #%d criado (%d processo(s))\n", t, proc_count-1, proc_count);
        }

        for(int i = 0; i < proc_count; i++) {
            int r = rand() % MAXPAGINAS;

            acessaPagina(gmv, processos[i]->paginas[r]);

            printf("[%03d] Tabela de páginas do Processo #%d:\n", t, i);
            mostraTabela(processos[i]->tabelaDePaginas);
        }

        t += 3;
        sleep(3);
    }

    printf("\nMemória Principal:\n");
    imprimeMemoriaPrincipal(gmv->mp);

    return 0;
}