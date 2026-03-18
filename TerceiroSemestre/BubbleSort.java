package TerceiroSemestre;

public class BubbleSort {

    public static void bubbleSort(int vetor[], int tam){
        boolean trocou = true;
        while(trocou){
            trocou = false;
            for(int i = 0; i < tam - 1; i++){
                if(vetor[i] > vetor[i+1]){
                    int temp = vetor[i];
                    vetor[i] = vetor[i+1];
                    vetor[i+1] = temp;

                    trocou = true;
                }
            }
            tam--;
        }
    }

    public static void main(String[] args){

        int vetor1[] = {2,9,3,8,4,7,5,6,1,0};

        System.out.print("\nVetor desordenado = [");

        for(int i = 0; i < 10; i++){
            System.out.print(" " + vetor1[i]);
        }
        System.out.print(" ]");

        bubbleSort(vetor1,10);
        
        System.out.print("\nVetor ordenado = [");

        for(int i = 0; i < 10; i++){
            System.out.print(" " + vetor1[i]);
        }
        System.out.print(" ]\n\n");
    }
}
