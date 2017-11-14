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

void agendarDespejo(int hora, int minuto, float massa)
{
  Serial.println("Despejo agendado!");
  AlarmId id = Alarm.alarmRepeat(hora,minuto,0, DespejarRacao);
  qtdRacao[id] = massa;
}

void printDiretriz(diretriz_t diretriz)
{
  Serial.print("  RX:");
  Serial.print("  A-ID:");
  Serial.print(diretriz.alimentID);
  Serial.print("  iniH:");
  Serial.print(diretriz.inicio_hora);
  Serial.print("  iniM:");
  Serial.print(diretriz.inicio_minuto);
  //Serial.print("  Freq:");
  //Serial.print(diretriz.frequencia);  
  Serial.print("  qtd:");
  Serial.println(diretriz.qtd);
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
