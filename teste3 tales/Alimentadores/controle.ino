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

 for(int cont=1; cont<=6; cont++)
  {
//    Serial.print("hora ");
//    Serial.print(diretriz.horad[cont]);
//    Serial.print(hour());
//    Serial.print("    minuto ");
//    Serial.print(diretriz.minutod[cont]);
//    Serial.println(minute());
 if(diretriz.horad[cont] == hour() && diretriz.minutod[cont] == minute() && second() == 30) {
    Serial.println(" "); 
    Serial.print("chegou a hora de alimentar");
    Serial.print(cont);
    Serial.print(": "); 
    Serial.print(diretriz.horad[cont]);  
    Serial.print(":");  
    Serial.print(diretriz.minutod[cont]);
    Serial.print("  com : ");
    Serial.print(diretriz.qtdd[cont]);
    Serial.println("kg");  
 }
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