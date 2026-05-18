package com.encapsulamento.Banco;

import java.util.ArrayList;

public class Banco {

    private ArrayList<Cliente> clientes = new ArrayList<>();

    public Banco(){}

    public void adicionarCliente(Cliente cliente){
        clientes.add(cliente);
        System.out.println("Cliente adicionado com sucesso!");
    }

    public int numeroDeClientes(){
        return clientes.size();
    }

    public Cliente getCliente(int indice){
        return clientes.get(indice);
    }

}
