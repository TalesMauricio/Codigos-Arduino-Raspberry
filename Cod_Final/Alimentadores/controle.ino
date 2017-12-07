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
    Serial.print(float(diretriz.qtdd[cont])/10);
    Serial.println("kg");  
    alimentaPeixes(diretriz.qtdd[cont]);


    
    flag_a = true;
    pastflag = millis();
        
 }
 }
   
  if (millis() - pastflag >= 60000 ) {   
     flag_a = false;    
  }


  
}



void alimentaPeixes(unsigned int valorAlimento)
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
  float massa = ((float)valorAlimento)/10;
  while(massa > 10)
  {
    DespejarRacao(10);
    esvaziarCompatimento(valorAlimento);
    
    massa = massa - 10;
    valorAlimento = valorAlimento - 100;
  }

  DespejarRacao(massa);
  esvaziarCompatimento(valorAlimento);

}


void DespejarRacao(float pesoAlimento)
{
  float bufferPeso[20] = {0};
  flag_alimenta=millis();
  digitalWrite(fuso, HIGH);
  while( (obterPeso(bufferPeso) <= pesoAlimento) || ((millis()-flag_alimenta)<= pesoAlimento*tempoPortaAbert*10));
  
  digitalWrite(ADSK, HIGH);
  digitalWrite(fuso, LOW);
}

void esvaziarCompatimento(unsigned int pesoAlimento)
{
  porta.write(anguloPortaFecha);
  delay(2000);
  digitalWrite(enServo, HIGH);
  porta.write(anguloPortaAbert);
  delay(1.2*tempoPortaAbert*pesoAlimento);
  porta.write(anguloPortaFecha);
  delay(2000);
  digitalWrite(enServo, LOW);
}


void fecha_porta()
{
  porta.write(anguloPortaFecha);
}

