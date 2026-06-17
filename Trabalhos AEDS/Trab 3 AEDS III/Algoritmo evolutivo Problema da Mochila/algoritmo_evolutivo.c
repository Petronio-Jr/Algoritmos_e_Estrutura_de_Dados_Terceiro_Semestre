#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

#define num_combinacoes_mochila 51
#define quantidade_itens 10
#define limite_peso_mochila 20

#define taxa_mutacao 0.1 //  (1 / quantidade_itens)
#define taxa_cruzamento 0.8
#define maximo_geracoes 300

typedef struct{
    int peso;
    int valor;
}Item;

//======================================== Geração da população inicial ==========================================================

int valor_aleatorio(){
    return rand() % 2;
}

bool combinacoes_sao_diferentes(int** lista_combinacoes, int* nova_combinacao){

    for(int combinacao = 0; combinacao < num_combinacoes_mochila; combinacao++){
        
        if(lista_combinacoes[combinacao] == NULL) return true;

        for(int item = 0; item < quantidade_itens; item++){
            
            if(lista_combinacoes[combinacao][item] != nova_combinacao[item]){
                break;
            }
            else{
                if(item == quantidade_itens - 1)   return false;
            }
        }
    }
    return true;
}

int** gera_mochila_inicial(){

    int** lista_combinacoes_mochila = (int**)malloc(sizeof(int*) * num_combinacoes_mochila);

    for(int i = 0; i < num_combinacoes_mochila; i++){
        lista_combinacoes_mochila[i] = NULL;
    }

    for(int combinacao = 0; combinacao < num_combinacoes_mochila; ){
        
        int* nova_combinacao_mochila = (int*)malloc(sizeof(int) * quantidade_itens);
        
        for(int item = 0; item < quantidade_itens; item++){
            nova_combinacao_mochila[item] = valor_aleatorio();
        }

        if(combinacoes_sao_diferentes(lista_combinacoes_mochila, nova_combinacao_mochila)){
            lista_combinacoes_mochila[combinacao] = nova_combinacao_mochila;
            combinacao++;
        }
        else{
            free(nova_combinacao_mochila);
        }
    }

    return lista_combinacoes_mochila;
}

//===============================================================================================================================

Item cria_item(int peso, int valor){

    Item novo_item;
    novo_item.peso = peso;
    novo_item.valor = valor;

    return novo_item;
}

int calcula_peso_item_mais_leve(Item* lista_valores_itens){

    int peso_item_mais_leve = INT_MAX;

    for(int item = 0; item < quantidade_itens; item++){

        if(lista_valores_itens[item].peso < peso_item_mais_leve){
            peso_item_mais_leve = lista_valores_itens[item].peso;
        }
    }

    return peso_item_mais_leve;
}

int calcula_valor_max_itens(Item* lista_valores_itens){

    int valor_maximo_possivel = 0;

    for(int item = 0; item < quantidade_itens; item++){
        valor_maximo_possivel += lista_valores_itens[item].valor;
    }

    return valor_maximo_possivel;
}

int penalidade(int peso_total_combinacao, Item* lista_valores_itens){

    int valor_maximo_possivel = calcula_valor_max_itens(lista_valores_itens);
    int peso_item_mais_leve = calcula_peso_item_mais_leve(lista_valores_itens);

    int excesso_de_peso = peso_total_combinacao - limite_peso_mochila;

    return (excesso_de_peso * (valor_maximo_possivel/peso_item_mais_leve));
}

void aptidao_combinacoes_mochila(Item* lista_valores_itens, int** lista_combinacoes_mochila, int* pontuacao_combinacoes){

    int peso_total_combinacao = 0; // RESETAR AO FIM
    int valor_total_combinacao = 0;

    for(int combinacao = 0; combinacao < num_combinacoes_mochila; combinacao++){

        for(int item = 0; item < quantidade_itens; item++){
            if(lista_combinacoes_mochila[combinacao][item] == 1){
                peso_total_combinacao += lista_valores_itens[item].peso;
                valor_total_combinacao += lista_valores_itens[item].valor;
            }
        }

        if(peso_total_combinacao <= limite_peso_mochila){
            pontuacao_combinacoes[combinacao] = valor_total_combinacao;
        }
        else{
            pontuacao_combinacoes[combinacao] = valor_total_combinacao - penalidade(peso_total_combinacao, lista_valores_itens);
        }

        peso_total_combinacao = 0;
        valor_total_combinacao = 0;
    }
}

