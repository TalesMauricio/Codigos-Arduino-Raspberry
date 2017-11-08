
struct Dados
{
  unsigned char temperatura;
  unsigned char ph;
  unsigned char turbidez;
  unsigned char condutividade;
  unsigned char oxigen;
};

union Dados_t
{
    Dados valor;
    char bytes[ sizeof(Dados) ];
};

