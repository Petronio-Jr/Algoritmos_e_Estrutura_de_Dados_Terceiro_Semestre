package com.encapsulamento.Banco;

public class Cliente {

    private String nome;
    private String sobrenome;
    private Conta conta;

    public Cliente(String nome, String sobrenome, Conta conta){
        this.nome = nome;
        this.sobrenome = sobrenome;
        this.conta = conta;
    }

    public String getNome(){
        return nome;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public String getSobrenome(){
        return sobrenome;
    }

    public void setSobrenome(String sobrenome){
        this.sobrenome = sobrenome;
    }

    public Conta getConta() {
        return conta;
    }

    public void setConta(Conta conta) {
        this.conta = conta;
    }

}
