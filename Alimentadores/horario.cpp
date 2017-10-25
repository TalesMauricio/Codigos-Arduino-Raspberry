//Aqui vai tudo relacionado ao RTC e ao agendamento de tarefas

// RTC
#define DS1307_ADDRESS 0x68
#include "Wire.h"


char zero = 0x00; 
char segundos = 0;        // Segundo atual do RTC
char minutos = 0;         // Minuto atual do RTC
char horas = 0;           // Hora atual do RTC
char diadasemana = 0;     // Dia da semana atual do RTC
char diadomes = 0;        // Dia do mes atual do RTC
char mes = 0;             // Mes atual do RTC
char ano = 0;             // Ano atual do RTC

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

