typedef struct Pagina Pagina;
typedef struct Node Node;

typedef struct Node {
    Pagina *pag;
    Node *ant, *prox;
} Node;

typedef struct LRUQueue {
    Node *frente, *tras;
} LRUQueue;

LRUQueue* criaLRUQueue() {
    LRUQueue* queue = (LRUQueue*) err_malloc(sizeof(LRUQueue));
  
    queue->frente = queue->tras = NULL;
  
    return queue;
}

int isEmpty(LRUQueue *queue) {
    return queue->frente == NULL && queue->tras == NULL;
}

void enqueue(LRUQueue *queue, Pagina *pag) {
    Node *newNode;

    if(isEmpty(queue)) {
        newNode = (Node*) err_malloc(sizeof(Node));
        newNode->pag = pag;
        newNode->ant = NULL;
        newNode->prox = NULL;
        queue->frente = newNode;
        queue->tras = newNode;
        return;
    }
    
    if(queue->tras->pag == pag) return;

    newNode = queue->frente;

    while (newNode){
        if(newNode->pag == pag) break;
        newNode = newNode->ant;
    }

    if(newNode) {
        Node *prox = newNode->prox;
        Node *ant = newNode->ant;

        if(prox) prox->ant = ant;
        else queue->frente = ant;
        
        ant->prox = prox;
    } else {
        newNode = (Node*) err_malloc(sizeof(Node));
        newNode->pag = pag;
    }
    newNode->ant = NULL;

    Node *tras = queue->tras;
    queue->tras = newNode;
    newNode->prox = tras;
    tras->ant = newNode;
}

Pagina* dequeue(LRUQueue *queue) {
    Node *frente = queue->frente;
    Pagina *pag = frente->pag;
    
    if(isEmpty(queue)) return NULL;

    queue->frente = frente->ant;

    if(queue->frente) 
        queue->frente->prox = NULL;
    else
        queue->tras = NULL;

    free(frente);

    return pag;
}

void removeQueue(LRUQueue *queue, Pagina *pagina) {
    if(isEmpty(queue)) return;

    Node *newNode = queue->frente;

    while (newNode){
        if(newNode->pag == pagina) break;
        newNode = newNode->ant;
    }

    if(!newNode) return;

    Node *prox = newNode->prox;
    Node *ant = newNode->ant;

    if(prox) prox->ant = ant;
    else queue->frente = ant;
    
    if(ant) ant->prox = prox;
    else queue->tras = prox;

    free(newNode);
}