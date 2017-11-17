#include <stdio.h>
#include <stdlib.h>

int *linha;
int *coluna;
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


void captura_msgLinha(TMensagem* msg) {
	linha->msg->jogadaLinha;
	coluna->msg->jogadaColuna;
}

void captura_msgColuna(TMensagem2* msg) {
	coluna->msg->jogadaColuna;
}

ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	if (mq_getattr(queue, &attr) != -1) {
		printf("max msg size: %ld\n", attr.mq_msgsize);
		return attr.mq_msgsize;
	}

	perror("aloca_msg_buffer");
	exit(3);
}


void jogadaInvalida(int *linha, int *coluna)
{
while(linha < 0 || coluna < 0 || linha > 2 || coluna > 2){
	printf("Jogada Invalida...Tente novamente\n");
}
}

void mapaJogo(char mapa[2][2])
{
printf("\t %c | %c | %c\n", mapa[0][0], mapa[0][1], mapa[0][2]);
printf("\t-------------\n");
printf("\t %c | %c | %c\n", mapa[1]0], mapa[1][1], mapa[1][2]);
printf("\t-------------\n");
printf("\t %c | %c | %c\n", mapa[2][0], mapa[2][1], mapa[2][2]);
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
ssize_t nbytes;
ssize_t tam_buffer2;
ssize_t nbytes2;

	/*ABERTURA FILA PARA JOGADOR 1*/
	queue = mq_open(NOME_FILA, O_RDONLY);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);

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

	
}