bool teste_taxa_cruzamento(){

    double taxa_gerada = (double)rand() / RAND_MAX;

    if(taxa_gerada < taxa_cruzamento) 
        return true;
    else
        return false; 
}

bool teste_taxa_mutacao(){

    double taxa_gerada = (double)rand() / RAND_MAX;

    if(taxa_gerada < taxa_mutacao) 
        return true;
    else
        return false; 
}

void mutacao_combinacoes_filhas(int* filho_1, int* filho_2){

    for(int i = 0; i < quantidade_itens; i++){
        if(teste_taxa_mutacao()){
            filho_1[i] = filho_1[i] == 0 ? 1 : 0; 
        }
    }

    for(int i = 0; i < quantidade_itens; i++){
        if(teste_taxa_mutacao()){
            filho_2[i] = filho_2[i] == 0 ? 1 : 0; 
        }
    }
}

// Método de Cruzamento de Ponto Único
void geracao_combinacoes_filhas(int pai_1, int pai_2, int** lista_combinacoes_mochila, int* filho_1, int* filho_2){

    if(!teste_taxa_cruzamento()){

        for(int item = 0; item < quantidade_itens; item++){
            filho_1[item] = lista_combinacoes_mochila[pai_1][item];
            filho_2[item] = lista_combinacoes_mochila[pai_2][item]; 
        }
    }
    else{

        int ponto_de_corte = (rand() % 8) + 1; // vai de 1 até 8
        
        for(int i = 0; i < quantidade_itens; i++){

            if(i < ponto_de_corte){
                filho_1[i] = lista_combinacoes_mochila[pai_1][i]; 
                filho_2[i] = lista_combinacoes_mochila[pai_2][i]; 
            }
            else{
                filho_1[i] = lista_combinacoes_mochila[pai_2][i]; 
                filho_2[i] = lista_combinacoes_mochila[pai_1][i]; 
            }
        }
    }

    mutacao_combinacoes_filhas(filho_1, filho_2);
}

void selecao_de_combinacoes_pais(int** lista_combinacoes_mochila, int* pontuacao_combinacoes, int** lista_combinacoes_mochila_final, int indice_filho){

    int num_pais = 0, pai_1 = -1, pai_2 = -1;

    while(num_pais < 2){

        int possivel_pai_1 = rand() % num_combinacoes_mochila;
        int possivel_pai_2 = rand() % num_combinacoes_mochila;

        while(possivel_pai_2 == possivel_pai_1){
            possivel_pai_2 = rand() % num_combinacoes_mochila;
        }

        int possivel_pai_3 = rand() % num_combinacoes_mochila;

        while (possivel_pai_3 == possivel_pai_1 || possivel_pai_3 == possivel_pai_2){
            possivel_pai_3 = rand() % num_combinacoes_mochila;
        }

        int pai_de_maior_valor = pontuacao_combinacoes[possivel_pai_1] > pontuacao_combinacoes[possivel_pai_2] ? possivel_pai_1 : possivel_pai_2;
        pai_de_maior_valor = pontuacao_combinacoes[possivel_pai_3] > pontuacao_combinacoes[pai_de_maior_valor] ? possivel_pai_3 : pai_de_maior_valor;

        pai_1 = num_pais == 0 ? pai_de_maior_valor : pai_1;
        pai_2 = num_pais == 1 ? pai_de_maior_valor : pai_2;

        num_pais++;
    }

    if(pai_1 == -1 || pai_2 == -1)
        printf("Houve um erro na busca por pais - linha 156-176");

    lista_combinacoes_mochila_final[indice_filho] = (int*)malloc(sizeof(int) * quantidade_itens);
    lista_combinacoes_mochila_final[indice_filho + 1] = (int*)malloc(sizeof(int) * quantidade_itens);

    geracao_combinacoes_filhas(pai_1, pai_2, lista_combinacoes_mochila,lista_combinacoes_mochila_final[indice_filho],lista_combinacoes_mochila_final[indice_filho + 1]);
}

void elitismo(int* pontuacao_combinacoes,int** lista_combinacoes_mochila_inicial, int** lista_combinacoes_mochila_final){

    int indice_melhor_valor = 0;

    for(int combinacao = 0; combinacao < num_combinacoes_mochila; combinacao++){
        if(pontuacao_combinacoes[combinacao] > pontuacao_combinacoes[indice_melhor_valor]){
            indice_melhor_valor = combinacao;
        }
    }

    lista_combinacoes_mochila_final[0] = (int**)malloc(sizeof(int*) * quantidade_itens);

    for(int item = 0; item < quantidade_itens; item++){
        lista_combinacoes_mochila_final[0][item] = lista_combinacoes_mochila_inicial[indice_melhor_valor][item];
    }
}

