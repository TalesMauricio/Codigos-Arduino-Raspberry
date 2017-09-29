
/* 
 *  RF24Mesh_Example.ino by TMRh20
 *  simpless

  
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
int prfdde = 100; // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)


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

int atualiza = 5000;



void setup() {
 
// nivel com HC-SR04
  pinMode(echoPin, INPUT); // define o pino 7 como entrada (recebe)
  pinMode(trigPin, OUTPUT); // define o pino 6 como saida (envia)
  
// RTC
  Wire.begin();
   
// comunicação
  SPI.begin();    
  mesh.setNodeID(nodeID);  
  Serial.println(F("Connecting to the mesh..."));
   //  radio.begin();
  mesh.begin();

// serial 
  Serial.begin(115200);
 
}

void loop() {

  //////////////////////////////////////////Nível
  
  /* Rotina de funionamento para o Sensor Ultrasson 1 */
  digitalWrite(trigPin, LOW); // seta o pino 6 com um pulso baixo "LOW"
  delayMicroseconds(2); // delay de 2 microssegundos
  digitalWrite(trigPin, HIGH); // seta o pino 6 com pulso de "HIGH"
  delayMicroseconds(10); // delay de 10 microssegundos
  digitalWrite(trigPin, LOW); // seta o pino 12 com pulso baixo novamente
  long duration = pulseIn(echoPin, HIGH); // pulseIn lê o tempo entre a chamada e o pino entrar em high
  long distancia = duration / 29 / 2 ; // Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado// porque é o tempo de ida e volta do ultrassom
  /* Calculo do percentual do nivel da caixa */
  long nivel = distancia * 100 / prfdde; // variave nivel atribui o a valor da distancia e calcula
  
  //////////////////////////////////////////fim Nível
 
  mesh.update();
  Relogio();

  unsigned long now = millis();
   pacote_t pacote = {nodeID, 1, nivel, horas, minutos};
  // Send to the master node every second
  if (millis() - displayTimer >= atualiza) {
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
      Serial.print("Conexao OK:  //// ");
      // Serial.println(displayTimer);
      Serial.print("   val.env ");
      Serial.print("  1-nodeID: ");
      Serial.print(nodeID);
      Serial.print("  2-t-inf: ");
      Serial.print("1");
      Serial.print("  3-inf: ");
      Serial.print("102");  
      Serial.print("  4-Hora : ");
      Serial.print(horas);
      Serial.print(":");
      Serial.print(minutos); 
      Serial.print("   ////  ");
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
        Serial.print("  recebe   A-ID:");
        Serial.print(diretriz.alimentID);
        Serial.print("  ini:");
        Serial.print(diretriz.inicio);
        Serial.print("  Freq:");
        Serial.print(diretriz.frequencia);  
        Serial.print("  qtd:");
        Serial.print(diretriz.qtd); 
        Serial.print("  T-Tran:");
        Serial.print(diretriz.transf);
        atualiza = ((diretriz.transf)*1000); 
        Serial.print("  atl:");
        Serial.println(atualiza);
           
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











