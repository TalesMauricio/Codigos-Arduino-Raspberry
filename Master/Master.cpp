 
 
 /*	Master com controle
  * 
  * Com controle de estados
  *
  */
  
#include "RF24Mesh/RF24Mesh.h"  
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);  
RF24Network network(radio);
RF24Mesh mesh(radio,network);
uint32_t displayTimer=0;

/* Estrutura do pacote a ser enviado
erro:
   Dec ||     Bin  ||  Código
    1: ||       1  ||  Dados recebidos inconpativeis
    2: ||      10  ||  Tempo de alimentação muito grande
    4: ||     100  ||  Porta do alimntador com defeito
    8: ||    1000  ||  Tampa do reservatório aberta
   16: ||   10000  ||  
*/

struct pacote_t
{
  uint8_t alimentadorID; // ID de qual alimentador a informação está sendo enviada  
  uint8_t hora;          // Hora que foi enviada
  uint8_t minuto;        // Minuto que foi enviada
  uint8_t nivel;         // Nível de ração no reservatório 1
  uint8_t bateria;       // Bateria
  uint8_t erro;          // Erro - ler tabela ^^^^
  uint16_t temperatura;
  uint8_t ph;
  uint8_t turbidez;
  uint8_t condutividade;
  uint8_t oxigen;
};

// /*
struct diretriz_t
{
  unsigned short alimentID;         // ID do alimentador                       informaçao nao será usada aqui
  unsigned short horad[6];
  unsigned short minutod[6];
  unsigned short qtdd[6];   
};

struct relogio_t
{
  unsigned char segu;   // ajustar o segundo
  unsigned char minu;   // ajustar o minuto 
  unsigned char hora;   // ajustar a hora
  unsigned char diam;   // ajustar o dia do mes
  unsigned char mess;   // ajustar o mes
  unsigned char anoo;   // ajustar o ano
};

	unsigned char segui;
	unsigned char minui;
	unsigned char horai;	
	unsigned char diasi;
	unsigned char diami;
	unsigned char messi;	
	unsigned char anooi;
	unsigned char i=0;
	unsigned char apagarq=0;


// */
//Funções-----------------------------------------------
void Rx();
void Tx();
void Tx_hora_correta();
void Obter_comparador();

//------------------------------------------------------
FILE *arq, *arq_medidas;
diretriz_t diretriz;
pacote_t pacote;
relogio_t relogio;
//------------------------------------------------------

float pH = 0;
float temper = 0;

int main(int argc, char** argv) {  
 
	mesh.setNodeID(0);
//	printf("start\n");
	mesh.begin();
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_1MBPS);
	radio.setCRCLength(RF24_CRC_16);
  
	radio.printDetails();
	
	
	// char url[]="nodes.txt";
	//FILE *arq, *arq_medidas;
  

	while(1)	
	{
		arq = fopen("nodes.txt", "r");
		if(arq == NULL)
		{ // se nao foi possivel abrir o arquivo...			
			Rx(); // inicia a leitura ###################### se possivel fazer um loop por um determinado tempo ###########								
		}
		else
		{
			
//			while( (fscanf(arq,"%hu %hu %hu %hu %hu\n",
//   por é %hhu mesmo
			while( (fscanf(arq,"%hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu\n",
							   &diretriz.alimentID, 
							   &diretriz.horad[0], 
							   &diretriz.minutod[0],							   
							   &diretriz.qtdd[0],
							   &diretriz.horad[1], 
							   &diretriz.minutod[1],							   
							   &diretriz.qtdd[1],
							   &diretriz.horad[2], 
							   &diretriz.minutod[2],							   
							   &diretriz.qtdd[2],
							   &diretriz.horad[3], 
							   &diretriz.minutod[3],							   
							   &diretriz.qtdd[3],
							   &diretriz.horad[4], 
							   &diretriz.minutod[4],							   
							   &diretriz.qtdd[4],
							   &diretriz.horad[5], 
							   &diretriz.minutod[5],							   
							   &diretriz.qtdd[5]))!=EOF )
			{
				Tx();				
				//printf(" ||||   %hu %hu %hu %hu %hu  ", diretriz.alimentID, diretriz.inicio_hora, diretriz.inicio_minuto, diretriz.frequencia, diretriz.qtd);
			}	
			delay(500);		
			fclose(arq);
			delay(500);			
			apagarq++;
//			printf("  %hu   ",apagarq);
			if(apagarq == 10){
				printf("     Arquivo apagado \n\n");	
				remove("nodes.txt");
				apagarq = 0;
				}
			
		}
	
//		if(millis() - displayTimer >= 100000){
//			displayTimer = millis();
//			Tx_hora_correta();
	
//		}
		
	}
return 0;
}

