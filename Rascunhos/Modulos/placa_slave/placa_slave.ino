#include <Wire.h>
#include "dados.h"

Dados_t dados = {18, 1, 100, 60, 500};

void setup() {
  pinMode(8,OUTPUT);
  Wire.begin(1);                // join i2c bus with address #1
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(dados.bytes);
  digitalWrite(8, digitalRead(8));
  dados.valor.temperatura++;
  dados.valor.ph++;
  dados.valor.turbidez++;
  dados.valor.condutividade++;
}