int** algoritmo_evolutivo_problema_da_mochila(Item* lista_valores_itens){

    int** lista_combinacoes_mochila_inicial = gera_mochila_inicial();
    int** lista_combinacoes_mochila_final = NULL;

    int pontuacao_combinacoes[num_combinacoes_mochila];

    for(int geracao = 0; geracao < maximo_geracoes; geracao++){
     
        aptidao_combinacoes_mochila(lista_valores_itens, lista_combinacoes_mochila_inicial, pontuacao_combinacoes);

        lista_combinacoes_mochila_final = (int**)malloc(sizeof(int*) * num_combinacoes_mochila);
    
        elitismo(pontuacao_combinacoes, lista_combinacoes_mochila_inicial, lista_combinacoes_mochila_final);

        int indice_lista_final = 1;

        while(indice_lista_final < num_combinacoes_mochila - 1){
            selecao_de_combinacoes_pais(lista_combinacoes_mochila_inicial, pontuacao_combinacoes,lista_combinacoes_mochila_final, indice_lista_final);
            indice_lista_final += 2;
        }

        // Pra não quebrar o acesso à memória eu aloco o último por conta própria
        lista_combinacoes_mochila_final[indice_lista_final] = (int*)malloc(sizeof(int) * quantidade_itens);
        
        // e passo pra ele o mesmo do elitismo pois isso garante boas combinações
        for(int item = 0; item < quantidade_itens; item++){
            lista_combinacoes_mochila_final[indice_lista_final][item] = lista_combinacoes_mochila_final[0][item];
        }

        for(int i = 0; i < num_combinacoes_mochila; i++){
            free(lista_combinacoes_mochila_inicial[i]);
        }
        free(lista_combinacoes_mochila_inicial);

        lista_combinacoes_mochila_inicial = lista_combinacoes_mochila_final;
    }   

    return lista_combinacoes_mochila_inicial;
}

int main(){

    clock_t tempo_inicial = clock();
    srand(time(NULL));

    //================================= Criando vetor de itens ======================
    Item it1 = cria_item(3,7);
    Item it2 = cria_item(1,5);
    Item it3 = cria_item(9,2);
    Item it4 = cria_item(6,10);
    Item it5 = cria_item(4,8);
    Item it6 = cria_item(2,5);
    Item it7 = cria_item(8,6);
    Item it8 = cria_item(9,10);
    Item it9 = cria_item(7,4);
    Item it10 = cria_item(5,8);

    Item lista_valores_itens[quantidade_itens];

    lista_valores_itens[0] = it1;
    lista_valores_itens[1] = it2;
    lista_valores_itens[2] = it3;
    lista_valores_itens[3] = it4;
    lista_valores_itens[4] = it5;
    lista_valores_itens[5] = it6;
    lista_valores_itens[6] = it7;
    lista_valores_itens[7] = it8;
    lista_valores_itens[8] = it9;
    lista_valores_itens[9] = it10;

    //================================== Execução do algoritmo =========================

    int** melhores_combinacoes_problema_da_mochila = algoritmo_evolutivo_problema_da_mochila(lista_valores_itens);

    int pontuacoes_finais[num_combinacoes_mochila];

    aptidao_combinacoes_mochila(lista_valores_itens, melhores_combinacoes_problema_da_mochila, pontuacoes_finais);

    int melhor_pontuacao = 0, indice_alvo;

    for(int i = 0; i < num_combinacoes_mochila; i++){
        if(pontuacoes_finais[i] > melhor_pontuacao){
            melhor_pontuacao = pontuacoes_finais[i];
            indice_alvo = i;
        }
    }

    //===================================================================================

    printf("\n=================== RESULTADO ===================\n");

    printf("A melhor combinacao encontrada foi [ " );
    for(int i = 0; i < quantidade_itens; i++){
        printf("%d ", melhores_combinacoes_problema_da_mochila[indice_alvo][i]);
    }
    printf("]\n");

    // Limpeza da memória final
    for(int i = 0; i < num_combinacoes_mochila; i++){
        free(melhores_combinacoes_problema_da_mochila[i]);
    }
    free(melhores_combinacoes_problema_da_mochila);

    clock_t tempo_final = clock();
    double tempo_gasto = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;

    printf("\n================ METRICAS DE DESEMPENHO ================\n");
    printf("Tempo total de execucao: %.4f segundos\n", tempo_gasto);
    printf("\n========================================================\n");
}