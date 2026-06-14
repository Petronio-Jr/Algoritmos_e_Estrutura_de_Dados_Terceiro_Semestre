#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "algoritmos.h"

#define inf_D DBL_MAX //valor máximo de double
#define K 15.0

// Algoritmo de Dijkstra usando matriz de adjacência
double dijkstra(double **matriz, int num_nos, int origem) {
    
    //guarda a menor distância entre os nós
    double* distancia_nos = (double*)malloc(sizeof(double) * num_nos);
    //guarda os nos ja explorados como 1 e os não como 0
    int* visitados = (int*)calloc(num_nos, sizeof(int));
    //guarda de qual no ele veio 
    int* predecessores = (int*)malloc(sizeof(int) * num_nos);

    //inicialização
    for(int i = 0; i < num_nos; i++){
        distancia_nos[i] = inf_D;
        predecessores[i] = -1;
    }
    distancia_nos[origem] = 0.0;

    //percorre até num_nos - 1, pois o ultimo no não irá a lugar algum, logo ele nao terá um caminho mais curto
    for(int n = 0; n < num_nos - 1; n++){

        double valorMin = inf_D;
        int noAtual = -1;
        
        for(int i = 0; i < num_nos; i++){
            //percorrendo a linha atual e vendo o menor valor não visitado 
            if(distancia_nos[i] <= valorMin && visitados[i] == 0){
                valorMin = distancia_nos[i];
                noAtual = i;
            }
        }

        //marcando o no como ja visitado 
        visitados[noAtual] = 1;

        // Linha - de onde você ta saindo
        // Coluna - pra onde você ta indo

        for(int i = 0; i < num_nos; i++){
            // se o peso é maior que 0 (significa que tem caminho) && não foi visitado && não é um no isolado  
            if(matriz[noAtual][i] != 0.0 && visitados[i] == 0 && distancia_nos[noAtual] != inf_D){
                // se a distancia do no atual (ex: origem = 0) + o peso do no até a cidade (ex: 5) < valor salvo anteriormente como distancia (INT_MAX)
                if(distancia_nos[noAtual] + matriz[noAtual][i] < distancia_nos[i]){
                    distancia_nos[i] = distancia_nos[noAtual] + matriz[noAtual][i];
                    predecessores[i] = noAtual;
                }
            }
        }
    }

    double custo = 0.0;

    for(int i = 0; i < num_nos; i++){
        if(distancia_nos[i] != inf_D){
            custo += distancia_nos[i];
            printf("%.2f, ", distancia_nos[i]);
        }else{
            printf("inf_D, ");
        }
    }
    
    return custo;

}


//============================================================================================================================================================================
//============================================================================================================================================================================

// Funções principais do algoritmo 

ListaBlocos* criaListaBlocos(int capacidade){
    ListaBlocos* lista = (ListaBlocos*)malloc(sizeof(ListaBlocos));
    lista->capacidade = capacidade;
    lista->refHead = NULL;
    return lista;
}

