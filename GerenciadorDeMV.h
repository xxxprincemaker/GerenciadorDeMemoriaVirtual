#include "Processo.h"

#define TAM_MP 10

// TODO - Ao invés de usar um int *frames usar um Pagina **frames
typedef struct MemoriaPrincipal{
    int *frames;
} MemoriaPrincipal;

typedef struct GerenciadorDeMV{
    MemoriaPrincipal *mp;
} GerenciadorDeMV;


MemoriaPrincipal* criaMP() {
    MemoriaPrincipal *mp = (MemoriaPrincipal*) malloc(sizeof(MemoriaPrincipal));
    mp->frames = (int*) malloc(sizeof(int) * TAM_MP);
    for(int i = 0; i < TAM_MP; i++){
        mp->frames[i] = -1;
    }
    return mp;
}

GerenciadorDeMV* criaGMV() {
    GerenciadorDeMV *gmv = (GerenciadorDeMV*) malloc(sizeof(GerenciadorDeMV));
    gmv->mp = criaMP();
    return gmv;
}

int memoriaCheia(MemoriaPrincipal *mp) {
    // TODO
    return 0;
}

void imprimeMemoriaPrincipal(MemoriaPrincipal *mp) {
    printf("|Frame\t| Página\t|\n");

    for(int i = 0; i < TAM_MP; i++) {
        if( mp->frames[i] != -1 )
            printf("|%d\t| %d\t|\n", i, mp->frames[i]);
        else
            printf("|%d\t| -\t|\n", i);
    }

}

int colocaPagNaMP(GerenciadorDeMV *gmv, int pagina) {
    for(int i = 0; i < TAM_MP; i++){
        if(gmv->mp->frames[i] == -1) {
            gmv->mp->frames[i] = pagina;
            return i;
        }
    }
}

void tiraPagDaMP(GerenciadorDeMV *gmv, Processo *proc, int pagina) {
    if( !getPresenca(proc->tabelaDePaginas, pagina) ) { 
        printf("[Erro] Tentou remover página que não estava na MP");
        exit(-1);
    }

    int frame = getFrame(proc->tabelaDePaginas, pagina);
    setPresenca(proc->tabelaDePaginas, pagina, 0);
    gmv->mp->frames[frame] = -1;
}

int acessaPagina(GerenciadorDeMV *gmv, Processo *proc, int pagina) {

    if( !getPresenca(proc->tabelaDePaginas, pagina) ) {
        
        setPresenca(proc->tabelaDePaginas, pagina, 1);
        int frame = colocaPagNaMP(gmv, pagina);
        setFrame(proc->tabelaDePaginas, pagina, frame);
        return frame;
    } else {
        return getFrame(proc->tabelaDePaginas, pagina);
    }

}