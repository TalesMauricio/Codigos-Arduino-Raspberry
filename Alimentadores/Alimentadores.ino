
/*  Projeto Crema
 *  Alimentador de peixes;
 *  
 *   Este código é o principal. Aqui todo o algorítmo deve ser descrito por funções de alto grau de abstração. Isto é necessário para manter o
 *   código o mais compacto o possível e possibilitar uma melhor compreensão do código como todo, sem se perder em detalhes menores. A ideia é
 *   que da forma que for implementado, o código explique por si só, em procedimentos básicos, o algorítmo a ser desempenhado.
*/
  // Só devem ser declaradas as bibliotecas de funções locais de alta abstração. Nada de bibliotecas do arduino ou implementações de baixo nível
#include <SPI.h>
#include "pinos.h"
#include "comunicacao.cpp"
#include "nivel.cpp"

// nivel com HC-SR04

int profund = 100; // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)
long medianivel = 0;
uint8_t nivel;


void setup() {
 // serial 
  Serial.begin(115200);
  
  configPins();
  configRTC();
  initComunic();
   
}

void loop() {

  mesh.update();
  Relogio();
//  Nivel();      

  enviaPacote();
  delay(1000);
  recebeDiretriz();

/*
  if (estiver na hora de alimentar){
função de alimentaçao
}
*/
}


////////////////////////////////////////////////////////////////////////// Relogio ////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////// Nível 







