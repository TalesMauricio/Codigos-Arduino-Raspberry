//Aqui vai tudo relacionado ao RTC e ao agendamento de tarefas

// RTC
#define DS1307_ADDRESS 0x68
#include "Wire.h"


byte zero = 0x00; 
byte segundos = 0;        // Segundo atual do RTC
byte minutos = 0;         // Minuto atual do RTC
byte horas = 0;           // Hora atual do RTC
byte diadasemana = 0;     // Dia da semana atual do RTC
byte diadomes = 0;        // Dia do mes atual do RTC
byte mes = 0;             // Mes atual do RTC
byte ano = 0;             // Ano atual do RTC

byte ConverteParaBCD(byte val){ //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)  { //Converte de BCD para decimal
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

