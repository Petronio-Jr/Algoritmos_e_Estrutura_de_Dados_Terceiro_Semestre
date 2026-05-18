// Objeto Veiculo, as variáveis são guardadas em Newtons e transformadas para kg

package com.encapsulamento.Transportadora;

public class Veiculo {

    private double carga;
    private double cargaMaxima;

    Veiculo(double cargaMaxima){
        this.cargaMaxima = quilosParaNewtons(cargaMaxima);
        this.carga = quilosParaNewtons(carga);
        //this.cargaMaxima = cargaMaxima;
    }

    Veiculo(){}

    public double getCarga() {
        return newtonsParaQuilos(carga);
    }

    public double getCargaMaxima() {
        return newtonsParaQuilos(cargaMaxima);
    }

    public boolean adicionarCaixa(double peso) {

        peso = quilosParaNewtons(peso);
        double totalCarga = this.carga + peso;

        if(totalCarga > cargaMaxima) {
            System.out.println("O valor excede a carga máxima de " + newtonsParaQuilos(cargaMaxima));
            return false;
        }
        else{
            this.carga = totalCarga;
            return true;
        }
    }

    private double newtonsParaQuilos(double peso){
        return (peso * 9.8);
    }

    private double quilosParaNewtons(double peso){
        return (peso/9.8);
    }

}
