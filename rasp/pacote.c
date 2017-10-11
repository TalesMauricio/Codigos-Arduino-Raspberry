//Estrutura do pacote a ser enviado
struct pacote_t
{
  uint8_t alimentadorID; //ID de qual alimentador a informação está sendo enviada
  uint8_t hora;          //Hora que foi enviada
  uint8_t minuto;        //Minuto que foi enviada
  uint8_t nivel;         //Nível de ração no reservatório 1
  uint8_t temperatura;          //Informação
};

struct diretriz_t
{
  uint8_t alimentID;     //ID do alimentador                       informaçao nao será usada aqui
  uint8_t inicio;            //hora de início
  uint8_t frequencia;        //frequencia de alimentação
  uint8_t qtd;               //quantidade de raçao despejada
  uint8_t transf;          //tempo de atualização dos dados
};
