//Aqui vai tudo relacionado ao relógio e ao agendamento de tarefas


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

void agendarDespejo(diretriz_t d)
{
  //mandar função para apagar os alarmes aqui
  
  for(int cont=0; cont<6; cont++)
  {
    AlarmId id = Alarm.alarmRepeat(d.horad[cont],d.minutod[cont],0, alimentaPeixes);
    qtdRacao[id] = d.qtdd[cont];
  }

  
  Serial.println("Despejo agendado!");
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
  Serial.println(relogio.ano);
}
