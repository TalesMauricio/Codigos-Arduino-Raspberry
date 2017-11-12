//Aqui vai tudo relacionado ao acionamento de cargas, medição e controle dos motores

void configPins() {
  Wire.begin(); //I2C
  
  // nivel de ração com HC-SR04
  pinMode(echoPin, INPUT); // define o pino 7 como entrada (recebe)
  pinMode(trigPin, OUTPUT); // define o pino 6 como saida (envia)
  
  //Célula de carga
  pinMode(ADDO, INPUT_PULLUP);   
  pinMode(ADSK, OUTPUT);
  
  //motor(fuso) e servo(porta) ****/
  pinMode(fuso, OUTPUT);
  
  //medição de bateria
  pinMode(leBatPin, INPUT);   
  pinMode(enBatPin, OUTPUT);
  }

void DespejarRacao()
{
  digitalWrite(fuso, HIGH);
  delay(100);
  digitalWrite(fuso, LOW);
}

void alimentaPeixes(float valorAlimento)
{
  digitalWrite(fuso, HIGH);
  while(lerCelula()<=valorAlimento) delay(100);
  digitalWrite(fuso, LOW);
}
