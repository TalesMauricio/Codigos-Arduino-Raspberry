// Projeto : Medidor de nivel com HC-SR04
//
// 
//

/** Definindo nome e numero dos pinos **/
#define echoPin 6 // Pino 7 recebe o pulso do echo do Sensor 1
#define trigPin 5 // Pino 6 envia o pulso para gerar o echo do Sensor 1
int prfdde = 100; // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)
void setup()
{
  /* Define os pinos como INPUT ou OUTPUT */
  pinMode(echoPin, INPUT); // define o pino 7 como entrada (recebe)
  pinMode(trigPin, OUTPUT); // define o pino 6 como saida (envia) 
  Serial.begin(9600); //inicia a porta serial
}
void loop()
{
  /* Rotina de funionamento para o Sensor Ultrasson 1 */
  digitalWrite(trigPin, LOW); // seta o pino 6 com um pulso baixo "LOW"
  delayMicroseconds(2); // delay de 2 microssegundos
  digitalWrite(trigPin, HIGH); // seta o pino 6 com pulso de "HIGH"
  delayMicroseconds(10); // delay de 10 microssegundos
  digitalWrite(trigPin, LOW); // seta o pino 12 com pulso baixo novamente
  long duration = pulseIn(echoPin, HIGH); // pulseIn lê o tempo entre a chamada e o pino entrar em high
  long distancia = duration / 29 / 2 ; // Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado// porque é o tempo de ida e volta do ultrassom
  /* Calculo do percentual do nivel da caixa */
  long nivel = distancia * 100 / prfdde; // variave nivel atribui o a valor da distancia e calcula
  // o percentual de acordo com a prfdde
  /* Motra na Serial monitor o nivel em % */
  Serial.print("Nivel: ");
  Serial.println(nivel);
 //  Serial.print("%");
  /*** Interface do display ***/
 
  delay(300); // Espera 0,3 segundo para fazer a leitura novamente
}
