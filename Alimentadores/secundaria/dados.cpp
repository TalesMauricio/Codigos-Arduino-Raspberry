#include<arduino.h>

struct Sensores_t
{
  uint8_t temperatura;
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


