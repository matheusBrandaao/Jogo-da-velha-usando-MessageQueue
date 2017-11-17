#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int partida = 0;
char mapa[2][2];

//VALORES PARA X 
int linha; 
int coluna;

//VALORES PARA O
int linha2;
int coluna2;


//NOME DA FILA
const char* NOME_FILA = "/jogada1";
const char* NOME_FILA2 = "/jogada2";

//ESTRUTURA DA MSG
typedef struct Mensagem {
	char jogadaLinha[10];
} TMensagem;

typedef struct Mensagem2 {
	char jogadaColuna[10];
}TMensagem2;

/*
int* captura_msgLinha(TMensagem* msg, int *valor) {
	valor->msg->jogadaLinha;
	return valor;
}

int* captura_msgColuna(TMensagem2* msg, int *valor) {
	valor->msg->jogadaColuna;
	return valor;
}
*/

ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	if (mq_getattr(queue, &attr) != -1) {
		printf("max msg size: %ld\n", attr.mq_msgsize);
		return attr.mq_msgsize;
	}

	perror("aloca_msg_buffer");
	exit(3);
}


int jogadaInvalida(int linha, int coluna)
{
if(linha < 0 || coluna < 0 || linha > 2 || coluna > 2){
	return 0;
}
return 1;
}

void mapaJogo()
{

for(int i=0; i<2; i++){
	for(int j=0; j<2; j++)
		mapa[i][j] = ' '; 
}

printf("\t %c | %c | %c\n", mapa[0][0], mapa[0][1], mapa[0][2]);
printf("\t-------------\n");
printf("\t %c | %c | %c\n", mapa[1][0], mapa[1][1], mapa[1][2]);
printf("\t-------------\n");
printf("\t %c | %c | %c\n", mapa[2][0], mapa[2][1], mapa[2][2]);
}

void insereJogada(int linha, int coluna)
{
	int aux;
	aux = jogadaInvalida(linha, coluna);
	if(aux == 0)
		printf("Jogada Invalida...Tente novamente\n");
	else
	mapa[linha][coluna] = 'X';
	mapa[linha][coluna] = 'O';
}



int main(void)
{
mqd_t queue;
mqd_t queue2;
char *jogadaLinha = NULL;
char *jogadaColuna = NULL;
char *jogadaLinha2 = NULL;
char *jogadaColuna2 = NULL;
ssize_t tam_buffer;
ssize_t nbytesLinha;
ssize_t nbytesColuna;
ssize_t tam_buffer2;
ssize_t nbytesLinha2;
ssize_t nbytesColuna2;
	/*ABERTURA FILA PARA JOGADOR 1*/
	queue = mq_open(NOME_FILA, O_RDONLY);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}

	/*ABERTURA FILA PARA JOGADOR 2*/
	queue2 = mq_open(NOME_FILA2, O_RDONLY);
	if(queue2 == (mqd_t) -1){
		perror("mq_open2");
		exit(2);
	}


	// alocar buffer para receber msg
	tam_buffer = get_msg_buffer_size(queue);
	jogadaLinha = calloc(tam_buffer, 1);

	tam_buffer = get_msg_buffer_size(queue);
	jogadaColuna = calloc(tam_buffer, 1);


	tam_buffer2 = get_msg_buffer_size(queue2);
	jogadaLinha2 = calloc(tam_buffer2, 1);

	tam_buffer2 = get_msg_buffer_size(queue2);
	jogadaColuna2 = calloc(tam_buffer2, 1);

	nbytesLinha = mq_receive(queue, jogadaLinha, tam_buffer, NULL);
	if (nbytesLinha == -1) {
		perror("receive");
		exit(4);
	}

	nbytesColuna = mq_receive(queue, jogadaColuna, tam_buffer, NULL);
	if (nbytesColuna == -1) {
		perror("receive");
		exit(4);
	}

	nbytesLinha2 = mq_receive(queue2, jogadaLinha2, tam_buffer2, NULL);
	if (nbytesLinha2 == -1) {
		perror("receive");
		exit(4);
	}

	nbytesColuna2 = mq_receive(queue2, jogadaColuna2, tam_buffer2, NULL);
	if (nbytesColuna2 == -1) {
		perror("receive");
		exit(4);
	}

	
	linha = *jogadaLinha;
	coluna = *jogadaColuna;

	linha2 = *jogadaLinha2;
	coluna2 = *jogadaColuna2;

	mapaJogo();
	insereJogada(linha, coluna);
	insereJogada(linha2, coluna2);








	// liberar descritor (mq_close)
	if(partida == 11)
	{
	mq_close(queue);
	printf("Fim!\n");
	exit(EXIT_SUCCESS);
	}
}

