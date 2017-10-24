
/*  Projeto Crema
 *  Alimentador de peixes;
 *  
 *    
 *    
*/

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
//#include <printf.h>
#include "Estruturas.cpp"

// RTC
#include "Wire.h"
#define DS1307_ADDRESS 0x68

// nivel com HC-SR04
#define echoPin 6 // Pino 7 recebe o pulso do echo do Sensor 1
#define trigPin 5 // Pino 6 envia o pulso para gerar o echo do Sensor 1
int profund = 100; // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)
long medianivel = 0;
uint8_t nivel;

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#define nodeID 2  //1-255

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

void initComunic() {
// comunicação
  SPI.begin();    
 
   //  radio.begin();
  mesh.setNodeID(nodeID); 
  mesh.begin();
   
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setCRCLength(RF24_CRC_16);
 
  Serial.println(F("Connecting to the mesh..."));
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

enviaPacote() {
    //   pacote_t pacote = {nodeID, horas, minutos, nivel, 50, 0};
     pacote_t pacote = {nodeID, horas, minutos, 90, 50, 0};
  
  #define intervalo 5000     // tempo em milissegundos para enviar os dados 
  unsigned long past = 0;
  unsigned long now = millis();
  bool atualiza = false;

  atualiza = (now - past) >= intervalo;
  if (atualiza) {
    past = now;
    
    if (!mesh.write(&pacote, 'M', sizeof(pacote))) {     
      if (!mesh.checkConnection() ) {      
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
      }
    } else {
      Serial.print("  TX:");
      Serial.print("  1-NodeID: ");
      Serial.print(nodeID);
      Serial.print("  2-Hora: ");
      Serial.print(horas);
      Serial.print("  3-Minuto: ");
      Serial.print(minutos);  
      Serial.print("  4-Nivel: ");
//      Serial.print(nivel);
      Serial.print("  5-Bateria: ");
      Serial.print("50");
      Serial.print("  6-Erro: ");
      Serial.println("0");
    }
  }
}

recebeDiretriz() {
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);    
    uint32_t dat=0;    
   
    switch(header.type){
      case 'D':
        diretriz_t diretriz;
        network.read(header,&diretriz,sizeof(diretriz));
        Serial.print("  RX:");
        Serial.print("  A-ID:");
        Serial.print(diretriz.alimentID);
        Serial.print("  iniH:");
        Serial.print(diretriz.inicio_hora);
        Serial.print("  iniM:");
        Serial.print(diretriz.inicio_minuto);
        Serial.print("  Freq:");
        Serial.print(diretriz.frequencia);  
        Serial.print("  qtd:");
        Serial.println(diretriz.qtd);                    
        break;
      
      case 'T':
        relogio_t relogio;
        network.read(header,&relogio,sizeof(relogio));
        Serial.print("  RX - Tempo: ");
        Serial.print(relogio.hora);
        Serial.print(":");
        Serial.print(relogio.minu);
        Serial.print(":");
        Serial.print(relogio.segu);
        Serial.print("      dia");
        Serial.print(relogio.diam);
        Serial.print("/");
        Serial.print(relogio.mess);
        Serial.print("/");
        Serial.print(relogio.anoo);
        Serial.print("         semana:");
        Serial.println(relogio.dias); 
        
        Wire.beginTransmission(DS1307_ADDRESS);
        Wire.write(zero);                         //Stop no CI para que o mesmo possa receber os dados
        Wire.write(ConverteParaBCD(relogio.segu));
        Wire.write(ConverteParaBCD(relogio.minu));
        Wire.write(ConverteParaBCD(relogio.hora));
        Wire.write(ConverteParaBCD(relogio.dias));
        Wire.write(ConverteParaBCD(relogio.diam));
        Wire.write(ConverteParaBCD(relogio.mess));
        Wire.write(ConverteParaBCD(relogio.anoo));
        Wire.write(zero);                         //Start no CI
        Wire.endTransmission(); 
             
        break;
        
      default: network.read(header,0,0); //Serial.println(header.type);break;
    }
  } 

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






