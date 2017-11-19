//Aqui vai tudo relacionado ao acionamento de cargas, medição e controle dos motores

#include <Servo.h>

Servo porta;

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
  porta.attach(servo);
  
  //medição de bateria
  pinMode(leBatPin, INPUT);   
  pinMode(enBatPin, OUTPUT);
  }



void ini_prot_aliment()
{
//  Serial.print(diretriz.minutod1);
//  Serial.print("   ");  
//  Serial.print(minute());
//  Serial.print("   ");
//  alimentaPeixes(diretriz.qtdd1);

 if(diretriz.horad1 == hour() && diretriz.minutod1 == minute() && second() == 30) {
    Serial.println(" "); 
    Serial.print("chegou a hora de alimentar 1  ");
    Serial.print(diretriz.horad1);  
    Serial.print(":");  
    Serial.print(diretriz.minutod1);
    Serial.print("com : ");
    Serial.print(diretriz.qtdd1);
    Serial.println("kg");  
 }
 if(diretriz.horad2 == hour() && diretriz.minutod2 == minute() && second() == 30) {
    Serial.println(" "); 
    Serial.print("chegou a hora de alimentar 2  ");
    Serial.print(diretriz.horad2);  
    Serial.print(":");  
    Serial.print(diretriz.minutod2);
    Serial.print("com : ");
    Serial.print(diretriz.qtdd2);
    Serial.println("kg");
 }
 if(diretriz.horad3 == hour() && diretriz.minutod3 == minute() && second() == 30) {
    Serial.println(" "); 
    Serial.print("chegou a hora de alimentar 3  ");
    Serial.print(diretriz.horad3);  
    Serial.print(":");  
    Serial.print(diretriz.minutod3);
    Serial.print("com : ");
    Serial.print(diretriz.qtdd3);
    Serial.println("kg");  
 }
 if(diretriz.horad4 == hour() && diretriz.minutod4 == minute() && second() == 30) {
    Serial.println(" "); 
    Serial.print("chegou a hora de alimentar 4  ");
    Serial.print(diretriz.horad4);  
    Serial.print(":");  
    Serial.print(diretriz.minutod4);
    Serial.print("com : ");
    Serial.print(diretriz.qtdd4);
    Serial.println("kg");
 }
 if(diretriz.horad5 == hour() && diretriz.minutod5 == minute() && second() == 30) {
    Serial.println(" "); 
    Serial.print("chegou a hora de alimentar 5  ");
    Serial.print(diretriz.horad5);  
    Serial.print(":");  
    Serial.print(diretriz.minutod5);
    Serial.print("com : ");
    Serial.print(diretriz.qtdd5);
    Serial.println("kg");  
 }
 if(diretriz.horad6 == hour() && diretriz.minutod6 == minute() && second() == 30) {
    Serial.println(" "); 
    Serial.print("chegou a hora de alimentar 6  ");
    Serial.print(diretriz.horad6);  
    Serial.print(":");  
    Serial.print(diretriz.minutod6);
    Serial.print("com : ");
    Serial.print(diretriz.qtdd6);
    Serial.println("kg");
 }
 

 
  
}



//void alimentaPeixes(float valorAlimento)
void alimentaPeixes(unsigned long valorAlimento)
{
  //AlarmId id = Alarm.getTriggeredAlarmId();
  //float valorAlimento, massa = qtdRacao[id];


  /*
  float valorAlimento;
  
  bool pronto = false;
  
  while(!pronto)
  {
    if(massa > 10.0)
      valorAlimento = 10.0;
    else {
      valorAlimento = massa;
      pronto = true;
    }
    DespejarRacao(valorAlimento);
    esvaziarCompatimento();
  }
  */
  valorAlimento = 7677514; //valor exemplo
  digitalWrite(fuso, HIGH);
  while(lerCelula()>=valorAlimento) delay(100);
  digitalWrite(fuso, LOW);
  
  esvaziarCompatimento();
  delay(60000);
}

/*
void DespejarRacao(float pesoAlimento)
{
  float bufferPeso[20] = {0};
  
  digitalWrite(fuso, HIGH);
  while( obterPeso(bufferPeso) <= pesoAlimento ); //delay(100);
  
  digitalWrite(ADSK, HIGH);
  digitalWrite(fuso, LOW);
}*/

void esvaziarCompatimento()
{
  porta.write(anguloPortaAbert);
  delay(tempoPortaAbert);
  porta.write(anguloPortaFecha);
}

