
#include <Wire.h>
#include "dados.h"

#define pinAcopl A3
void setup() {
  pinMode(pinAcopl,INPUT_PULLUP)
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  bool acoplado;
  int size = sizeof(Dados);
  Dados_t dados;
  
  acoplado = !digitalRead(pinAcopl)
  if(acoplado)
  {
    Wire.requestFrom(0, size);    // request 6 bytes from slave device #8

    while (Wire.available())// slave may send less than requested
    {
      for(int k=0; k<size; k++)
      {
        dados.bytes[k] = Wire.read(); // receive a byte as character
      }
      Serial.println("temperatura: ");
      Serial.print(dados.valor.temperatura);
      Serial.println("ph: ");
      Serial.print(dados.valor.ph);
      Serial.println("turbidez: ");
      Serial.print(dados.valor.turbidez);
      Serial.println("condutividade: ");
      Serial.print(dados.valor.condutividade);
    }
  }
  delay(500);
}
