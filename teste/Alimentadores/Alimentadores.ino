
/* 
 *   Projeto Crema
 *   Alimentador de peixes;
 *  
 *   Este código é o principal. Aqui todo o algorítmo deve ser descrito por funções de alto grau de abstração. Isto é necessário para manter o
 *   código o mais compacto o possível e possibilitar uma melhor compreensão do código como todo, sem se perder em detalhes menores. A ideia é
 *   que da forma que for implementado, o código explique por si só, em procedimentos básicos, o algorítmo a ser desempenhado.
 *   
 *   Todos os pinos e variaveis globais estão em defines.h
 *   
 *   Todas as structs estão em estruturas.cpp
*/
  // Só devem ser declaradas as bibliotecas de funções locais de alta abstração. Nada de bibliotecas do arduino ou implementações de baixo nível
#include "defines.h"

diretriz_t diretriz = {61,61,61,61};

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
  delay(1000);
  
//  ini_prot_aliment();
//  medirBateria();
  reqMedidasSec();
}
