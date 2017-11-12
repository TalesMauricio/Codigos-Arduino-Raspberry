
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
  unsigned char alimentadorID; // ID de qual alimentador a informação está sendo enviada  
  unsigned char hora;          // Hora que foi enviada
  unsigned char minuto;        // Minuto que foi enviada
  unsigned char nivel;         // Nível de ração no reservatório 1
  unsigned char bateria;       // Bateria
  unsigned char erro;          // leia a estrutura
  unsigned char temperatura;
  unsigned char ph;
  unsigned char turbidez;
  unsigned char condutividade;
  unsigned char oxigen;
};

struct diretriz_t
{
  int alimentID;          // ID do alimentador                       informaçao nao será usada aqui
  int inicio_hora;        // Mora de início
  int inicio_minuto;      // Minuto de início
  //int frequencia;         // Frequencia de alimentação
  int qtd;                // Quantidade de raçao a ser despejada  
};

struct relogio_t
{
  unsigned char hora, minuto, segundo;
  unsigned char dia, mes, ano;
      
};

struct Sensores_t
{
  unsigned char temperatura;
  unsigned char ph;
  unsigned char turbidez;
  unsigned char condutividade;
  unsigned char oxigen;
};

union Dados_t
{
    Sensores_t valor;
    char bytes[ sizeof(Sensores_t) ];
};

