 
 
 /*	Master com controle
  * 
  * Com controle de estados
  *
  */
  
#include "RF24Mesh/RF24Mesh.h"  
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>


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
};

// /*
struct diretriz_t
{
  unsigned short alimentID;         // ID do alimentador                       informaçao nao será usada aqui
  unsigned short inicio_hora;       // hora de início
  unsigned short inicio_minuto;     // hora de início
  unsigned short frequencia;        // frequencia de alimentação
  unsigned short qtd;               // quantidade de raçao despejada          
};

struct relogio_t
{
  unsigned char segu;   // ajustar o segundo do RTC
  unsigned char minu;   // ajustar o minuto do RTC 
  unsigned char hora;   // ajustar a hora do RTC
  unsigned char dias;   // ajustar o dia da semana do RTC
  unsigned char diam;   // ajustar o dia do mes do RTC
  unsigned char mess;   // ajustar o mes do RTC
  unsigned char anoo;   // ajustar o ano do RTC
};


// */
//Funções-----------------------------------------------
void Rx();
void Tx();
void TxT();

//------------------------------------------------------
FILE *arq, *arq_medidas;
diretriz_t diretriz;
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
		arq = fopen("nodes.txt", "r");
		if(arq == NULL)
		{ // se nao foi possivel abrir o arquivo...			
			Rx(); // inicia a leitura ###################### se possivel fazer um loop por um determinado tempo ###########			
		}
		else
		{
			
			while( (fscanf(arq,"%hu %hu %hu %hu %hu\n", 
							   &diretriz.alimentID, 
							   &diretriz.inicio_hora, 
							   &diretriz.inicio_minuto, 
							   &diretriz.frequencia, 
							   &diretriz.qtd))!=EOF )
			{
				Tx();				
				//printf(" ||||   %hu %hu %hu %hu %hu  ", diretriz.alimentID, diretriz.inicio_hora, diretriz.inicio_minuto, diretriz.frequencia, diretriz.qtd);
			}	
					
			fclose(arq);
//		system("./apaga_arquivo");
			
		}
	
		if(millis() - displayTimer >= 60000){
			displayTimer = millis();
			TxT();
			
			printf("********Assigned Addresses********");
			for(int i=0; i<mesh.addrListTop; i++){
				printf("    NodeID: %d       RF24Network Address: 0%d   " mesh.addrList[i].nodeID, mesh.addrList[i].address,OCT);
				
			}
			printf("**********************************");
		}
		
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
				printf("Rx:");
				printf("  1-NodeID: %d  2-Hora: %d  3-Minuto: %d  4-Nivel: %d  5-Bateria: %d 6-Erro: %d \n",
				        pacote.alimentadorID, 
				        pacote.hora, 
				        pacote.minuto, 
				        pacote.nivel, 
				        pacote.bateria, 
				        pacote.erro ); 
			
//			char url [] = " medidas_tanques.txt " ;
			
			
				arq_medidas = fopen ("medidas_tanques.txt", "a" );
				if (arq_medidas == NULL )
				{
					printf ("Erro, nao foi possivel abrir o arquivo \n");
				}
				else 
				{
					fprintf(arq_medidas, "%hu %hu %hu %hu %hu %hu\n" , 
										  pacote.alimentadorID, 
										  pacote.hora, 
                                          pacote.minuto, 
                                          pacote.nivel, 
                                          pacote.bateria, 
                                          pacote.erro);
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
		printf("Tx: ID: %hu  inicH: %hu inicM: %hu  freq: %hu  qtd: %hu \n", 
		       diretriz.alimentID, 
		       diretriz.inicio_hora, 
		       diretriz.inicio_minuto, 
		       diretriz.frequencia, 
		       diretriz.qtd); // somente para testes 
		       	        
		delay(2000);
//- fazer comando para mover arquivo para outra pasta....
//system("rm nodes.txt");
	} 	
	
}
//////////////////////////////////////////////// TX
void TxT()
{
	mesh.update();
	relogio = {30, 20, 11, 0, 30, 5, 17};	
	if (!mesh.write(&relogio, 'T', sizeof(relogio), 2)) 
	{
		printf("Nao foi possivel atualizar o relogio do alimentador 2 \n");
		delay(2000);      
	} 
	else 
	{  
		printf("TxT: minuto     segundo \n"); 		       	        
		delay(2000);	
	} 	
	
}









      
      
      
