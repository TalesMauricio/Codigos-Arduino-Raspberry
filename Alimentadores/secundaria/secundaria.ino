#include <Wire.h>
#include "dados.cpp"

#define pinTemp A0
#define pinPH   A1
#define pinTurb A2
#define pinCond A3
#define pinOxig A4

Dados_t dados;

void setup() {
  pinMode(8,OUTPUT);
  Wire.begin(1);                // join i2c bus with address #1
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(1000);
  lerSensores();
}

void requestEvent() { // function that executes whenever data is requested by master
  Wire.write(dados.bytes);
}

void lerSensores()
{
  dados.valor.temperatura = analogRead(pinTemp);
  dados.valor.ph = analogRead(pinPH);
  dados.valor.turbidez = analogRead(pinTurb);
  dados.valor.condutividade = analogRead(pinCond);
  dados.valor.oxigen = analogRead(pinOxig);
}

