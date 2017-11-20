/*
 *  Projeto Crema
 *  Alimentador de peixes;
 *  
*/

//#define numeroAlimentador  3       //1-5
#define profund 50      // profundidade da caixa (aqui vc coloca a pronfudidade da caixa em CM)
#define capacCompat 10.0 // Capacidade máxima do segundo armazenador em Kg
#define dtNBR_ALARMS 6   // Número max. de agendamentos de despejo de ração 

#define anguloPortaAbert 0
#define anguloPortaFecha 90
#define tempoPortaAbert 4000 // Em MS

// Aqui devem ser declaradas todas as bibliotecas compartilhadas, os defines de pinos e as variáveis globais, que são usadas em mais de um arquivo.
#include <Wire.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

#include "structs.cpp"

/**** Pinos da célula de carga ****/
#define  ADSK  3  //SCK
#define  ADDO  4  //DOUT

/**** Pinos do motor(fuso) e servo(porta) ****/
#define servo 5
#define fuso 8

/**** Nivel com HC-SR04 ****/
#define trigPin 6 // Pino 6 envia o pulso para gerar o echo do Sensor 1
#define echoPin 7 // Pino 7 recebe o pulso do echo do Sensor 1

/**** nrf24l01 pins ****/
#define CEpin 9
#define CSpin 10

/**** Pinos da medição de bateria ****/
#define leBatPin A0 // (14) Pino de leitura analógica do nivel de bateria
#define enBatPin A1  // (15) Pino de ativação de leitura do nivel de bateria

// Declaração de variaveis e estruturas globais
uint8_t nivelRacao;
uint8_t nivelBateria;
float qtdRacao[dtNBR_ALARMS];
Sensores_t dados;


bool conectado = false;
bool tempoSinc = false;
unsigned long past = 0;

