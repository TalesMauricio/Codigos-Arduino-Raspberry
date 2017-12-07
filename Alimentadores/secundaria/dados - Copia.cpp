<<<<<<< HEAD
#include <Arduino.h>
=======
#include<arduino.h>

>>>>>>> 211d0e8c13a61dc6236216c0d164dbd69f366df3
struct Sensores_t
{
  int16_t temperatura;
  uint8_t ph;
  uint8_t turbidez;
  uint8_t condutividade;
  uint8_t oxigen;
};

union Dados_t
{
    Sensores_t valor;
    char bytes[ sizeof(Sensores_t) ];
};


