#ifndef _CAMINHOS_MINIMOS_
#define _H_CAMINHOS_MINIMOS_

typedef struct vertice_{
    int indice;
    struct vertice_* prox;
} Vertice;

typedef struct bloco_{
    int quantV;
    Vertice* head;
    double limite;
    struct bloco_* prox;
} Bloco;

typedef struct {
    Bloco* refHead;
    int capacidade;
} ListaBlocos;

double dijkstra(double **matriz, int num_nos, int origem);

ListaBlocos* criaListaBlocos(int capacidade);
void insereLotes(ListaBlocos* lista, int* arrayVertices, int quantV, double* distanciasV);
void libera_listaBlocos(ListaBlocos* lista);
void bellman_ford_limitado(int num_v, double** matriz, int* origens, int cont_origem, int num_etapas, double limite, double* distancias, int* pivos, int* cont_pivos);
void bmssp_recursivo(int num_v, double** matriz, int* origens, int cont_origens, double limite, int num_etapas, double* distancias);
double* duan_caminhos_minimos(double **matriz, int num_nos, int origem);
double duan(double **matriz, int num_nos, int origem);

#endif