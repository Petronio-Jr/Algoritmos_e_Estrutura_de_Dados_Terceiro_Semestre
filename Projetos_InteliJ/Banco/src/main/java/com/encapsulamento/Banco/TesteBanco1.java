package com.encapsulamento.Banco;

import java.util.Scanner;

public class TesteBanco1 {

    public static void main (String[] args){

        System.out.print("\t\tSeja bem vindo!\n\nInforme o saldo inicial da conta: ");

        Scanner sc = new Scanner(System.in);
        double saldoInicial = sc.nextDouble();

        Conta conta = new Conta(saldoInicial);
        System.out.println("Conta criada com sucesso!");;

        int opcao = -1;
        while(opcao != 0){

            System.out.println("\nMenu");
            System.out.println("1.Sacar dinheiro");
            System.out.println("2.Depositar dinheiro");
            System.out.println("3.Conferir saldo atual");
            System.out.println("4.Conferir rendimento da conta");
            System.out.println("0.Sair");
            opcao = sc.nextInt();

            switch (opcao){
                case 1:
                    System.out.print("Quanto deseja sacar da conta: R$");
                    double saque = sc.nextDouble();
                    conta.sacar(saque);
                    break;
                case 2:
                    System.out.print("Quanto deseja depositar da conta: R$");
                    double deposito = sc.nextDouble();
                    conta.depositar(deposito);
                    break;
                case 3:
                    System.out.println("Saldo atual: R$ " + conta.getSaldo());
                    break;
                case 4:
                    System.out.println("Rendimento da conta: R$ " + conta.rendimento());
                    break;
                default:
                    if(opcao == 0) break;
                    System.out.println("Opção inválida!");
            }
        }

    }
}
