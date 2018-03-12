#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    //Trocar pelos valores recebidos  

	FILE *arq_medidas;

	arq_medidas = fopen("nodes.txt", "r");
	if(arq_medidas == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		fclose(arq_medidas);
		system("rm nodes.txt");		
	}
	
	

	return 0;;
}
