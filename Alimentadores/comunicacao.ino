//Aqui vai tudo relacionado a comunicação sem fio
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

#define nodeID  2       //1-255
#define intervalo 5000  // tempo em milissegundos para enviar os dados 
#define zero 0x00

pacote_t pacote;
diretriz_t diretriz;

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9, 10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

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

void enviaPacote() {
  pacote = {nodeID, horas, minutos, 90, 50, 0, dados.valor.temperatura, dados.valor.ph, dados.valor.turbidez, dados.valor.condutividade, dados.valor.oxigen};

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
      Serial.print("0");
      Serial.print("temperatura:");
      Serial.print(dados.valor.temperatura);
      Serial.print("   ph:");
      Serial.print(dados.valor.ph);
      Serial.print("   turbidez:");
      Serial.print(dados.valor.turbidez);
      Serial.print("   condutividade:");
      Serial.print(dados.valor.condutividade);
      Serial.print("   oxigenio:");
      Serial.println(dados.valor.oxigen);
    }
  }
}

void recebeDiretriz() {
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);    
    uint32_t dat=0;    
   
    switch(header.type){
      case 'D':
        //diretriz_t diretriz;
        network.read(header,&diretriz,sizeof(diretriz));
        Serial.print("  RX:");
        Serial.print("  A-ID:");
        Serial.print(diretriz.alimentID);
        Serial.print("  iniH:");
        Serial.print(diretriz.inicio_hora);
        Serial.print("  iniM:");
        Serial.print(diretriz.inicio_minuto);
        //Serial.print("  Freq:");
        //Serial.print(diretriz.frequencia);  
        Serial.print("  qtd:");
        Serial.println(diretriz.qtd);                    
        break;
      
      case 'T':
        //relogio_t relogio;
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

