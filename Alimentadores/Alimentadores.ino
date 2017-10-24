
/*  Projeto Crema
 *  Alimentador de peixes;
 *  
 *   Este código é o principal. Aqui todo o algorítmo deve ser descrito por funções de alto grau de abstração. Isto é necessário para manter o
 *   código o mais compacto o possível e possibilitar uma melhor compreensão do código como todo, sem se perder em detalhes menores. A ideia é
 *   que da forma que for implementado, o código explique por si só, em procedimentos básicos, o algorítmo a ser desempenhado.
*/
  // Só devem ser declaradas as bibliotecas de funções locais de alta abstração. Nada de bibliotecas do arduino ou implementações de baixo nível
#include <SPI.h>
//#include <printf.h>
#include "estruturas.cpp"
#include "comunicacao.cpp"

// RTC
#include "Wire.h"
#define DS1307_ADDRESS 0x68

// nivel com HC-SR04
#define echoPin 6 // Pino 7 recebe o pulso do echo do Sensor 1
#define trigPin 5 // Pino 6 envia o pulso para gerar o echo do Sensor 1
int profund = 100; // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)
long medianivel = 0;
uint8_t nivel;

byte zero = 0x00; 
byte segundos = 0;        // Segundo atual do RTC
byte minutos = 0;         // Minuto atual do RTC
byte horas = 0;           // Hora atual do RTC
byte diadasemana = 0;     // Dia da semana atual do RTC
byte diadomes = 0;        // Dia do mes atual do RTC
byte mes = 0;             // Mes atual do RTC
byte ano = 0;             // Ano atual do RTC


void setup() {
 // serial 
  Serial.begin(115200);
  
  configPins();
  configRTC();
  initComunic();
   
}

void configPins() {
// nivel com HC-SR04
  pinMode(echoPin, INPUT); // define o pino 7 como entrada (recebe)
  pinMode(trigPin, OUTPUT); // define o pino 6 como saida (envia)
}

void configRTC() {
    Wire.begin();
}

void loop() {

  mesh.update();
  Relogio();
//  Nivel();      

  enviaPacote();
  delay(1000);
  recebeDiretriz();

/*
  if (estiver na hora de alimentar){
função de alimentaçao
}
*/
}


////////////////////////////////////////////////////////////////////////// Relogio ////////////////////////////////////////////

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



//////////////////////////////////////////////////////////////////////////////// Nível 
void Nivel()
{ 
  /* Rotina de funionamento para o Sensor Ultrasson 1 */  
  for (int i=1; i <= 10; i++){
    digitalWrite(trigPin, LOW); // seta o pino 6 com um pulso baixo "LOW"
    delayMicroseconds(2); // delay de 2 microssegundos
    digitalWrite(trigPin, HIGH); // seta o pino 6 com pulso de "HIGH"
    delayMicroseconds(10); // delay de 10 microssegundos
    digitalWrite(trigPin, LOW); // seta o pino 12 com pulso baixo novamente
    long tempo = pulseIn(echoPin, HIGH); // pulseIn lê o tempo entre a chamada e o pino entrar em high
    
    //////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    melhorar o filtro @@@@@@@@@@@@@@@@@@@@@@@@@@@@//////////
    
    long nivel_atual = tempo / 58 *100 / profund ; //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado ///// distancia = tempo / (29 * 2)//// ..........................
     
      if(nivel_atual <= 100){
        medianivel = (medianivel + nivel_atual);
      }
      else{
        i--;
        delay(100);
      }
    delay(200);
  }
  medianivel = 100-(medianivel/10);
  nivel = medianivel;
  medianivel = 0; 
}






