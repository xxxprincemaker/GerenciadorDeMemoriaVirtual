#include "Processo.h"
#define TAM_MP 10

typedef struct MemoriaPrincipal{
    int count;
    Pagina **frames;
} MemoriaPrincipal;

typedef struct GerenciadorDeMV{
    MemoriaPrincipal *mp;
    LRUQueue *queue;
} GerenciadorDeMV;


MemoriaPrincipal* criaMP() {
    MemoriaPrincipal *mp = (MemoriaPrincipal*) malloc(sizeof(MemoriaPrincipal));
    mp->count = 0;
    mp->frames = (Pagina**) malloc(sizeof(Pagina*) * TAM_MP);
    for(int i = 0; i < TAM_MP; i++){
        mp->frames[i] = NULL;
    }
    return mp;
}

GerenciadorDeMV* criaGMV() {
    GerenciadorDeMV *gmv = (GerenciadorDeMV*) malloc(sizeof(GerenciadorDeMV));
    gmv->mp = criaMP();
    gmv->queue = criaLRUQueue();
    return gmv;
}

int memoriaCheia(MemoriaPrincipal *mp) {
    return mp->count == TAM_MP;
}

void imprimeMemoriaPrincipal(MemoriaPrincipal *mp) {
    printf("|Frame\t| Página\t|\n");

    for(int i = 0; i < TAM_MP; i++) {
        if( mp->frames[i] != NULL )
            printf("|%d\t| P#%d.%d \t|\n", i, mp->frames[i]->proc->PID, mp->frames[i]->index);
        else
            printf("|%d\t| -\t\t|\n", i);
    }

}

int colocaPagNaMP(GerenciadorDeMV *gmv, Pagina *pagina) {
    int frame;

    setPresenca(pagina->proc->tabelaDePaginas, pagina->index, 1);
    pagina->proc->workingset++;

    for(int i = 0; i < TAM_MP; i++){
        if(gmv->mp->frames[i] == NULL) {
            gmv->mp->frames[i] = pagina;
            gmv->mp->count++;
            frame = i;
            break;
        }
    }
    
    setFrame(pagina->proc->tabelaDePaginas, pagina->index, frame);
    return frame;
}

void tiraPagDaMP(GerenciadorDeMV *gmv, Pagina *pagina) {
    if( !getPresenca(pagina->proc->tabelaDePaginas, pagina->index) ) { 
        printf("[Erro] Tentou remover página que não estava na MP");
        exit(-1);
    }

    int frame = getFrame(pagina->proc->tabelaDePaginas, pagina->index);
    setPresenca(pagina->proc->tabelaDePaginas, pagina->index, 0);
    pagina->proc->workingset--;
    gmv->mp->frames[frame] = NULL;
    gmv->mp->count--;
}

void tiraPagDeProcLRU(GerenciadorDeMV *gmv, Processo *proc) {
    Pagina *pagina_retirada;

    pagina_retirada = dequeue(proc->queue);

    removeQueue(gmv->queue, pagina_retirada);

    tiraPagDaMP(gmv, pagina_retirada);
}

void tiraPagDaMPLRU(GerenciadorDeMV *gmv) {
    Pagina *pagina_retirada;
    
    pagina_retirada = dequeue(gmv->queue);

    tiraPagDaMP(gmv, pagina_retirada);
}

int acessaPagina(GerenciadorDeMV *gmv, Pagina *pagina) {
    printf("enqueue gmv\n");
    //enqueue(gmv->queue, pagina);
    printf("enqueue proc\n");
    //enqueue(pagina->proc->queue, pagina);
    if( !getPresenca(pagina->proc->tabelaDePaginas, pagina->index) ) {
        if( pagina->proc->workingset == WORKINGSETLIMIT ) {
            tiraPagDeProcLRU(gmv, pagina->proc);
        } else if( memoriaCheia(gmv->mp) ) {
            tiraPagDaMPLRU(gmv);
        } 
        return colocaPagNaMP(gmv, pagina);
    } else {
        return getFrame(pagina->proc->tabelaDePaginas, pagina->index);
    }

}