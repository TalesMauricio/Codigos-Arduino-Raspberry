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
  AlarmId id = Alarm.alarmRepeat(d.inicio_hora,d.inicio_minuto,0, alimentaPeixes);
  
  if(id == 255)
    Serial.println(F("Agendamento não-registrado"));
  else {
    if(id == dtNBR_ALARMS-1)
      Serial.println(F("Limite de agendamentos estourado!"));
    qtdRacao[id] = d.qtd;
    Serial.print(F("Despejo agendado!   alarmID: "));
    Serial.println(id);
  }
  Serial.println("");
}

void printDiretriz(diretriz_t diretriz)
{
  Serial.print(F("  RX:"));
  Serial.print(F("  A-ID:"));
  Serial.print(diretriz.alimentID);
  Serial.print(F("  iniH:"));
  Serial.print(diretriz.inicio_hora);
  Serial.print(F("  iniM:"));
  Serial.print(diretriz.inicio_minuto);
  //Serial.print("  Freq:");
  //Serial.print(diretriz.frequencia);  
  Serial.print(F("  qtd:"));
  Serial.println(diretriz.qtd);
}

void printTempo(relogio_t relogio)
{
  Serial.print(F("  RX - Tempo: "));
  Serial.print(relogio.hora);
  Serial.print(F(":"));
  Serial.print(relogio.minuto);
  Serial.print(F(":"));
  Serial.print(relogio.segundo);
  Serial.print(F("      dia"));
  Serial.print(relogio.dia);
  Serial.print(F("/"));
  Serial.print(relogio.mes);
  Serial.print(F("/"));
  Serial.println(relogio.ano);
}
