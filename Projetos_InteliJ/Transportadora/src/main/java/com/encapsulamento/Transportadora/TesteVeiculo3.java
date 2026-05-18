//implementando leitura de valores do teclado

package com.encapsulamento.Transportadora;

import java.util.Scanner;

public class TesteVeiculo3 {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Insira a carga máxima do veículo: ");
        double cargaMaxima = sc.nextDouble();

        Veiculo veiculo = new Veiculo(cargaMaxima);

        int opcao = -1;

        while(opcao != 0){

            System.out.println("\nMenu");
            System.out.println("1.Adicionar caixa ao veículo");
            System.out.println("2.Ver carga do veículo");
            System.out.println("0.Sair");
            opcao = sc.nextInt();

            switch (opcao){
                case 1:
                    System.out.print("Insira o peso da caixa: ");
                    double pesoCaixa = sc.nextDouble();
                    veiculo.adicionarCaixa(pesoCaixa);
                    break;
                case 2:
                    System.out.println("Carga atual: " + veiculo.getCarga());
                    break;
                default:
                    if(opcao == 0) break;
                    System.out.println("Comando inválido!");
            }
        }
    }
}
