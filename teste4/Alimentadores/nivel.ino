//Aqui vai tudo relacionado a medição de nível de raçao e nivel de bateria

void Nivel_bat()
{
 // digitalWrite(enBatPin, HIGH);
 // delay(1);
// for (int i=1; i <= 2; i++){
//   }

  nivelBateria = analogRead(leBatPin); 
  nivelBateria = nivelBateria - (nivelBateria % 5);
 // nivelBateria = 1.25 * nivelBateria - 938.75 ;// * nivelBateria
//         Serial.println(" tensao da bateria ");
//         Serial.println(nivelBateria); 
 //  digitalWrite(enBatPin, LOW);
}



void Nivel_ra()
{ 
  long medianivel = 0;
  
  for (int i=1; i <= 2; i++){
    long duracao = medirTempoEco();    
    
    long nivel_atual = duracao  / 58 *100 / profund ; //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado ///// distancia = tempo / (29 * 2)//// ..........................
     
//      if(nivel_atual <= profund)
        medianivel = (medianivel + nivel_atual);
//      else{
//        i--;
//        delay(100);
//      }
    delay(200);
  }
  medianivel = 108-(medianivel/2);
  nivelRacao = medianivel;
  if (nivelRacao >= 100){
    erro_nivel_ra = true;
  }else{
     erro_nivel_ra = false;    
  }
}

long medirTempoEco()
{    
    digitalWrite(trigPin, LOW); // seta o pino 6 com um pulso baixo "LOW"
    delayMicroseconds(2); // delay de 2 microssegundos
    digitalWrite(trigPin, HIGH); // seta o pino 6 com pulso de "HIGH"
    delayMicroseconds(10); // delay de 10 microssegundos
    digitalWrite(trigPin, LOW); // seta o pino 6 com pulso baixo novamente

    return pulseIn(echoPin, HIGH); // pulseIn lê o tempo entre a chamada e o pino entrar em high
}

