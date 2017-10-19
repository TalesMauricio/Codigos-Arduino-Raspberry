// Programa : Data e Hora com DS1307
// Autor : Arduino e Cia

#include "Wire.h"
#define DS1307_ADDRESS 0x68

byte zero = 0x00; 

  byte segundos = 0;
  byte minutos = 0;
  byte horas = 0;
  byte diadasemana = 0;
  byte diadomes = 0;
  byte mes = 0;
  byte ano = 0;

void setup()
{

  Wire.begin();
  Serial.begin(115200);
  //A linha abaixo pode ser retirada apos setar a data e hora
  SelecionaDataeHora(); 
}

void loop()
{
  Mostrarelogio();
  delay(1000);

  
}

void SelecionaDataeHora()   //Seta a data e a hora do DS1307
{
  byte segundos = 06; //Valores de 0 a 59
  byte minutos = 46; //Valores de 0 a 59
  byte horas = 19; //Valores de 0 a 23
  byte diadasemana = 2; //Valores de 0 a 6 - 0=Domingo, 1 = Segunda, etc.
  byte diadomes = 17; //Valores de 1 a 31
  byte mes = 10; //Valores de 1 a 12
  byte ano = 17; //Valores de 0 a 99
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados

  //As linhas abaixo escrevem no CI os valores de 
  //data e hora que foram colocados nas variaveis acima
  Wire.write(ConverteParaBCD(segundos));
  Wire.write(ConverteParaBCD(minutos));
  Wire.write(ConverteParaBCD(horas));
  Wire.write(ConverteParaBCD(diadasemana));
  Wire.write(ConverteParaBCD(diadomes));
  Wire.write(ConverteParaBCD(mes));
  Wire.write(ConverteParaBCD(ano));
  Wire.write(zero); //Start no CI
  Wire.endTransmission(); 
}

byte ConverteParaBCD(byte val){ //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)  { //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}

void Mostrarelogio()
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

  //Mostra a data no Serial Monitor
  Serial.print("Data: ");
  Serial.print(diadomes);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/");
  Serial.print(ano);
  Serial.print(" ");
  Serial.print("Hora : ");
  Serial.print(horas);
  Serial.print(":");
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos);
 
}