///////////////////////////////////////////////  RX
void Rx()
{
	mesh.update();
	mesh.DHCP();	
	
    
	if(network.available())
	{    // retirar o while
		RF24NetworkHeader header;
		network.peek(header);    
		
		network.read(header,&pacote,sizeof(pacote));
		
		switch(header.type)
		{
			case 'M':
			
				Obter_comparador();
				if(pacote.hora != horai || ((pacote.minuto <= (minui-2) || (pacote.minuto >= (minui+2)))))
				{
					printf("\n####################################################\n");
					printf("hora do alimentador %hu esta errada \n", pacote.alimentadorID);
					Tx_hora_correta();
				}
				
				//Calibração dos sensores
				pH = 0.026087* (float) pacote.ph + 2.565;
				temper = ((float) pacote.temperatura)/16;
				
				if(pH<=0) pH=0;
				if(pH>=14) pH=14.0;
				if(temper>=50) temper=0.0;
				
				printf("Rx:");
				printf("  NodeID: %hu    Hora: %hu    Minuto: %hu    Nivel: %hu    Bateria: %hu    Erro: %hu    Temp: %.2f    pH %.2f    Turb %hu    Cond %hu    Oxi %hu\n",
				        pacote.alimentadorID, 
				        pacote.hora, 
				        pacote.minuto, 
				        pacote.nivel, 
				        pacote.bateria, 
				        pacote.erro,
				        temper,
				        pH,
				        pacote.turbidez,
				        pacote.condutividade,
				        pacote.oxigen); 
			
//			char url [] = " medidas_tanques.txt " ;			
			
				arq_medidas = fopen ("medidas_tanques.txt", "a" );
				if (arq_medidas == NULL )
				{
					printf ("Erro, nao foi possivel abrir o arquivo \n");
				}
				else 
				{
					fprintf(arq_medidas, "%hu %hu %hu %d %hu %hu %hu %.2f %.2f %hu %hu %hu\n" , 
										  pacote.alimentadorID, 
										  pacote.hora, 
                                          pacote.minuto,
                                          segui, 
                                          pacote.nivel, 
                                          pacote.bateria, 
                                          pacote.erro,
                                          temper,
										  pH,
										  pacote.turbidez,
										  pacote.condutividade,
										  pacote.oxigen);
				}
			fclose (arq_medidas);		
			
			break;        
		
		default:  network.read(header,0,0); 
			printf("Rcv bad type %d from 0%o\n",header.type,header.from_node); 
			break;
		}    
	}
}


//////////////////////////////////////////////// TX
void Tx()
{
	mesh.update();
		
	if (!mesh.write(&diretriz, 'D', sizeof(diretriz), diretriz.alimentID)) 
	{
		printf("Nao enviado para %hu \n", diretriz.alimentID);
		delay(2000);	
	
      
	} 
	else 
	{   
	
		
//		printf("Tx: ID: %hu  inicH: %hu inicM: %hu  freq: %hu  qtd: %hu \n",
        printf("  %hu   ",apagarq); 
		printf("Tx: ID: %hu  h1:%hu:%hu Q1:%hu    h2:%hu:%hu Q2:%hu    h3:%hu:%hu Q3:%hu    h4:%hu:%hu Q4:%hu    h5:%hu:%hu Q5:%hu    h6:%hu:%hu Q6:%hu\n", 
		       diretriz.alimentID, 
		       diretriz.horad[0], 
		       diretriz.minutod[0],
		       diretriz.qtdd[0],
		       diretriz.horad[1], 
		       diretriz.minutod[1],
		       diretriz.qtdd[1],
		       diretriz.horad[2], 
		       diretriz.minutod[2],
		       diretriz.qtdd[2],
		       diretriz.horad[3], 
		       diretriz.minutod[3],
		       diretriz.qtdd[3],
		       diretriz.horad[4], 
		       diretriz.minutod[4],
		       diretriz.qtdd[4],
		       diretriz.horad[5], 
		       diretriz.minutod[5],
		       diretriz.qtdd[5]); // somente para testes 
		       	        
		delay(500);
		
//testes mostraram que nao é possivel enviar para o mesmo alimentador em um periodo de tempo curto,
// entao para testes foi colocado esse delay que será returado posteriormente
        delay(1000);



		
		
//- fazer comando para mover arquivo para outra pasta....
//system("rm nodes.txt");
	} 	
	
}
//////////////////////////////////////////////// Tx_hora_correta
void Tx_hora_correta()
{
	time_t current_time;
	struct tm *time_info;
	char segu1[3];
	char minu1[3];
	char hora1[3];	
	char diam1[3];
	char mess1[3];	
	char anoo1[5];

	current_time = time(NULL);
	time_info = localtime(&current_time);
	strftime(segu1, 3, "%S", time_info);
	strftime(minu1, 3, "%M", time_info);
	strftime(hora1, 3, "%H", time_info);
	strftime(diam1, 3, "%d", time_info);
	strftime(mess1, 3, "%m", time_info);
	strftime(anoo1, 5, "%g", time_info);
	
	segui=atoi(segu1);
	minui=atoi(minu1);
	horai=atoi(hora1);
	diami=atoi(diam1);
	messi=atoi(mess1);	
	anooi=atoi(anoo1);
	
	mesh.update();
	relogio = {segui, minui, horai, diami, messi, anooi};	
	if (!mesh.write(&relogio, 'T', sizeof(relogio), pacote.alimentadorID)) 
	{
		printf("Nao foi possivel atualizar o relogio do alimentador %hu \n", pacote.alimentadorID);
		printf("####################################################\n\n");
		delay(2000);      
	} 
	else 
	{  
		
		printf("Tx-hora-correta:\n");
		printf("alimentador id: %hu recebe: %i : %i : %i    %i / %i / %i \n", pacote.alimentadorID, horai, minui, segui, diami, messi, anooi);
		printf("####################################################\n\n"); 		       	        
		delay(2000);	
	} 	
	
}


//////////////////////////////////////////////// Obter_comparador
void Obter_comparador()
{ 
	time_t current_time;
	struct tm *time_info;
	char minu[3];
	char hora[3];
	char segu[3];
		
	current_time = time(NULL);
	time_info = localtime(&current_time);
	strftime(segu, 3, "%S", time_info);
	strftime(minu, 3, "%M", time_info);
	strftime(hora, 3, "%H", time_info);
	
	segui=atoi(segu);
	minui=atoi(minu);
	horai=atoi(hora);
		
}
      
