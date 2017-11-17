#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int linha = 0;
int coluna = 0;

//NOME DA FILA
const char *NOME_FILA = "/jogada2";

//ESTRUTURA DA MSG
typedef struct Mensagem {
	int id;
	char jogadaLinha[10];
	char jogadaColuna[10];
} TMensagem;


int main(int argc, char *argv[])
{
	mqd_t queue; //ID queue
	TMensagem jog; 
	char* primeiraLinha = argv[1]; 
	char* segundaColuna = argv[2];


	//Obtendo descritor 
	queue = mq_open(NOME_FILA, O_WRONLY | O_CREAT, 0666, NULL); 
	

	//Verificando erro
	if(queue == (mqd_t) -1)
	{
	perror("mq_open");
	exit(2);
	}


//MONTANDO A MSG 
jog.id = 1;
strncpy(jog.jogadaLinha, primeiraJogada, 10);
strcpy(jog.jogadaColuna, segundaJogada, 10);

linha = atoi(jogadaLinha);
coluna = atoi(jogadaColuna);



//ENVIAR MSG
if(mq_send(queue, &linha, sizeof(TMensagem), 10) != 0){
	perror("Linha");
}
if(mq_send(queue, &coluna, sizeof(TMensagem), 11) != 0){
	perror("Coluna");
}

mq_close(queue);
printf("Jogada Enviada\n");
exit(EXIT_SUCCESS);
}



