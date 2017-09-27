 
 
 /** RF24Mesh_Example_Master.ino by TMRh20
  * simples
  *
  *
  *
  */
  
  
#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"
#include <SPI.h>
//Include eeprom.h for AVR (Uno, Nano) etc. except ATTiny
#include <EEPROM.h>
#include "Wire.h"
#define DS1307_ADDRESS 0x68

/***** Configure the chosen CE,CS pins *****/
RF24 radio(9,53);  //arduino mega
RF24Network network(radio);
RF24Mesh mesh(radio,network);


uint32_t displayTimer = 0;

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
  uint8_t alimentID;         //ID do alimentador                       informaçao nao será usada aqui
  uint8_t inicio;            //hora de início
  uint8_t frequencia;        //frequencia de alimentação
  uint8_t qtd;               //quantidade de raçao despejada
  uint8_t transf;          //tempo de atualização dos dados
};



void setup() {
  Serial.begin(115200); 
  mesh.setNodeID(0);
   Serial.print("Meu IP:");
  Serial.println(mesh.getNodeID());
  mesh.begin();

}


void loop() {  
  
  mesh.update();  
  mesh.DHCP();  
  
 
  if(network.available()){
    RF24NetworkHeader header;

    network.peek(header);
    
    uint32_t dat=0;
    
    pacote_t pacote;
    network.read(header,&pacote,sizeof(pacote));
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
//      case 'M': network.read(header,&dat,sizeof(dat)); 
//      Serial.println(dat); 
//      break;

      case 'M':
        Serial.print("Alimentador:");
        Serial.print(pacote.alimentadorID);
        Serial.print("    Sensor:");
        Serial.print(pacote.tipoInfo);
        Serial.print("    Valor medido:");
        Serial.print(pacote.info);  
        Serial.print("    Hora:");
        Serial.print(pacote.hora); 
        Serial.print(":");
        Serial.println(pacote.minuto);   
        break;
        
      default: network.read(header,0,0); //Serial.println(header.type);break;
    }
  }

//////////////////////////  enviar

  diretriz_t diretriz = {5, 10, 15, 20, 25};
  
if (!mesh.write(&diretriz, 'D', sizeof(diretriz),3)) {
       
      if (!mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("sem conexão");
//        mesh.renewAddress();
      } else {
        Serial.println("Send fail");
      }
    } else {
      Serial.print("       Teste de conexao ok ");
    }

////////////////////// fim enviar
  
  
  if(millis() - displayTimer > 5000){
    displayTimer = millis();
    Serial.println(" ");
    Serial.println(F("********Assigned Addresses********"));
     for(int i=0; i<mesh.addrListTop; i++){
       Serial.print("NodeID: ");
       Serial.print(mesh.addrList[i].nodeID);
       Serial.print(" RF24Network Address: 0");
       Serial.println(mesh.addrList[i].address,OCT);
     }
    Serial.println(F("**********************************"));
  }
}
