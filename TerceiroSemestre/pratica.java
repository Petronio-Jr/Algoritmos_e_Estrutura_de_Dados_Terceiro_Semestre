package TerceiroSemestre;

import java.util.Scanner;

public class pratica {

    public static void main (String[] args){ // isso é a função main do java

        System.out.println("Hello, cruel word!"); // comando de println exibe texto no terminal separado por LINHAS 

        System.out.println(
            "Integer: " + 10 +
            " Double: " + 3.14 +
            " Boolean: " + true);
    
        System.out.print("Hello "); // comando print exibe a mensagem sem quebrar linha
        System.out.print("World!\n");

        System.out.printf("pi = %.5f",Math.PI); // comando printf exibe a mensagem de forma mais formatada
        System.out.printf("\n\n");

        Scanner sc = new Scanner(System.in); //criando um OBJETO para ser lido (input)

        System.out.print("Digite o numero da sua camisa: ");
        int numero = sc.nextInt(); //input de int
        System.out.print("Digite seu nome: ");
        String nome = sc.next(); //int de string 

        sc.close(); //fechando o scanner

        // final variables não podem ser alteradas;
        final int expedicao = 33;
        // mas elas podem ser inicializadas depois.
        final double E;
        E = 2.71828;

        // var é uma tipagem coringa, é preciso definir o conteudo da variável ao declará-la mas o sistema identifica seu tipo
        var Ellie = "\nAté não sobrar nenhum!";
        var Pet = 1;
        var pi = 3.14;

        System.out.println(Ellie);

        // usar três aspas seguidas permite escrever um bloco de texto
        var bloco_de_texto = """
                \nEsse é um bloco de texto
                """;
            
        System.out.println(bloco_de_texto);
        
        // operando + colecta frase e outras variáveis 
        String frase = "frases podem " + "ser conectadas usando " + "o operando da adicao";
        System.out.println(frase); 

        System.out.print("\n");

        // String builder controi um texto atraves de fragmentos
        // append adiciona a frase ao final 
        StringBuilder StringPart = new StringBuilder();
        StringPart.append("Sem mente pra pensar ");
        StringPart.append("Sem vontade pra quebrar ");
        StringPart.append("Sem voz pra gritar de sofrimento ");
        StringPart.append("Nascido de Deus e do Vazio ");
        System.out.println(StringPart.toString()); // é nessa parte que o string é conectado com .toString

        System.out.print("\n");

        // As duas strings vao ser formadas pelo loop mas nesse caso compensa mais o string partilhada
        StringBuilder string_eficiente = new StringBuilder();
        String string_ineficiente = "";

        for(int i = 0; i < 10; i++){
            string_eficiente.append(i).append(" ");
            string_ineficiente += i + " ";
        }

        System.out.println("Forma mais otimizada: " + string_eficiente);
        System.out.println("Forma mais trabalhosa pro programa: " + string_ineficiente);

        System.out.print("\n");

        // Vetores

        int[] x = {1,2,3,4,5,6,7,8,9,0};
        int[] y = new int[10];
        boolean[] z = {true,false,false};

        System.out.println("Primeiro elemento do vetor = " + x[0]);

        // Condição

        int pokedex = 491;
        System.out.println("\nQuem é esse pokemon? " + (pokedex > 490 ? "Darkrai" : "Mesprit"));

        // Conversão de dados

        Integer.parseInt("487"); // string pra inteiro 
        Integer.toString(100); // inteiro pra string

        System.out.println("3 = 2?" + (3 == 2));
    }
}
