 
 
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

struct payload_t {                  // Structure of our payload
  unsigned long ms;
  unsigned long counter;  
  int segundos_p;
  int minutos_p;
  int horas_p;
  int diadomes_p;
  int mes_p;
  int ano_p;    
};


void setup() {
  Serial.begin(115200); 
  mesh.setNodeID(0);
  Serial.println(mesh.getNodeID());
  mesh.begin();

}


void loop() {  
  
  mesh.update();  
  mesh.DHCP();  
  
 
  if(network.available()){
    RF24NetworkHeader header;

/* //////////////////////  exemplo helloworld_rx

    payload_t payload;
    network.read(header,&payload,sizeof(payload));
    Serial.print("Received packet #");
    Serial.print(payload.counter);
    Serial.print(" at ");
    Serial.println(payload.ms);





*/ ////////////////////// FIM exemplo helloworld_rx
    
    network.peek(header);
    
    uint32_t dat=0;
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
//      case 'M': network.read(header,&dat,sizeof(dat)); 
//      Serial.println(dat); 
//      break;

      case 'H':
      payload_t payload;
    network.read(header,&payload,sizeof(payload));
    Serial.print("Pacote N:");
    Serial.print(payload.counter);
    Serial.print(" Teste conexao ok: ");
    Serial.print(payload.ms);
    
    Serial.print("             Data: ");
    Serial.print(payload.diadomes_p);
    Serial.print("/");
    Serial.print(payload.mes_p);
    Serial.print("/");
    Serial.print(payload.ano_p);
    Serial.print(" ");
    Serial.print("    Hora : ");
    Serial.print(payload.horas_p);
    Serial.print(":");
    Serial.print(payload.minutos_p);
    Serial.print(":");
    Serial.println(payload.segundos_p);    
   
    
      break;
      default: network.read(header,0,0); //Serial.println(header.type);break;
    }
  }
  
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
