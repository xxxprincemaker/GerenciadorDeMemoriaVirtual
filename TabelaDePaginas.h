//
// Created by VipSo on 7/5/2022.
//
#define MAXPAGINAS 50

typedef struct TabelaDePaginas{
    int *presenca;
    int *frames;
} TabelaDePaginas;

TabelaDePaginas * criarTabelaDePaginas()
{
    TabelaDePaginas * tabelaDePaginas = malloc(sizeof(TabelaDePaginas));
    tabelaDePaginas->presenca = (int*)malloc(sizeof(int) * MAXPAGINAS);
    for(int i = 0; i < MAXPAGINAS; i++){
        *tabelaDePaginas->presenca = 0;
    }
    tabelaDePaginas->frames = (int*)malloc(sizeof(int) * MAXPAGINAS);

    return tabelaDePaginas;
}