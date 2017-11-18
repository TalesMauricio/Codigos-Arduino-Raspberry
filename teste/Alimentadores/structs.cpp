#include <arduino.h>
/*Estrutura do pacote a ser enviado
erro:
   Dec ||    Bin   ||  Código
    1: ||      1   ||  Dados recebidos inconpativeis
    2: ||     10   ||  Tempo de alimentação muito grande
    4: ||    100   ||  Porta do alimntador com defeito
    8: ||   1000   ||  Tampa do reservatório aberta
   16: ||  10000   ||  

*/
struct pacote_t
{
  uint8_t alimentadorID; // ID de qual alimentador a informação está sendo enviada  
  uint8_t hora;          // Hora que foi enviada
  uint8_t minuto;        // Minuto que foi enviada
  uint8_t nivel;         // Nível de ração no reservatório 1
  uint8_t bateria;       // Bateria
  uint8_t erro;          // leia a estrutura
  uint8_t temperatura;
  uint8_t ph;
  uint8_t turbidez;
  uint8_t condutividade;
  uint8_t oxigen;
};

struct diretriz_t
{
  uint8_t alimentID;          // ID do alimentador                       informaçao nao será usada aqui
  uint8_t horad1;        // Mora de início
  uint8_t minutod1;      // Minuto de início
  float qtdd1;                // Quantidade de raçao a ser despejada  
};




struct relogio_t
{
  uint8_t segundo; 
  uint8_t minuto; 
  uint8_t hora;
  uint8_t dia;
  uint8_t mes;
  uint8_t ano;
      
};

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
    uint8_t bytes[ sizeof(Sensores_t) ];
};

