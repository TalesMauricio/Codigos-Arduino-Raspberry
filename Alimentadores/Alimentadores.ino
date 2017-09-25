
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

int comut = 1;

byte zero = 0x00; 
int segundos = 0;
int minutos = 0;
int horas = 0;
int diadasemana = 0;
int diadomes = 0;
int mes = 0;
int ano = 0;


uint32_t displayTimer = 0;
////////////////////////////   helloworld_tx


const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already

////////////////////////////// FIM helloworld_tx


//Estrutura do pacote a ser enviado
struct pacote_t
{
  uint8_t alimentadorID; //ID de qual alimentador a informação está sendo enviada
  uint8_t tipoInfo;      //Tipo da informação
  uint8_t Info;          //Informação
  uint8_t hora;          //Hora que foi enviada
  uint8_t minuto;        //Minuto que foi enviada
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
  Relogio();

  mesh.update();

///////////////////////////  helloworld_tx

 unsigned long now = millis();              // If it's time to send a message, send it!
//  if ( now - last_sent >= interval  )
//  {
//    last_sent = now;

//    Serial.print("Sending...");
    pacote_t pacote = { nodeID, 1, 1024, horas, minutos};
//    RF24NetworkHeader header(/*to node*/ other_node);
//    bool ok = network.write(header,&payload,sizeof(payload));
  if (!mesh.write(&payload, 'H', sizeof(payload))) {
    if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("ress");
//        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
      }
    } else {
      Serial.print("            Pacote N:"); Serial.print(packets_sent);
      last_sent = now;
    }
    
//    if (ok)
//      Serial.println("ok.");
//    else
//      Serial.println("failed.");
//  }

delay(1000);
////////////////////////////// FIM helloworld_tx



  // Send to the master node every second
  if (millis() - displayTimer >= 1000) {
    displayTimer = millis();

    // Send an 'M' type message containing the current millis()
    if (!mesh.write(&displayTimer, 'M', sizeof(displayTimer))) {

      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
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
  
///////////////// parte esquisita...

  while (network.available()) {
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header, &payload, sizeof(payload));
    Serial.print("Received packet #");
    Serial.print(payload.counter);
    Serial.print(" at ");
    Serial.println(payload.ms);
  }
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











