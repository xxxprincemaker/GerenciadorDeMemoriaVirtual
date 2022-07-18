//
// Created by VipSo on 7/5/2022.
//

#define MAXPAGINAS 50

typedef struct TabelaDePaginas{
    int *presenca;
    int *frames;
} TabelaDePaginas;

TabelaDePaginas* criarTabelaDePaginas()
{
    TabelaDePaginas* tabelaDePaginas = (TabelaDePaginas*) err_malloc(sizeof(TabelaDePaginas));
    tabelaDePaginas->presenca = (int*) err_malloc(sizeof(int) * MAXPAGINAS);
    for(int i = 0; i < MAXPAGINAS; i++){
        tabelaDePaginas->presenca[i] = 0;
    }
    tabelaDePaginas->frames = (int*) err_malloc(sizeof(int) * MAXPAGINAS);

    return tabelaDePaginas;
}

int  getPresenca(TabelaDePaginas *tabela, int pagina) { return tabela->presenca[pagina]; }
void setPresenca(TabelaDePaginas *tabela, int pagina, int pres) { tabela->presenca[pagina] = pres; }

int  getFrame(TabelaDePaginas *tabela, int pagina) { return tabela->frames[pagina]; }
void setFrame(TabelaDePaginas *tabela, int pagina, int frame) { tabela->frames[pagina] = frame; }

/*
    Mostra tabela de paginas, passado uma tabela.
*/
void mostraTabela(TabelaDePaginas *tabela){
    printf("|Página\t| Frame\t|\n");

    for(int i = 0; i < MAXPAGINAS; i++) {
        if( getPresenca(tabela, i) )
            printf("|%d\t| %d\t|\n", i, getFrame(tabela, i));
        //else
        //    printf("|%d\t| 0\t| -\t|\n", i);
    }
}