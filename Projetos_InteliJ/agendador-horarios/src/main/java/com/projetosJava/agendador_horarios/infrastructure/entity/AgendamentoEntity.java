package com.projetosJava.agendador_horarios.infrastructure.entity;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import org.hibernate.annotations.AnyDiscriminatorImplicitValues;

import java.time.LocalDateTime;

@Getter //Adiciona os gets dos objetos
@Setter //Adiciona os sets dos objetos

@NoArgsConstructor //Gera um construtor vazio para os objetos
@AllArgsConstructor //Gera um construtor com todas as variáveis para o objeto

@Entity //Marca a classe como uma entidade do banco de dados. Diz que a classe vai virar uma tabela e cada objeto é uma linha
@Table(name = "agendamento") //Permite modificar o nome da tabela criada

public class AgendamentoEntity {

    @Id //O Id identifica e classifica cada linha da tabela
    @GeneratedValue(strategy = GenerationType.IDENTITY) //Geração automática do Id
    private Long id;

    private String servico;

    private String profissional;

    private LocalDateTime dataHoraAgendamento;
    private LocalDateTime dataInsercao = LocalDateTime.now();

    private String cliente;
    private String telefoneCliente;


}
