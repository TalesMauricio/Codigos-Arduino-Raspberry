//Aqui vai tudo relacionado a medição de nível
#include "Wire.h"

#define echoPin 6 // Pino 7 recebe o pulso do echo do Sensor 1
#define trigPin 5 // Pino 6 envia o pulso para gerar o echo do Sensor 1

void configPins() {
// nivel com HC-SR04
  pinMode(echoPin, INPUT); // define o pino 7 como entrada (recebe)
  pinMode(trigPin, OUTPUT); // define o pino 6 como saida (envia)
  Wire.begin(); //RTC
}

void configRTC() {
    
}