// analisa a distância dos vértices e decide em qual bloco ele entra, ou se é preciso criar um novo bloco
void insereLotes(ListaBlocos* lista, int* arrayVertices, int quantV, double* distanciasV){

    for(int i = 0; i < quantV; i++){
      
        //salva o índice e a distância do vértice à origem
        int v = arrayVertices[i];
        double dist = distanciasV[i];

        //se a distancia é inacessível, pula a iteração
        if(dist == inf_D) continue;

        //cria um bloco definindo ele como a cabeça da lista 
        Bloco* b_Atual = lista->refHead;
        Bloco* b_Anterior = NULL;

        //se existir algum bloco além da head e a head possuir um limite menor que a distância do vértice analisado
        //o bloco avança para o proximo para procurar onde o vértice se encaixe ou até encontrar NULL
        while(b_Atual != NULL && b_Atual->limite < dist){
            b_Anterior = b_Atual;
            b_Atual = b_Atual->prox;
        }

        //se o bloco atual é NULL (não existe bloco para o vértice visto) ou o bloco é ideal para o vértice mas está
        //lotado, um novo bloco é criado para armazená-lo
        if(b_Atual == NULL || b_Atual->quantV >= lista->capacidade){
            
            Bloco* novo_Bloco = (Bloco*)malloc(sizeof(Bloco));
            novo_Bloco->head = NULL;
            novo_Bloco->quantV = 0;
            novo_Bloco->limite = dist + K;
            novo_Bloco->prox = b_Atual;

            //se for o primeiro bloco criado ele é a head, senão só é adicionado na lista
            if(b_Anterior == NULL)
                lista->refHead = novo_Bloco;
            else
                b_Anterior->prox = novo_Bloco;
        
            //define o bloco atual como o novo bloco 
            b_Atual = novo_Bloco;
        }

        Vertice* v_inserido = (Vertice*)malloc(sizeof(Vertice));
        v_inserido->indice = v;
        
        //atualiza a head do bloco como o novo vertice
        v_inserido->prox = b_Atual->head;
        b_Atual->head = v_inserido;

        //acresce a quantidade de vertices do bloco
        b_Atual->quantV++;
    }
}

void libera_listaBlocos(ListaBlocos* lista){
    Bloco* b = lista->refHead;
    while(b != NULL){
        Vertice* v = b->head;
        while(v != NULL){
            Vertice* tmp_v = v;
            v = v->prox;
            free(tmp_v);
        }
        Bloco* tmp_b = b;
        b = b->prox;
        free(tmp_b);
    }
    free(lista);
}

/**
 * @param num_v numero de vertices do grafo
 * @param matriz matriz de adjacencia do grafo
 * @param origens arrays com os vertices de origem do grafo
 * @param cont_origem numero de vertices como origem
 * @param num_etapas limitacao de etapas do algoritmo
 * @param limite limite de peso que ele busca nas arestas
 * @param distancias array com as distancias minimas dos vertices até a origem
 * @param pivos array que guarda possiveis novas origens
 * @param cont_pivos ponteiro que referencia a quantidade de pivos
*/
void bellman_ford_limitado(int num_v, double** matriz, int* origens, int cont_origem, int num_etapas,
                            double limite, double* distancias, int* pivos, int* cont_pivos){

   //array pra armazenar o tamanho de cada arvore gerada pelas fontes
   int* tam_arvore = (int*)calloc(num_v, sizeof(int));
   //array boleano para marcar e conferir rapidamente os pontos de partida originais da chamada
   bool* eh_fonte =  (bool*)calloc(num_v, sizeof(bool));
   
   //marca os pontos de partida originais como true e coloca seu tamanho como 1
   for(int i = 0; i < cont_origem; i++){
        eh_fonte[origens[i]] = true;
        tam_arvore[origens[i]] = 1;
   }

   //cria um laço de repeticao com limite de etapas
   for(int etapa = 0; etapa < num_etapas; etapa++){
        bool mudou = false;
        for(int u = 0; u < num_v; u++){
            //se a distancia do vertice analisado até a origem for maior que o limite ele é ignorado e vai pra próxima iteração
            if(distancias[u] >= limite) continue;
            //se estiver dentro do limite ele checa seus vizinhos na matriz
            for(int v = 0; v < num_v; v++){
                double peso = matriz[u][v];
                //peso inf_D (não conectado no ponto), peso 0 (conectado nele mesmo). Ignorados
                if(peso < inf_D && peso > 0){
                    //se a distancia da origem a v passando por u é menor que a distancia da origem a v já conhecida (inicialmente inf_D)
                    //e se essa distancia não ultrapassa o limite determinado
                    if((distancias[u] + peso) < distancias[v] && (distancias[u] + peso) < limite){
                        //atualiza a distância da origem até v
                        distancias[v] = distancias[u] + peso;
                        //aumenta o numero de nos conectados no ponto de partida
                        if(eh_fonte[u])
                            tam_arvore[u]++;
                        mudou = true;
                    }
                }
            }
        }
        if(!mudou) break;
   }

   int p_index = 0;

   //analisa e salva as origens que formam caminhos maiores que o numero de etapas
   for(int i = 0; i < cont_origem; i++){
        if(tam_arvore[origens[i]] >= num_etapas){
            pivos[p_index++] = origens[i];
        }
   }
   *cont_pivos = p_index;

   free(tam_arvore); free(eh_fonte);
}

