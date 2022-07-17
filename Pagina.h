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
    Pagina * pagina = (Pagina *) malloc(sizeof(Pagina));
    if(!pagina) {printf("Não malocou"); exit(1);}
    pagina->proc = p;
    pagina->index = 0;
    printf("Conseguiu Alocar a Pagina de Endereco: %x\n", pagina);
    return pagina;
}
