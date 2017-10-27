//Aqui vai tudo relacionado a medição de nível

int profund = 100; // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)
long medianivel = 0;
uint8_t nivel;

void Nivel()
{ 
  /* Rotina de funionamento para o Sensor Ultrasson 1 */  
  for (int i=1; i <= 10; i++){
    digitalWrite(trigPin, LOW); // seta o pino 6 com um pulso baixo "LOW"
    delayMicroseconds(2); // delay de 2 microssegundos
    digitalWrite(trigPin, HIGH); // seta o pino 6 com pulso de "HIGH"
    delayMicroseconds(10); // delay de 10 microssegundos
    digitalWrite(trigPin, LOW); // seta o pino 12 com pulso baixo novamente
    long tempo = pulseIn(echoPin, HIGH); // pulseIn lê o tempo entre a chamada e o pino entrar em high
    
    //////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    melhorar o filtro @@@@@@@@@@@@@@@@@@@@@@@@@@@@//////////
    
    long nivel_atual = tempo / 58 *100 / profund ; //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado ///// distancia = tempo / (29 * 2)//// ..........................
     
      if(nivel_atual <= 100){
        medianivel = (medianivel + nivel_atual);
      }
      else{
        i--;
        delay(100);
      }
    delay(200);
  }
  medianivel = 100-(medianivel/10);
  nivel = medianivel;
  medianivel = 0; 
}

