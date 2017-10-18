#include <Wire.h>
#include "dados.h"

Dados_t dados = {18, 1, 100, 60, 500};

void setup() {

  Wire.begin(0);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(dados.bytes);

  dados.valor.temperatura++;
  dados.valor.ph++;
  dados.valor.turbidez++;
  dados.valor.condutividade++;
}
