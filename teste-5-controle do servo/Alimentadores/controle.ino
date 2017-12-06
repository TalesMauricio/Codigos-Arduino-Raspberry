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
  pinMode(enServo, OUTPUT);
  porta.attach(servo);
  
  //medição de bateria
  pinMode(leBatPin, INPUT);   
  pinMode(enBatPin, OUTPUT);
  

  //medição de erros
  pinMode(tampa, INPUT);   
//  pinMode(rotfuso, INPUT);
  }



void ini_prot_aliment()
{

 for(int cont=0; cont<6; cont++)
  {
 if(diretriz.horad[cont] == hour() && diretriz.minutod[cont] == minute() && flag_a == false){
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
    alimentaPeixes(float(diretriz.qtdd[cont]));


    
    flag_a = true;
    pastflag = millis();
        
 }
 }
   
  if (millis() - pastflag >= 60000 ) {   
     flag_a = false;    
  }


  
}



void alimentaPeixes(float valorAlimento)
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
//  valorAlimento = valorAlimento/10;
//  while(valorAlimento > 10.0)
//  {
//    DespejarRacao(valorAlimento);
//    esvaziarCompatimento();
//    
//    valorAlimento = valorAlimento - 10.0;
//  }
//
//  DespejarRacao(valorAlimento);
//  esvaziarCompatimento();

  digitalWrite(fuso, HIGH);
  //while( obterPeso(bufferPeso) <= pesoAlimento ); //delay(100);
  delay(5000);
  digitalWrite(ADSK, HIGH);
  digitalWrite(fuso, LOW);
}


void DespejarRacao(float pesoAlimento)
{
  float bufferPeso[20] = {0};
  
  digitalWrite(fuso, HIGH);
  while( obterPeso(bufferPeso) <= pesoAlimento ); //delay(100);
  
  digitalWrite(ADSK, HIGH);
  digitalWrite(fuso, LOW);
}

void esvaziarCompatimento()
{
  int pos = anguloPortaFecha;    // variable to store the servo position
  
  porta.write(anguloPortaFecha);
  delay(2000);
  digitalWrite(enServo, HIGH);  
  
  porta.write(anguloPortaAbert);
  for (pos = anguloPortaFecha;  pos <= anguloPortaAbert; pos += 1) {   
    porta.write(pos);           
    delay(15);                     
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);             
    delay(15);                     
  }


  
  delay(tempoPortaAbert);
  porta.write(anguloPortaFecha);
  delay(2000);
  digitalWrite(enServo, LOW);
}
void Fecha_porta()
{
  porta.write(anguloPortaFecha);
 }
}


