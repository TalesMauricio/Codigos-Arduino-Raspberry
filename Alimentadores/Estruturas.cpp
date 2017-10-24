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
};

struct diretriz_t
{
  int alimentID;          // ID do alimentador                       informaçao nao será usada aqui
  int inicio_hora;        // Mora de início
  int inicio_minuto;      // Minuto de início
  int frequencia;         // Frequencia de alimentação
  int qtd;                // Quantidade de raçao a ser despejada  
};

struct relogio_t
{
  byte segu;          // Dado para atualizar o segundo do RTC                       
  byte minu;          // Dado para atualizar o minuto do RTC
  byte hora;          // Dado para atualizar a hora do RTC
  byte dias;          // Dado para atualizar o dia da semana do RTC
  byte diam;          // Dado para atualizar o dia do mes do RTC
  byte mess;          // Dado para atualizar o mes do RTC
  byte anoo;          // Dado para atualizar o ano do RTC
      
};

