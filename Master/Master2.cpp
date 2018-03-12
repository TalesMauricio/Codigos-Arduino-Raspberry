

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

#define numDiretrizes 6
#define numAlimentadores 4

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
  uint8_t temperatura;
  uint8_t ph;
  uint8_t turbidez;
  uint8_t condutividade;
  uint8_t oxigen;
};

// /*
struct diretriz_t
{
  unsigned short inicio_hora;       // hora de início
  unsigned short inicio_minuto;     // hora de início
  unsigned short qtd;               // quantidade de raçao despejada

};

struct tabelaAgendamentos_t
{
  unsigned short alimentID;         // ID do alimentador
  diretriz_t diretriz[numDiretrizes]

};

struct relogio_t
{
  uint8_t segu;   // ajustar o segundo do RTC
  uint8_t minu;   // ajustar o minuto do RTC
  uint8_t hora;   // ajustar a hora do RTC
  uint8_t diam;   // ajustar o dia do mes do RTC
  uint8_t mess;   // ajustar o mes do RTC
  uint8_t anoo;   // ajustar o ano do RTC
};

	uint8_t segui;
	uint8_t minui;
	uint8_t horai;
	uint8_t diami;
	uint8_t messi;
	uint8_t anooi;
	uint8_t i=0;


// */
//Funções-----------------------------------------------
void Rx();
void Tx();
void Tx_hora_correta();
void Obter_comparador();

//------------------------------------------------------
FILE *arq, *arq_medidas;
tabelaAgendamentos_t alimentador[numAlimentadores];
pacote_t pacote;
relogio_t relogio;
//------------------------------------------------------

int main(int argc, char** argv) {

	mesh.setNodeID(0);
	printf("start\n");
	mesh.begin();
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_1MBPS);
	radio.setCRCLength(RF24_CRC_16);

	radio.printDetails();


	// char url[]="nodes.txt";
	//FILE *arq, *arq_medidas;


	while(1)
	{
        mesh.update();
        mesh.DHCP();

		arq = fopen("nodes.txt", "r");
		if(arq == NULL)
		{ // se nao foi possivel abrir o arquivo...
			Rx(); // inicia a leitura ###################### se possivel fazer um loop por um determinado tempo ###########
		}
		else
		{

//			while( (fscanf(arq,"%hu %hu %hu %hu %hu\n",
			while( (fscanf(arq,"%hu %hu %hu %hu\n",
							   &diretriz.alimentID,
							   &diretriz.inicio_hora,
							   &diretriz.inicio_minuto,
//							   &diretriz.frequencia,
							   &diretriz.qtd))!=EOF )
			{
				Tx();
				//printf(" ||||   %hu %hu %hu %hu %hu  ", diretriz.alimentID, diretriz.inicio_hora, diretriz.inicio_minuto, diretriz.frequencia, diretriz.qtd);
			}

			fclose(arq);
//		system("./apaga_arquivo");

		}

		if(millis() - displayTimer >= 100000){
			displayTimer = millis();
//			Tx_hora_correta();

		}

	}
return 0;
}

///////////////////////////////////////////////  RX
void Rx()
{
	if(network.available())
	{    // retirar o while
		RF24NetworkHeader header;
		network.peek(header);

		network.read(header,&pacote,sizeof(pacote));

		switch(header.type)
		{
			case 'M':

				Obter_comparador();
				if(pacote.hora != horai || pacote.minuto != minui)
				{
					printf("\n####################################################\n");
					printf("hora do alimentador %hu esta errada \n", pacote.alimentadorID);
					Tx_hora_correta();
				}


				printf("Rx:");
				printf("  1-NodeID: %hu  2-Hora: %hu  3-Minuto: %hu  4-Nivel: %hu  5-Bateria: %hu 6-Erro: %hu   temp %hu ph %hu tur %hu  cond %hu oxi %hu\n",
				        pacote.alimentadorID,
				        pacote.hora,
				        pacote.minuto,
				        pacote.nivel,
				        pacote.bateria,
				        pacote.erro,
				        pacote.temperatura,
				        pacote.ph,
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
					fprintf(arq_medidas, "%hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu\n" ,
										  pacote.alimentadorID,
										  pacote.hora,
                                          pacote.minuto,
                                          pacote.nivel,
                                          pacote.bateria,
                                          pacote.erro,
                                          pacote.temperatura,
										  pacote.ph,
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
    for(int idAgend=0; idAgend < numDiretrizes; idAgend++)
    {
        enviado = mesh.write(&alimentador[alimentID].diretriz, 'D', sizeof(diretriz), alimentID);

        if (!enviado)
        {
            printf("Nao enviado para %hu \n", diretriz.alimentID);
        }
        else
        {
            printf("Tx: ID: %hu  inicH: %hu inicM: %hu  qtd: %hu \n",
                   diretriz.alimentID,
                   diretriz.inicio_hora,
                   diretriz.inicio_minuto,
                   diretriz.qtd); // somente para testes

    //- fazer comando para mover arquivo para outra pasta....
    //system("rm nodes.txt");
        }
    }
	delay(2000);

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

	current_time = time(NULL);
	time_info = localtime(&current_time);
	strftime(minu, 3, "%M", time_info);
	strftime(hora, 3, "%H", time_info);
	minui=atoi(minu);
	horai=atoi(hora);

}

