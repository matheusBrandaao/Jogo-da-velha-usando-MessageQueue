#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int sair;
int running = 1;
int partida = 0;
char mapa[2][2];

//VALORES PARA X 
int linha; 
int coluna;

//VALORES PARA O
int linha2;
int coluna2;

//NOME JOGADORES
char nomeJogador1[100];
char nomeJogador2[100];


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


ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	if (mq_getattr(queue, &attr) != -1) {
		return attr.mq_msgsize;
	}

	perror("aloca_msg_buffer");
	exit(3);
}


int jogadaInvalida(int linha, int coluna)
{
if(mapa[linha][coluna] != ' ')
{
	return 0;
}
return 1;
}

void mapaJogo()
{
system("clear");
for(int i=0; i<2; i++){
	for(int j=0; j<2; j++)
		mapa[i][j] = ' '; 
}

}

void exibeMapa()
{
printf("JOGO DA VELHA!!!\n");
printf("\t%c | %c | %c\n", mapa[0][0], mapa[0][1], mapa[0][2]);
printf("\t-------------\n");
printf("\t%c | %c | %c\n", mapa[1][0], mapa[1][1], mapa[1][2]);
printf("\t-------------\n");
printf("\t%c | %c | %c\n", mapa[2][0], mapa[2][1], mapa[2][2]);
}

//VERIFICAR COMO INTERROMPER E PEDIR JOGADA DE NOVO
void insereJogadaX(int linha, int coluna)
{
	int aux;
	aux = jogadaInvalida(linha, coluna);
	if(aux == 0)
		printf("Jogada Invalida...Tente novamente\n");
	else
	mapa[linha][coluna] = 'X';
	partida++;
}

void insereJogadaO(int linha, int coluna)
{
	int aux;
	aux = jogadaInvalida(linha, coluna);
	if(aux == 0)
		printf("Jogada Invalida...Tente novamente\n");
	else
	mapa[linha][coluna] = 'O';
	partida++;
}

void condicoesVitoria()
{
	//horizontal
	if(mapa[0][0] == 'X' && mapa[0][1] == 'X' && mapa[0][2] == 'X') {partida = 12;}
	if(mapa[1][0] == 'X' && mapa[1][1] == 'X' && mapa[1][2] == 'X') {partida = 12;}
	if(mapa[2][0] == 'X' && mapa[2][1] == 'X' && mapa[2][2] == 'X') {partida = 12;}
	//diagonal
	if(mapa[0][0] == 'X' && mapa[1][1] == 'X' && mapa[2][2] == 'X') {partida = 12;}
	if(mapa[2][2] == 'X' && mapa[1][1] == 'X' && mapa[0][2] == 'X') {partida = 12;}
	//vertical
	if(mapa[0][0] == 'X' && mapa[1][0] == 'X' && mapa[2][0] == 'X') {partida = 12;}
	if(mapa[0][1] == 'X' && mapa[1][1] == 'X' && mapa[2][1] == 'X') {partida = 12;}
	if(mapa[0][2] == 'X' && mapa[1][2] == 'X' && mapa[2][2] == 'X') {partida = 12;}

	if(mapa[0][0] == 'O' && mapa[0][1] == 'O' && mapa[0][2] == 'O') {partida = 13;}
	if(mapa[1][0] == 'O' && mapa[1][1] == 'O' && mapa[1][2] == 'O') {partida = 13;}
	if(mapa[2][0] == 'O' && mapa[2][1] == 'O' && mapa[2][2] == 'O') {partida = 13;}
	
	if(mapa[0][0] == 'O' && mapa[1][1] == 'O' && mapa[2][2] == 'O') {partida = 13;}
	if(mapa[2][2] == 'O' && mapa[1][1] == 'O' && mapa[0][2] == 'O') {partida = 13;}

	if(mapa[0][0] == 'O' && mapa[1][0] == 'O' && mapa[2][0] == 'O') {partida = 13;}
	if(mapa[0][1] == 'O' && mapa[1][1] == 'O' && mapa[2][1] == 'O') {partida = 13;}
	if(mapa[0][2] == 'O' && mapa[1][2] == 'O' && mapa[2][2] == 'O') {partida = 13;}


	if(partida == 12){
		printf("%s ganhou do jogador %s\n", nomeJogador1, nomeJogador2);
		exit(2);
	}
	if(partida == 13){
		printf("%s ganhou do jogador %s\n", nomeJogador2, nomeJogador1);
		exit(2);
	}
	partida++;
}

void recebeNome()
{
printf("Digite o nome dos jogadores\n");
printf("Jogador1:");
scanf("%s", nomeJogador1);
printf("Jogador2:");
scanf("%s", nomeJogador2);
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

	//INICIA O MAPA DO JOGO E RECEBE O NOME DOS JOGADORES ANTES DE RECEBER AS MSG
	mapaJogo();
	recebeNome();

	/*ABERTURA FILA PARA JOGADOR 1*/
	queue = mq_open(NOME_FILA, O_RDONLY);
	if (queue == (mqd_t) -1) 
	{
		perror("mq_open");
		exit(2);
	}

	/*ABERTURA FILA PARA JOGADOR 2*/
	queue2 = mq_open(NOME_FILA2, O_RDONLY);
	if(queue2 == (mqd_t) -1)
	{
		perror("mq_open2");
		exit(2);
	}

	while(running)
	{
	system("clear");
	exibeMapa();
	printf("Deseja sair do jogo? [1(Sim) - 0(Não)]\n");
	scanf("%d", &sair);
	if(sair == 1){
	exit(2);
	running = 0;
	}
	printf("Aguardando jogadas...\n");
	
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
	if (nbytesLinha == -1) 
	{
		perror("receive");
		exit(4);
	}

	nbytesColuna = mq_receive(queue, jogadaColuna, tam_buffer, NULL);
	if (nbytesColuna == -1)
	{
		perror("receive");
		exit(4);
	}

	nbytesLinha2 = mq_receive(queue2, jogadaLinha2, tam_buffer2, NULL);
	if (nbytesLinha2 == -1) 
	{
		perror("receive");
		exit(4);
	}

	nbytesColuna2 = mq_receive(queue2, jogadaColuna2, tam_buffer2, NULL);
	if (nbytesColuna2 == -1) 
	{
		perror("receive");
		exit(4);
	}

	
	linha = *jogadaLinha;
	coluna = *jogadaColuna;

	linha2 = *jogadaLinha2;
	coluna2 = *jogadaColuna2;


	insereJogadaX(linha, coluna);
	insereJogadaO(linha2, coluna2);
	condicoesVitoria();
	
	

	// liberar descritor (mq_close)
	if(partida == 9 || partida == 12 || partida == 13)
	{
	exibeMapa();
	mq_close(queue);
	printf("Fim!\n");
	exit(EXIT_SUCCESS);
	running = 0; 
	}

}

}

