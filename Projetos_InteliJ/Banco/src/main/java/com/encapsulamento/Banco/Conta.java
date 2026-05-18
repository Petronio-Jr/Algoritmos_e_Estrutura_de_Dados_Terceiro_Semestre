package com.encapsulamento.Banco;

public class Conta {

    private double saldo;
    private double saldoInicial; //saudoInicial foi criado para calcular o rendimento da conta

    public Conta(double saldoinicial){
        this.saldo = saldoinicial;
        this.saldoInicial = saldoinicial;
    }

    public double getSaldo() {
        return saldo;
    }

    public void depositar(double valor){
        this.saldo += valor;
    }

    public void sacar(double amount){
        if(amount < saldo)
            this.saldo -= amount;
        else
            System.out.println("Dinheiro insuficiente na conta!");
    }

    //esse eu adicionei, não ta na lista
    public double rendimento(){
        return -(saldoInicial - getSaldo());
    }

}
