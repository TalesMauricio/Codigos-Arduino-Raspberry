/*
 *  Projeto Crema
 *  Alimentador de peixes;
 *  
*/

//#define numeroAlimentador  3       //1-5
#define profund 64      // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)
#define capacCompat 10.0 // Capacidade máxima do segundo armazenador em Kg
#define dtNBR_ALARMS 6   // Número max. de agendamentos de despejo de ração 

#define anguloPortaAbert 60
#define anguloPortaFecha 0
#define tempoPortaAbert 500 // Em MS

// Aqui devem ser declaradas todas as bibliotecas compartilhadas, os defines de pinos e as variáveis globais, que são usadas em mais de um arquivo.
#include <Wire.h>
#include <TimeLib.h>
//#include <TimeAlarms.h>

#include "structs.cpp"
#include "secundaria/dados.cpp"

/**** Pinos da célula de carga ****/
#define  ADSK  3  //SCK
#define  ADDO  4  //DOUT

/**** Pinos do motor(fuso) e servo(porta) ****/
#define servo 5
#define enServo 2
#define fuso 8

/**** Nivel com HC-SR04 ****/
#define trigPin 6 // Pino 6 envia o pulso para gerar o echo do Sensor 1
#define echoPin 7 // Pino 7 recebe o pulso do echo do Sensor 1

/**** nrf24l01 pins ****/
#define CEpin 9
#define CSpin 10

/**** Pinos da medição de bateria ****/
#define leBatPin A1 // (14) Pino de leitura analógica do nivel de bateria
#define enBatPin A0  // (15) Pino de ativação de leitura do nivel de bateria

/**** Pinos da medição da tampa do reservatorio ****/
#define tampa A2

/**** Pinos da medição da rotaçao do fuso ****/
// nao  mais #define rotfuso A3
// a3 = vibra

// Declaração de variaveis e estruturas globais
uint8_t nivelRacao;
//uint8_t nivelBateria;
int nivelBateria;
uint8_t erro;
float qtdRacao[dtNBR_ALARMS];
Sensores_t dados;


bool conectado = false;
bool tempoSinc = false;
bool erro_nivel_ra = false;
bool flag_a = false;
unsigned long past = 0;
unsigned long pastflag = 0;
unsigned long pastbat = 0;
unsigned long tara = 0;
//uint8_t flag_a = 0; //Flag para verificar se já alimentou naquele horário

unsigned long flag_alimenta = 0;

