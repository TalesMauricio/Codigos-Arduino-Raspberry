//Aqui vai tudo relacionado ao RTC e ao agendamento de tarefas

AlarmId idAgendamento;

void sincTempo(relogio_t relogio)
{
    setTime(            // set time to Saturday 8:29:00am Jan 1 2011
            relogio.hora,
            relogio.minu,
            relogio.segu,
          //relogio.dias,
            relogio.diam,
            relogio.mess,
            relogio.anoo);
  
    tempoSinc = true;
}

void agendarDespejo(int hora, int minuto) {
  Serial.println("Despejo agendado!");
  idAgendamento = Alarm.alarmRepeat(hora,minuto,0, DespejarRacao);
}

char ConverteParaBCD(char val){ //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

char ConverteparaDecimal(char val)  { //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}
void Relogio()
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  
  segundos = ConverteparaDecimal(Wire.read());
  minutos = ConverteparaDecimal(Wire.read());
  horas = ConverteparaDecimal(Wire.read() & 0b111111); 
  diadasemana = ConverteparaDecimal(Wire.read()); 
  diadomes = ConverteparaDecimal(Wire.read());
  mes = ConverteparaDecimal(Wire.read());
  ano = ConverteparaDecimal(Wire.read());
}

