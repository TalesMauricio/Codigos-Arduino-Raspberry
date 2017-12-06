//Aqui vai tudo relacionado a medição de nível de raçao e nivel de bateria

void Nivel_bat()
{
  digitalWrite(enBatPin, HIGH);  
  delay(1500);
  
  nivelBateria = analogRead(leBatPin);            // reads the value of the potentiometer (value between 0 and 1023)
  nivelBateria = map(nivelBateria, 160, 1023, 0, 100);     // scale it to use it with the servo (value between 0 and 180)
  

  /*
  double media_nivelBateria =0;
  int Bater = 0;  
  for (int i=1; i <= 10; i++){    
      Bater = analogRead(leBatPin); 
      media_nivelBateria = media_nivelBateria + ((Bater - 24)/10) ;
      delay(50);
      }
  nivelBateria = (media_nivelBateria/10); 

*/



  
  digitalWrite(enBatPin, LOW);
}



void Nivel_ra()
{ 
  long medianivel = 0;
  int repetir = 10;
  int contagem = 10;
  int erro_r = 0;
  
  for (int i=1; i <= contagem; i++){
    long duracao = medirTempoEco();   
// teste   
    
    
    
// teste    
    
//    long nivel_atual = duracao  / 58 *100 / profund ; //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado ///// distancia = tempo / (29 * 2)//// ..........   
    long nivel_atual = duracao  / 58;
      if(nivel_atual <= profund){
        medianivel = (medianivel + nivel_atual);
        contagem + 2;
        repetir - 2;
//        delay(350); 
      }
      else{
        repetir --;
        erro_r ++;
//        delay(350);        
      }
    delay(300);
  }
 // medianivel = 100-(medianivel/repetir);
  medianivel = (100-(((medianivel/repetir)*100)/profund));
  // medianivel = 100-(medianivel/6);
  nivelRacao = medianivel;
  if (erro_r >= 5){
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

