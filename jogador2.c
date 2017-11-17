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
typedef struct Mensagem1 {
	char jogadaLinha[10];
} TMensagem;

typedef struct Mensagem2 {
	char jogadaColuna[10];
} TMensagem2;

int main(int argc, char *argv[])
{
	mqd_t queue; 
	TMensagem jog; 
	TMensagem2 jog2;
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
strcpy(jog.jogadaLinha, primeiraLinha);
strcpy(jog2.jogadaColuna, segundaColuna);

linha = atoi(jog.jogadaLinha);
coluna = atoi(jog2.jogadaColuna);



//ENVIAR MSG
if(mq_send(queue, (const char*)&linha, sizeof(TMensagem), 10) != 0){
	perror("Linha");
}
if(mq_send(queue, (const char*)&coluna, sizeof(TMensagem2), 11) != 0){
	perror("Coluna");
}

mq_close(queue);
printf("Jogada do segundo jogador enviada\n");
exit(EXIT_SUCCESS);
}



