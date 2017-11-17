#include <stdio.h>
#include <stdlib.h>

int *linha;
int *coluna;
//NOME DA FILA
const char* NOME_FILA = "/jogada1";
const char* NOME_FILA2 = "/jogada2";

//ESTRUTURA DA MSG
typedef struct Mensagem {
	int id;
	char jogadaLinha[10];
	char jogadaColuna[10];
} TMensagem;


void captura_msg(TMensagem* msg) {
	linha->msg->jogadaLinha;
	coluna->msg->jogadaColuna;
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
char *buffer = NULL;
ssize_t tam_buffer;
ssize_t nbytes;

	queue = mq_open(NOME_FILA, O_RDONLY);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);

	// alocar buffer para receber msg
	
}