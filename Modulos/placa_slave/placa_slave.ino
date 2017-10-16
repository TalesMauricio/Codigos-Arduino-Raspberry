#include <Wire.h>
#include "pacote.h"

#define nodeID 5
#define horas 2
#define minutos 40
#define nivel 80

union stream
{
    pacote_t pacote;
    char bytes[ sizeof(pacote_t) ];
};

stream pacote = {nodeID, horas, minutos, nivel, 50, 0};

void setup() {
  
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(pacote.bytes); // respond with message of 6 bytes
  // as expected by master
}
