//Aqui vai tudo relacionado a comunicação sem fio

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

#define nodeID 3        //1-255
#define intervalo 5000  // tempo em milissegundos para enviar os dados 

/**** Configure the communication ****/
RF24 radio(CEpin, CSpin);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

void initComunic() {
  SPI.begin();    
  mesh.setNodeID(nodeID);
  while (!Serial)
  Serial.println(F("Connecting to the mesh..."));

  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setCRCLength(RF24_CRC_16);
  
  mesh.begin();
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
  pacote_t pacote = { nodeID, hour(), minute(),
                      90, 50, 0,
                      dados.temperatura, dados.ph, dados.turbidez, dados.condutividade, dados.oxigen};
  
  
  bool atualiza = (millis() - past) >= intervalo;

  if (atualiza) {
    bool enviado;
    past = millis();
    
    if( !tempoSinc )
      enviado = mesh.write(&pacote, 'M', sizeof(pacote));//0);
    else
      enviado = mesh.write(&pacote, 'M', sizeof(pacote));
    
    if (enviado)
      printPacoteEnviado();
    else
      Serial.println(F("Falha ao enviar pacote"));
  }
}

void recebeDiretriz() {
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);    
    uint32_t dat=0;    
   
    switch(header.type){
      case 'D':
        diretriz_t diretriz;
        network.read(header,&diretriz,sizeof(diretriz));
        printDiretriz(diretriz);
        agendarDespejo(diretriz);  break;
      
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
  Serial.print(F("  TX:"));
  Serial.print(F("    1-NodeID: "));
  Serial.print(nodeID);
  Serial.print(F("    2-Hora: "));
  Serial.print(hour());
  Serial.print(F("    3-Minuto: "));
  Serial.print(minute());  
  Serial.print(F("    4-Nivel: "));
  Serial.print(nivelRacao);
  Serial.print(F("    5-Bateria: "));
  Serial.print("50");
  Serial.print(F("    6-Erro: "));
  Serial.print("0");
  Serial.print(F("    temperatura:"));
  Serial.print(dados.temperatura);
  Serial.print(F("    ph:"));
  Serial.print(dados.ph);
  Serial.print(F("    turbidez:"));
  Serial.print(dados.turbidez);
  Serial.print(F("    condutividade:"));
  Serial.print(dados.condutividade);
  Serial.print(F("    oxigenio:"));
  Serial.println(dados.oxigen);
}

