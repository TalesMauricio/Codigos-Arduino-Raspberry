#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


   unsigned short alimentadorID; // ID de qual alimentador a informação está sendo enviada  
   unsigned short horaaa;          // Hora que foi enviada
   unsigned short minuto;        // Minuto que foi enviada
   unsigned short nivel;         // Nível de ração no reservatório 1
   unsigned short bateria;       // Bateria
   unsigned short erro;          // Erro - ler tabela ^^^^
   
	unsigned short segui;
	unsigned short minui;
	unsigned short horai;	
	unsigned short diasi;
	unsigned short diami;
	unsigned short messi;	
	unsigned short anooi;
	unsigned short i=0;


FILE *arq_medidas;



int main(int argc, char** argv) {  

//int main (void) {	

	time_t current_time;
	struct tm *time_info;
	char segu[3];
	char minu[3];
	char hora[3];	
	char dias[2];
	char diam[3];
	char mess[3];	
	char anoo[5];

	current_time = time(NULL);
	time_info = localtime(&current_time);
	strftime(segu, 3, "%S", time_info);
	strftime(minu, 3, "%M", time_info);
	strftime(hora, 3, "%H", time_info);
	strftime(dias, 2, "%w", time_info);
	strftime(diam, 3, "%d", time_info);
	strftime(mess, 3, "%m", time_info);
	strftime(anoo, 5, "%g", time_info);
	
	segui=atoi(segu);
	minui=atoi(minu);
	horai=atoi(hora);	
	diasi=atoi(dias);
	diami=atoi(diam);
	messi=atoi(mess);	
	anooi=atoi(anoo);
	
	
	printf("segui:%i\n",segui);
	printf("minui:%i\n",minui);
	printf("horai:%i\n",horai);
	printf("diasi:%i\n",diasi);
	printf("diami:%i\n",diami);
	printf("messi:%i\n",messi);
	printf("anooi:%i\n\n\n",anooi);
	
	minui = minui + 2; 
	printf("minui mais 2 =:%i\n\n\n",minui);
	
		
	printf("segu: %s\n", segu);
	printf("minu: %s\n", minu);
	printf("hora: %s\n", hora);
	printf("dias: %s\n", dias);
	printf("diam: %s\n", diam);
	printf("mess: %s\n", mess);
	printf("anoo: %s\n", anoo);
	
	

			
	arq_medidas = fopen ("medidas_tanques2.txt", "r" );
			if (arq_medidas == NULL )
			{
				printf ("Erro, nao foi possivel abrir o arquivo \n");
			}
			else 
			{
				printf ("arquivo aberto \n");
				
				while( (fscanf(arq_medidas,"%hu %hu %hu %hu %hu %hu\n" , &alimentadorID, &horaaa, &minuto, &nivel, &bateria, &erro))!=EOF );
				{
					printf("  1-NodeID: %d  2-Hora: %d  3-Minuto: %d  4-Nivel: %d  5-Bateria: %d 6-Erro: %d \n",
				        &alimentadorID, 
				        &hora, 
				        &minuto, 
				        &nivel, 
				        &bateria, 
				        &erro ); 
				}
	
			}		
			fclose (arq_medidas);				





 


		
	
	
	return 0;
}
