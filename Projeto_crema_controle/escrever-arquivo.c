#include <stdio.h>

typedef struct
{
  int alimentadorID; //ID de qual alimentador a informação está sendo enviada
  int hora;          //Hora que foi enviada
  int minuto;        //Minuto que foi enviada
  int nivel;         //Nível de ração no reservatório 1
  int temperatura;   //Informação
}pacote_t;

typedef struct
{
  int alimentID;     //ID do alimentador                       informaçao nao será usada aqui
  int inicio_hora;        //hora de início
  int inicio_minuto;
  int frequencia;    //frequencia de alimentação
  int qtd;           //quantidade de raçao despejada
}diretriz_t;



int main(void)
{
    //Trocar pelos valores recebidos
    pacote_t pacote = {23, 45, 83, 98, 11};

    char url[]="medidas_tanques.txt";
	FILE *arq_medidas;

	arq_medidas = fopen(url, "a");
	if(arq_medidas == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		fprintf(arq_medidas, "%d %d %d %d %d\n", pacote.alimentadorID,
                                                 pacote.hora,
                                                 pacote.minuto,
                                                 pacote.nivel,
                                                 pacote.temperatura);
	}
	fclose(arq_medidas);

	return 0;;
}
