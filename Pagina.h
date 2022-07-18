void *err_malloc(unsigned int size) {
    void *res = malloc(size);
    if(!res) {
        printf("[Erro] malloc não funcionou\n");
        exit(-1);
    }
    return res;
}

typedef struct Processo Processo;

typedef struct Pagina{
    Processo* proc;
    int index;
} Pagina;

int getIndex(Pagina *pagina){
    return pagina->index;
}

void setIndex(Pagina *pagina, int index){
    pagina->index = index;
}

Processo * getProcesso(Pagina *pagina){
    return pagina->proc;
}

void setProcesso(Pagina * pagina, Processo * processo){
    pagina->proc = processo;
}

Pagina * criarPagina(Processo *p){
    Pagina * pagina = (Pagina *) err_malloc(sizeof(Pagina));
    pagina->proc = p;
    pagina->index = 0;
    return pagina;
}
