//Aqui vai tudo relacionado a comunicação sem fio


#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

#define nodeID 3        //1-255
#define intervalo 15000  // tempo em milissegundos para enviar os dados 

/**** Configure the communication ****/
RF24 radio(CEpin, CSpin);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

void initComunic() {
  SPI.begin();    
  mesh.setNodeID(nodeID);
  Serial.println(F("Connecting to the mesh..."));

  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setCRCLength(RF24_CRC_16);
  
  mesh.begin();
//  Serial.println(F("Conectado a malha!"));
}

bool atualizarMalha()
{
  mesh.update();
  if (!mesh.checkConnection() ) {      
    Serial.println(F("Conexão perdida, renovando endereço"));
    mesh.renewAddress();
    conectado = false;
  }
  conectado = true;
}

void enviaPacote() {
  Nivel();
  pacote_t pacote = { nodeID, hour(), minute(),
                      nivelRacao, 50, 0,
                      dados.temperatura, dados.ph, dados.turbidez, dados.condutividade, dados.oxigen};

 
    if (millis() - past >= intervalo) {
    past = millis();

     if (!mesh.write(&pacote, 'M', sizeof(pacote))) {
         Serial.println(F("Falha ao enviar pacote"));     
        if (!mesh.checkConnection() ) {      
          Serial.println("Renovando Endereço");
          mesh.renewAddress();
        } else {
          Serial.println("Falha no envio, Teste OK");
        }
     } else {
        printPacoteEnviado();
    }
    }
  

  
  
  /*
  unsigned long now = millis();
  bool atualiza = (now - past) >= intervalo;

  if (atualiza) {
    bool enviado;
    past = now;
    
    if( !tempoSinc )
 //     enviado = mesh.write(&pacote, 'T', sizeof(pacote));//0);
    else
      enviado = mesh.write(&pacote, 'M', sizeof(pacote));
    
    if (enviado)
      printPacoteEnviado();
    else
      Serial.println(F("Falha ao enviar pacote"));
  }*/
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
        //agendarDespejo(diretriz);
        printDiretriz(diretriz);  break;
      
      case 'T':
        relogio_t relogio;
        network.read(header,&relogio,sizeof(relogio));
        sincTempo(relogio);
        printTempo(relogio);  break;
        
      default:
        network.read(header,0,0);
        Serial.println(F("Alguma coisa errada recebida..."));
    }
  } 
}
//Outros prints em horario
void printPacoteEnviado()
{
  Serial.print("  TX:");
  Serial.print("    1-NodeID: ");
  Serial.print(nodeID);
  Serial.print("    2-Hora: ");
  Serial.print(hour());
  Serial.print("    3-Minuto: ");
  Serial.print(minute());  
  Serial.print("    4-Nivel: ");
  Serial.print(nivelRacao);
  Serial.print("    5-Bateria: ");
  Serial.print("50");
  Serial.print("    6-Erro: ");
  Serial.print("0");
  Serial.print("    temperatura:");
  Serial.print(dados.temperatura);
  Serial.print("    ph:");
  Serial.print(dados.ph);
  Serial.print("    turbidez:");
  Serial.print(dados.turbidez);
  Serial.print("    condutividade:");
  Serial.print(dados.condutividade);
  Serial.print("    oxigenio:");
  Serial.println(dados.oxigen);
}

void printDiretriz(diretriz_t diretriz)
{
  Serial.print("  RX:");
  Serial.print("  A-ID:");
  Serial.print(diretriz.alimentID);
  
  for(int cont=1; cont<=6; cont++)
  {
  Serial.print("  H");
  Serial.print(cont);
  Serial.print(":");
  Serial.print(diretriz.horad[cont]);
  Serial.print("  M");
  Serial.print(cont);
  Serial.print(":");
  Serial.print(diretriz.minutod[cont]);  
  Serial.print("  Q");
  Serial.print(cont);
  Serial.print(":");
  Serial.print(diretriz.qtdd[cont]);
  }
  Serial.println("  ");
}
