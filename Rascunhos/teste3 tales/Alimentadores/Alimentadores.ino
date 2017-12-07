
#include "defines.h"


void setup() {
  Serial.begin(115200);
  configPins();  //Declarado em controle
  initComunic(); //Declarado em comunicacao
}

void loop() {
  atualizarMalha();  //Declarado em comunicacao
  if(conectado)
  {
    recebeDiretriz();
    enviaPacote();
  }
  delay(50);
  
  ini_prot_aliment();
//  medirBateria();
  reqMedidasSec();
}
