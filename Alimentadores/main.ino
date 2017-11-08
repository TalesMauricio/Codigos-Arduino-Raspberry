
/* 
 *   Este código é o principal. Aqui todo o algorítmo deve ser descrito por funções de alto grau de abstração. Isto é necessário para manter o
 *   código o mais compacto o possível e possibilitar uma melhor compreensão do código como todo, sem se perder em detalhes menores. A ideia é
 *   que da forma que for implementado, o código explique por si só, em procedimentos básicos, o algorítmo a ser desempenhado.
*/
  // Só devem ser declaradas as bibliotecas de funções locais de alta abstração. Nada de bibliotecas do arduino ou implementações de baixo nível

void setup() {
  Serial.begin(115200);
  
  configPins();
  configRTC();
  initComunic();
}

void loop() {
  mesh.update();
  Relogio();
//  Nivel();      

  requisitarMedidas();
  enviaPacote();
  delay(1000);
  recebeDiretriz();

  verificaHorario(diretriz);
}

void configPins() {
  Wire.begin(); //I2C
  
  // nivel com HC-SR04
  pinMode(echoPin, INPUT); // define o pino 7 como entrada (recebe)
  pinMode(trigPin, OUTPUT); // define o pino 6 como saida (envia)
  
  //Célula de carga
  pinMode(ADDO, INPUT_PULLUP);   
  pinMode(ADSK, OUTPUT);        
  pinMode(fuso, OUTPUT);
}

void configRTC() {
    
}

void verificaHorario(diretriz_t diretriz) {  //Verificar se está no horário de alimentar
  if ((diretriz.inicio_hora==horas) && (diretriz.inicio_minuto==minutos))
    alimentaPeixes(diretriz.qtd);
}



