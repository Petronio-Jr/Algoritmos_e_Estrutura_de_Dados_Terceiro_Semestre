package com.POO.aulaArrays;

import java.util.Arrays;

public class TesteArray {

    public static void exibeArray(int array[]){
        int tam = array.length;
        System.out.print("<");
        for(int i = 0; i < tam; i++){
            if(i == tam-1)
                System.out.print(array[i] + ">");
            else
                System.out.print(array[i] + ",");
        }
    }

    public static void mudaPares(int array[]){
        int tam = array.length;
        for(int i = 0; i < tam; i++){
            array[i] = array[i] % 2 == 0 ? i : array[i];
        }
    }

    public static void criaMatriz(int [][]matriz, int linhas){
        //atribuindo os espaços a cada linha
        for(int i = 0; i < linhas; i++){
            matriz[i] = new int[i];
            for(int j = 0; j < i; j++){
                matriz[i][j] = i * j;
            }
        }
    }

    public static void exibeMatriz(int [][]matriz, int linhas){
        for(int i = 0; i < linhas; i++){
            System.out.print("<");
            for(int j = 0; j < i; j++){
                if(j == i-1)
                    System.out.print(matriz[i][j]);
                else
                    System.out.print(matriz[i][j] + ",");
            }
            System.out.println(">");
        }
    }


    public static void main(String[] args) {

        int array1[] = {2,3,5,7,11,13,17,19};
        int array2[] = array1;
        int [][]matriz1 = new int [5][];

        mudaPares(array2);
        System.out.println("\nArray 1");
        exibeArray(array1);

        System.out.println("\n\nMatriz como no enunciado:");
        criaMatriz(matriz1,5);
        exibeMatriz(matriz1,5);

        //java.util.Arrays

        System.out.println("\nExibindo array1, array2 e matriz1 com funções do java:");
        System.out.println(Arrays.toString(array1));
        System.out.println(Arrays.toString(array2));
        System.out.println(Arrays.deepToString(matriz1));

    }
}
