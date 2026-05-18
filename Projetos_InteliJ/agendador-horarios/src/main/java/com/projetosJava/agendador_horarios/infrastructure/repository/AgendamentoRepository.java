package com.projetosJava.agendador_horarios.infrastructure.repository;

import com.projetosJava.agendador_horarios.infrastructure.entity.AgendamentoEntity;
import jakarta.transaction.Transactional;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.Repository;

import java.time.LocalDateTime;

public interface AgendamentoRepository extends JpaRepository <AgendamentoEntity,Long> {

    AgendamentoEntity findByServicoAndDataHoraAgendamentoBetween(String servico, LocalDateTime dataHoraInicio, LocalDateTime dataHoraFinal);

    @Transactional //“Tudo que acontecer aqui dentro tem que dar certo. Se der erro, desfaz tudo.
    void deleteByDataHoraAgendamentoAndCliente(LocalDateTime dataHoraAgendamento, String cliente);

}
