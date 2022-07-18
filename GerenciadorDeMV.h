#include "Processo.h"
#define TAM_MP 64

int t = 0;

typedef struct MemoriaPrincipal{
    int count;
    Pagina **frames;
} MemoriaPrincipal;

typedef struct GerenciadorDeMV{
    MemoriaPrincipal *mp;
    LRUQueue *queue;
} GerenciadorDeMV;


MemoriaPrincipal* criaMP() {
    MemoriaPrincipal *mp = (MemoriaPrincipal*) err_malloc(sizeof(MemoriaPrincipal));
    mp->count = 0;
    mp->frames = (Pagina**) err_malloc(sizeof(Pagina*) * TAM_MP);
    for(int i = 0; i < TAM_MP; i++){
        mp->frames[i] = NULL;
    }
    return mp;
}

GerenciadorDeMV* criaGMV() {
    GerenciadorDeMV *gmv = (GerenciadorDeMV*) err_malloc(sizeof(GerenciadorDeMV));
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

Pagina *tiraPagDeProcLRU(GerenciadorDeMV *gmv, Processo *proc) {
    Pagina *pagina_retirada;

    pagina_retirada = dequeue(proc->queue);

    removeQueue(gmv->queue, pagina_retirada);

    tiraPagDaMP(gmv, pagina_retirada);

    return pagina_retirada;
}

Pagina *tiraPagDaMPLRU(GerenciadorDeMV *gmv) {
    Pagina *pagina_retirada;
    
    pagina_retirada = dequeue(gmv->queue);

    tiraPagDaMP(gmv, pagina_retirada);

    return pagina_retirada;
}

int acessaPagina(GerenciadorDeMV *gmv, Pagina *pagina) {
    printf("[%03d] Processo #%d pede acesso a página %d (P#%d.%d)\n", t, pagina->proc->PID, pagina->index, pagina->proc->PID, pagina->index);

    // Atualiza as filas de LRU tanto da mémoria inteira quanto do processo
    enqueue(gmv->queue, pagina);
    enqueue(pagina->proc->queue, pagina);
    
    if( !getPresenca(pagina->proc->tabelaDePaginas, pagina->index) ) {
        printf("[%03d] (PAGE MISS) Página P#%d.%d não está na MP\n", t, pagina->proc->PID, pagina->index);
        if( pagina->proc->workingset == WORKINGSETLIMIT ) {
            Pagina *pagina_retirada = tiraPagDeProcLRU(gmv, pagina->proc);
            printf("[%03d] (WORKING SET LIMIT ATINGIDO) Página P#%d.%d removida da MP\n", t, pagina_retirada->proc->PID, pagina_retirada->index);
        } else if( memoriaCheia(gmv->mp) ) {
            Pagina *pagina_retirada = tiraPagDaMPLRU(gmv);
            printf("[%03d] (MEMÓRIA CHEIA) Página P#%d.%d removida da MP\n", t, pagina_retirada->proc->PID, pagina_retirada->index);
        }
        int frame = colocaPagNaMP(gmv, pagina);
        printf("[%03d] Página P#%d.%d colocada no frame %d\n", t, pagina->proc->PID, pagina->index, frame);
        return frame;
    } else {
        int frame = getFrame(pagina->proc->tabelaDePaginas, pagina->index);
        printf("[%03d] (PAGE HIT) Página P#%d.%d encontrada no frame %d\n", t, pagina->proc->PID, pagina->index, frame);
        return frame;
    }

}