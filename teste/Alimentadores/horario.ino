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
/*
void agendarDespejo(diretriz_t d)
{
  AlarmId id = Alarm.alarmRepeat(d.inicio_hora,d.inicio_minuto,0, alimentaPeixes);
  qtdRacao[id] = d.qtd;
  Serial.println("Despejo agendado!");
}
*/
//iii
/*
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
*/


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
