
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

uint32_t displayTimer = 0;

/*Estrutura do pacote a ser enviado
erro:
   Dec ||    Bin   ||  Código
    1: ||      1   ||  Dados recebidos inconpativeis
    2: ||     10   ||  Tempo de alimentação muito grande
    4: ||    100   ||  Porta do alimntador com defeito
    8: ||   1000   ||  Tampa do reservatório aberta
   16: ||  10000   ||  

*/
struct pacote_t
{
  uint8_t alimentadorID; // ID de qual alimentador a informação está sendo enviada  
  uint8_t hora;          // Hora que foi enviada
  uint8_t minuto;        // Minuto que foi enviada
  uint8_t nivel;         // Nível de ração no reservatório 1
  uint8_t bateria;       // Bateria
  uint8_t erro;          // leia a estrutura
};

struct diretriz_t
{
  int alimentID;          // ID do alimentador                       informaçao nao será usada aqui
  int inicio_hora;        // Mora de início
  int inicio_minuto;      // Minuto de início
  int frequencia;         // Frequencia de alimentação
  int qtd;                // Quantidade de raçao a ser despejada  
};

struct relogio_t
{
  byte segu;          // Dado para atualizar o segundo do RTC                       
  byte minu;          // Dado para atualizar o minuto do RTC
  byte hora;          // Dado para atualizar a hora do RTC
  byte dias;          // Dado para atualizar o dia da semana do RTC
  byte diam;          // Dado para atualizar o dia do mes do RTC
  byte mess;          // Dado para atualizar o mes do RTC
  byte anoo;          // Dado para atualizar o ano do RTC
      
};

int atualiza = 5000;     // tempo em milissegundos para enviar os dados 

void setup() {
 // serial 
  Serial.begin(115200);
  
// nivel com HC-SR04
  pinMode(echoPin, INPUT); // define o pino 7 como entrada (recebe)
  pinMode(trigPin, OUTPUT); // define o pino 6 como saida (envia)
  
// RTC  
  Wire.begin();
   
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
  

  unsigned long now = millis();
//   pacote_t pacote = {nodeID, horas, minutos, nivel, 50, 0};
     pacote_t pacote = {nodeID, horas, minutos, 90, 50, 0};
  
  if (millis() - displayTimer >= atualiza) {
    displayTimer = millis();
    
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

  delay(1000);


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






