
#include <Wire.h>
#include "dados.h"

#define pinAcopl A3
void setup(){
  pinMode(pinAcopl,INPUT_PULLUP);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  bool acoplado;
  Dados_t dados;
  
  acoplado = !digitalRead(pinAcopl);
  if(acoplado)
  {
    dados = recebeDadosSlave();
    
    Serial.print("temperatura: ");
    Serial.println(dados.valor.temperatura);
    Serial.print("ph: ");
    Serial.println(dados.valor.ph);
    Serial.print("turbidez: ");
    Serial.println(dados.valor.turbidez);
    Serial.print("condutividade: ");
    Serial.println(dados.valor.condutividade);
  }
  else  Serial.println("desacoplado!");
  delay(500);
}

Dados_t recebeDadosSlave()
{
  const int size = sizeof(Dados);
  Dados_t dados;
  Wire.requestFrom(1, size);    // request 6 bytes from slave device #8

  while (Wire.available())// slave may send less than requested
    for(int k=0; k<size; k++)
      dados.bytes[k] = Wire.read(); // receive a byte as character
}
