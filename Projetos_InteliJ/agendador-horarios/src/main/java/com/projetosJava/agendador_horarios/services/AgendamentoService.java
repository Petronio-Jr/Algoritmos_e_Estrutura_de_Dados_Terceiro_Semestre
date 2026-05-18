package com.projetosJava.agendador_horarios.services;

import com.projetosJava.agendador_horarios.infrastructure.entity.AgendamentoEntity;
import com.projetosJava.agendador_horarios.infrastructure.repository.AgendamentoRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.Objects;

@Service
@RequiredArgsConstructor

public class AgendamentoService {

    private final AgendamentoRepository agendamentoRepository;

    public AgendamentoEntity salvarAgendamento(AgendamentoEntity agendamento){

        LocalDateTime horaAgendamento = agendamento.getDataHoraAgendamento();
        LocalDateTime horaFim = agendamento.getDataHoraAgendamento().plusHours(1);

        AgendamentoEntity agendados = agendamentoRepository.findByServicoAndDataHoraAgendamentoBetween(agendamento.getServico(), horaAgendamento, horaFim);

        if(Objects.nonNull(agendados)) {//se não tiver agendamento
            throw new RuntimeException("Horario ja esta ocupado!");
        }
        return agendamentoRepository.save(agendamento);
    }

    public void deletarAgendamento(LocalDateTime dataHoraAgendamento, String cliente){

    }



}
