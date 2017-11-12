//Aqui vai tudo relacionado a medição de nível de profundidade

void Nivel()
{ 
  long medianivel = 0;
  for (int i=1; i <= 10; i++){
    long duração = medirTempoEco()
    
    //////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    melhorar o filtro @@@@@@@@@@@@@@@@@@@@@@@@@@@@//////////
    long nivel_atual = tempo / 58 *100 / profund ; //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado ///// distancia = tempo / (29 * 2)//// ..........................
     
      if(nivel_atual <= profund)
        medianivel = (medianivel + nivel_atual);
      else{
        i--;
        delay(100);
      }
    delay(200);
  }
  medianivel = 100-(medianivel/10);
  nivelRacao = medianivel;
}

long medirTempoEco()
{    /* Rotina de funionamento para o Sensor Ultrasson 1 */  
    digitalWrite(trigPin, HIGH); // seta o pino 6 com pulso de "HIGH"
    delayMicroseconds(10); // delay de 10 microssegundos
    digitalWrite(trigPin, LOW); // seta o pino 6 com pulso baixo novamente

    return pulseIn(echoPin, HIGH); // pulseIn lê o tempo entre a chamada e o pino entrar em high
}

