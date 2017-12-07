
#include "defines.h"

diretriz_t diretriz = {61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61};

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
  Alarm.delay(1000);
//  ini_prot_aliment();
//  medirBateria();
  reqMedidasSec();
}
