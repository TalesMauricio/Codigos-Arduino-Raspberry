/*
 *  Projeto Crema
 *  Alimentador de peixes;
 *  
 *   Este não é o código principal. Os blocos setup e loop estão no arquivo (aba) main.
 *   Isto foi feito para possibilitar a declaração de todas as funções de modo simples no arduino.
*/

// Aqui devem ser declaradas todas as bibliotecas compartilhadas, os defines de pinos e as variáveis globais, que são usadas em mais de um arquivo.
#include <TimeLib.h>
#include <Wire.h>
#include "estruturas.cpp"
#include "dados.cpp"

/**** Real Time Clock RTC DS1307 ****/
#define DS1307_ADDRESS 0x68

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
Dados_t dados;
//relogio_t relogio;

bool tempoSinc = false;

// RTC
char segundos = 0;        // Segundo atual do RTC
char minutos = 0;         // Minuto atual do RTC
char horas = 0;           // Hora atual do RTC
char diadasemana = 0;     // Dia da semana atual do RTC
char diadomes = 0;        // Dia do mes atual do RTC
char mes = 0;             // Mes atual do RTC
char ano = 0;             // Ano atual do RTC
