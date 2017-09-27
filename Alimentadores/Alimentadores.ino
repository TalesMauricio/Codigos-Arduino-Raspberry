
/* 
 *  RF24Mesh_Example.ino by TMRh20
 *  simpless

  
*/


#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
//#include <printf.h>
#include "Wire.h"
#define DS1307_ADDRESS 0x68


/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);
#define nodeID 3  //1-255

byte zero = 0x00; 
int segundos = 0;
int minutos = 0;
int horas = 0;
int diadasemana = 0;
int diadomes = 0;
int mes = 0;
int ano = 0;


uint32_t displayTimer = 0;

//Estrutura do pacote a ser enviado
struct pacote_t
{
  uint8_t alimentadorID; //ID de qual alimentador a informação está sendo enviada
  uint8_t tipoInfo;      //Tipo da informação
  uint8_t info;          //Informação
  uint8_t hora;          //Hora que foi enviada
  uint8_t minuto;        //Minuto que foi enviada
};

struct diretriz_t
{
  uint8_t alimentID;     //ID do alimentador                       informaçao nao será usada aqui
  uint8_t inicio;            //hora de início
  uint8_t frequencia;        //frequencia de alimentação
  uint8_t qtd;               //quantidade de raçao despejada
  uint8_t transf;          //tempo de atualização dos dados
};



void setup() {
  
  Wire.begin();
  Serial.begin(115200);
  SPI.begin();    
  mesh.setNodeID(nodeID);  
  Serial.println(F("Connecting to the mesh..."));
//  radio.begin();
  mesh.begin();   
}



void loop() {
 
  mesh.update();
  Relogio();

  unsigned long now = millis();
   pacote_t pacote = {nodeID, 1, 102, horas, minutos};
  // Send to the master node every second
  if (millis() - displayTimer >= 1000) {
    displayTimer = millis();

    // Send an 'M' type message containing the current millis()
    if (!mesh.write(&pacote, 'M', sizeof(pacote))) {

      // If a write fails, check connectivity to the mesh network
      if (!mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
      }
    } else {
      Serial.print("       Teste de conexao OK: "); Serial.println(displayTimer);
    }
  }

  delay(1000);


if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);    
    uint32_t dat=0;    
    diretriz_t diretriz;
    network.read(header,&diretriz,sizeof(diretriz));
    switch(header.type){
      case 'D':
        Serial.print("Alimentador:");
        Serial.print(diretriz.alimentID);
        Serial.print("    inicio:");
        Serial.print(diretriz.inicio);
        Serial.print("    Frequencia:");
        Serial.print(diretriz.frequencia);  
        Serial.print("    qtd:");
        Serial.print(diretriz.qtd); 
        Serial.print("transf");
        Serial.println(diretriz.transf);   
        break;
        
      default: network.read(header,0,0); //Serial.println(header.type);break;
    }
  }









  
///////////////// parte esquisita...
/*
  while (network.available()) {
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header, &payload, sizeof(payload));
    Serial.print("Received packet #");
    Serial.print(payload.counter);
    Serial.print(" at ");
    Serial.println(payload.ms);
  }
  */
}

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