/**
 * @param num_v numero de vertices do grafo
 * @param matriz matriz de adjacencia do grafo
 * @param origens arrays com os vertices de origem do grafo
 * @param cont_origem numero de vertices como origem
 * @param num_etapas limitacao de etapas do algoritmo
 * @param limite limite de peso que ele busca nas arestas
 * @param distancias array com as distancias minimas dos vertices até a origem
*/
void bmssp_recursivo(int num_v, double** matriz, int* origens, int cont_origens, double limite, int num_etapas, double* distancias){

    if(cont_origens <= 2) return;

    ListaBlocos* lista = criaListaBlocos(num_etapas);
    insereLotes(lista, origens, cont_origens, distancias);

    int* pivos = (int*)malloc(sizeof(int) * num_v);
    int cont_pivos = 0;

    bellman_ford_limitado(num_v, matriz, origens, cont_origens, num_etapas, limite, distancias, pivos, &cont_pivos);

    if(cont_pivos > 0 && cont_pivos < cont_origens){
        bmssp_recursivo(num_v, matriz, pivos, cont_pivos, limite * 1.5, num_etapas, distancias);
    }

    free(pivos);
    libera_listaBlocos(lista);
}


// Algoritmo de Duan usando matriz de adjacência
double* duan_caminhos_minimos(double **matriz, int num_nos, int origem) {

    double* distancias = (double*)malloc(sizeof(double) * num_nos);
    
    //preenchendo a matriz com inf_D menos a origem
    for(int i = 0; i < num_nos; i++){
        distancias[i] = inf_D;
    }
    distancias[origem] = 0.0;

    //encontrando a aresta de maior peso no grafo
    double maiorPeso = 0.0;
    for(int i = 0; i < num_nos; i++){
        for(int j = 0; j < num_nos; j++){
            if(matriz[i][j] > maiorPeso && matriz[i][j] != inf_D){
                maiorPeso = matriz[i][j];
            }
        }
    }

    //defininfo o novo limite com base na maior aresta
    double limiteDinamico = maiorPeso * 5;
    if(limiteDinamico < 100) limiteDinamico = 100; // teto mínimo 

    int num_etapas = (int)pow(num_nos, 1.0 / 3.0); //pow é elevado. num_nos^1/3
    if(num_etapas < 2) num_etapas = 2; //limite mínimo de etapas
    
    int* origens_iniciais = (int*)malloc(sizeof(int) * num_nos);
    
    for(int i = 0; i < num_nos; i++)
        origens_iniciais[i] = i;

    //recursão com o novo limite dinâmico
    bmssp_recursivo(num_nos, matriz, origens_iniciais, num_nos, limiteDinamico, num_etapas, distancias);

    free(origens_iniciais);
    
    return distancias;
}

double duan(double **matriz, int num_nos, int origem){

    //chamando o algoritmo de Duan
    double* distancias = duan_caminhos_minimos(matriz, num_nos, origem);
    
    //definindo o custo 
    double custo = 0.0;

    for(int i = 0; i < num_nos; i++){
        if(distancias[i] != inf_D){
            printf("%.2f, ", distancias[i]);
            custo += distancias[i];
        }
        else{
            printf("inf_D, ");
        }
    }

    return custo;
}


/*
// Implementação do terceiro usando matriz de adjacência
double outro(int **matriz, int num_nos, int origem) {
    double custo = 0;

    // Esta retorno também é obrigatório e não deve ser retirado
    return custo;
}
*/