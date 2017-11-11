//Aqui vai tudo relacionado ao RTC e ao agendamento de tarefas

AlarmId idAgendamento;

void sincTempo(relogio_t relogio)
{
    setTime( relogio.hora,
             relogio.minuto,
             relogio.segundo,
             relogio.dia,
             relogio.mes,
             relogio.ano );
  
    tempoSinc = true;
}

void agendarDespejo(int hora, int minuto) {
  Serial.println("Despejo agendado!");
  idAgendamento = Alarm.alarmRepeat(hora,minuto,0, DespejarRacao);
}

void printTempo(relogio_t relogio)
{
  Serial.print("  RX - Tempo: ");
  Serial.print(relogio.hora);
  Serial.print(":");
  Serial.print(relogio.minuto);
  Serial.print(":");
  Serial.print(relogio.segundo);
  Serial.print("      dia");
  Serial.print(relogio.dia);
  Serial.print("/");
  Serial.print(relogio.mes);
  Serial.print("/");
  Serial.print(relogio.ano);
}
