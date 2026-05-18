package com.encapsulamento.Banco;

public class TesteBanco2 {

    public static void main(String[] args){

       Banco banco = new Banco();

       Conta conta1 = new Conta(100000);
       Cliente cliente1 = new Cliente("Leon ","S Kennedy",conta1);

       Conta conta2 = new Conta(6500);
       Cliente cliente2 = new Cliente("Verso ","Dessendre",conta2);

       Conta conta3 = new Conta(1000);
       Cliente cliente3 = new Cliente("Ellie ","Willians",conta3);

       Conta conta4 = new Conta(7500);
       Cliente cliente4 = new Cliente("Willian ","Afton",conta4);

       Conta conta5 = new Conta(1500);
       Cliente cliente5 = new Cliente("Thor ","Odinson",conta5);

        Conta conta6 = new Conta(3500);
        Cliente cliente6 = new Cliente("Arthur ","Morgan",conta6);

        banco.adicionarCliente(cliente1);
        banco.adicionarCliente(cliente2);
        banco.adicionarCliente(cliente3);
        banco.adicionarCliente(cliente4);
        banco.adicionarCliente(cliente5);
        banco.adicionarCliente(cliente6);
        

        System.out.println("\nCliente[1]: " + banco.getCliente(0).getNome() + banco.getCliente(0).getSobrenome() + ". Saldo: R$" + conta1.getSaldo());
        System.out.println("Cliente[2]: " + banco.getCliente(1).getNome() + banco.getCliente(1).getSobrenome() + ". Saldo: R$" + conta2.getSaldo());
        System.out.println("Cliente[3]: " + banco.getCliente(2).getNome() + banco.getCliente(2).getSobrenome() + ". Saldo: R$" + conta3.getSaldo());
        System.out.println("Cliente[4]: " + banco.getCliente(3).getNome() + banco.getCliente(3).getSobrenome() + ". Saldo: R$" + conta4.getSaldo());
        System.out.println("Cliente[5]: " + banco.getCliente(4).getNome() + banco.getCliente(4).getSobrenome() + ". Saldo: R$" + conta5.getSaldo());
        System.out.println("Cliente[6]: " + banco.getCliente(5).getNome() + banco.getCliente(5).getSobrenome() + ". Saldo: R$" + conta6.getSaldo());

    }

}
