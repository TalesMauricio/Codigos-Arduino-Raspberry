
#include "defines.h"

diretriz_t diretriz = {61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61};

void setup() {
  Serial.begin(115200);
  configPins();  //Declarado em controle
  //initComunic(); //Declarado em comunicacao
 // Nivel_bat();
 // Nivel_ra();
  
  //fecha_porta(); 
}

void loop() {
  //atualizarMalha();  //Declarado em comunicacao

 // if(conectado)
 // {
  //recebeDiretriz();
  //enviaPacote();
 // }
  //delay(60);
  
  //ini_prot_aliment();
  //reqMedidasSec();
  DespejarRacao(10);
}
