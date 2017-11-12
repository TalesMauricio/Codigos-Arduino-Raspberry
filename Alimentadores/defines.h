/*
 *  Projeto Crema
 *  Alimentador de peixes;
 *  
*/

//#define numeroAlimentador  3       //1-5

// Aqui devem ser declaradas todas as bibliotecas compartilhadas, os defines de pinos e as variáveis globais, que são usadas em mais de um arquivo.
#include <Wire.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "estruturas.cpp"

/**** nrf24l01 pins ****/
#define CEpin 9
#define CSpin 10

/**** Nivel com HC-SR04 ****/
#define echoPin 7 // Pino 7 recebe o pulso do echo do Sensor 1
#define trigPin 6 // Pino 6 envia o pulso para gerar o echo do Sensor 1

/**** Pinos da célula de carga ****/
#define  ADDO  4  //DOUT
#define  ADSK  3  //SCK

/**** Pinos do motor(fuso) e servo(porta) ****/
#define fuso 8
#define servo 5

// Declaração de estruturas globais
unsigned char nivelRacao;
unsigned char nivelBateria;
Sensores_t dados;

bool conectado = false;
bool tempoSinc = false;
unsigned long past = 0;
